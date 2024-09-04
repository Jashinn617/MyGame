#include "ObjectManager.h"
#include "../Shader/ToonShader.h"
#include "../Shader/ShadowMapShader.h"

#include "../Object/Field.h"
#include "../Object/ObjectBase.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Item/ItemBase.h"
#include "../Object/Item/ItemManager.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"

#include "../Util/Input.h"
#include "../Util/Time.h"
#include "../Util/Collision.h"

#include "Model.h"

namespace
{	
	constexpr float kRotSpeed = 0.4f;	// ��]���x
	constexpr int kGameEndTime = 120;	// �S�[���ɂ��Ă��玟�̃V�[���Ɉڍs����܂ł̎���
}

ObjectManager::ObjectManager(Game::Stage stage):
	m_isGameClear(false),
	m_isGameEnd(false),
	m_isGoal(false),
	m_isTutorial(false)
{
	m_H = LoadGraph("Data/img/Sky.png");
	m_pCollision = std::make_shared<Collision>();
	m_pSkyDome = std::make_shared<SkyDome>();
	m_pEnemyManager = std::make_shared<EnemyManager>(stage, this);
	m_pItemManager = std::make_shared<ItemManager>(stage, this);
	m_pToonShader = std::make_shared<ToonShader>();
	m_pShadowMapShader = std::make_shared<ShadowMapShader>();
	m_gameEndTime = std::make_shared<Time>(kGameEndTime);

	AddObject(new Player);
	AddObject(new Field(stage));

	m_pItemManager->Init();
	m_pEnemyManager->Init();
}

ObjectManager::~ObjectManager()
{
	DeleteGraph(m_H);
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pObject.erase(it);
	}
}

void ObjectManager::Update(Input& input)
{
	// �I�u�W�F�N�g�z��̍ŏ��̃C�e���[�^���擾����
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		// �I�u�W�F�N�g�̍X�V
		auto obj = (*it);
		obj->Update(input);

		// �I�u�W�F�N�g�����݂��Ă��Ȃ��ꍇ
		if (!obj->GetInfo().isExist)
		{
			// �I�u�W�F�N�g���A�C�e���������ꍇ
			if (obj->GetColType() == ObjectBase::ColType::Item)
			{
				// �Q�b�g���𑝂₷
				m_pItemManager->AddGetNum();
			}

			// �I�u�W�F�N�g���v���C���[�ȊO�������ꍇ
			if (obj->GetColType() != ObjectBase::ColType::Player)
			{
				delete obj;
				obj = nullptr;
				it = m_pObject.erase(it);
			}
			else
			{
				// �C�e���[�^��i�߂�
				it++;
			}
		}
		else
		{
			// �C�e���[�^��i�߂�
			it++;
		}
	}

	// �A�C�e�������ׂďW�߂��ꍇ
	if (m_pItemManager->IsClear())
	{
		// �N���A�t���O��true�ɂ���
		m_isGameEnd = true;
	}

	if (m_isGameEnd)
	{
		// ��莞�Ԃ�������N���A�t���O�𗧂Ă�
		if (IsObjGameEnd())
		{
			m_isGameEnd = false;
			m_isGameClear = true;
		}
		else
		{
			GameEndUpdate();
		}
	}

	if (m_isGameClear)
	{
		// �N���A���̏���������
		GameClearUpdate();
	}

	// �X�J�C�h�[���̍X�V
	m_pSkyDome->Update(GetPlayer()->GetInfo().pos);

	// �N���A���Ă���ꍇ�͍X�V�������s��Ȃ�
	if (m_isGameClear) return;

	// �����蔻��
	for (auto& myObj : m_pObject)
	{
		for (auto& targetObj : m_pObject)
		{
			// �����I�u�W�F�N�g�̏ꍇ�͓����蔻��̏��������Ȃ�
			if (myObj == targetObj)continue;
			// �����蔻��̏���
			m_pCollision->Update(myObj, targetObj);
		}
	}
}

void ObjectManager::Draw()
{
	// �J�����̈ʒu�̃��Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();

	// �X�J�C�h�[���̕`��
	m_pSkyDome->Draw();

	// �I�u�W�F�N�g�̕`��
	for (auto& obj : m_pObject)
	{
		obj->Draw(m_pToonShader);
	}

	// �V���h�E�}�b�v�̏������݊J�n
	m_pShadowMapShader->WriteStart(GetPlayer()->GetPos());

	for (auto& obj : m_pObject)
	{
		// �t�B�[���h�ȊO�ɏ������s��
		// (�t�B�[���h�ɃV���h�E�}�b�v�𒣂�t���邽��)
		if (obj->GetColType() != ObjectBase::ColType::Field)
		{
			obj->ShadowMapDraw(m_pShadowMapShader);
		}
	}

	// �I��
	m_pShadowMapShader->WriteEnd();

	// �J�����̈ʒu�̃��Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();

	// �t�B�[���h�ɃV���h�E�}�b�v�𒣂�t���鏀��������
	m_pShadowMapShader->SetShaderField(GetPlayer()->GetPos());
	for (auto& obj : m_pObject)
	{
		//�����ł̓t�B�[���h�����`����s��
		if (obj->GetColType() == ObjectBase::ColType::Field)
		{
			obj->ShadowMapDraw(m_pShadowMapShader);
		}
	}
	// ��ƏI��
	m_pShadowMapShader->WriteEnd();

	 //�X�e�[�W�N���A���͕`������Ȃ�
	if (!m_isGameClear)
	{
		// �J�����̈ʒu�̃��Z�b�g
		GetPlayer()->GetCamera()->ResetCamera();

	// 2D�`��
		for (auto& obj : m_pObject)
		{
			obj->Draw2D();
		}
		// �c��A�C�e�����`��
		m_pItemManager->Draw();		
	}
	 //�J�����̈ʒu�̃��Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();
}

bool ObjectManager::IsPlayerExist()
{
	return GetPlayer()->GetInfo().isExist;
}

bool ObjectManager::IsEnemyExist()
{
	for (auto& enemy : m_pObject)
	{
		if (enemy->GetColType() != ObjectBase::ColType::Enemy) continue;

		if (enemy->GetInfo().isExist) return true;
	}
	return false;
}

bool ObjectManager::IsItemExist()
{
	for (auto& item : m_pObject)
	{
		if (item->GetColType() != ObjectBase::ColType::Item) continue;

		if (item->GetInfo().isExist) return true;
	}
	return false;
}

int ObjectManager::GetItemNum() const
{
	// �c��A�C�e���̐�
	int itemNum = 0;

	for (auto& item : m_pObject)
	{
		if (item->GetColType() != ObjectBase::ColType::Item) continue;

		itemNum++;
	}
	return itemNum;
}

bool ObjectManager::IsObjGameEnd()
{
	
	for (auto& obj : m_pObject)
	{
		// ������ł��I���������I���Ă��Ȃ��I�u�W�F�N�g����������
		// false�ŕԂ�
		if (!obj->IsGameEnd())
		{
			return false;
		}
	}

	// ���ׂẴI�u�W�F�N�g�̏I���������I���Ă���
	// ��莞�Ԃ������玟�̃V�[���ɔ��
	if (m_gameEndTime->Update())
	{
		return true;
	}
	
	return false;
}

Player* const ObjectManager::GetPlayer()
{
	// �S�I�u�W�F�N�g����������
	for (auto& obj : m_pObject)
	{
		if (obj->GetColType() != ObjectBase::ColType::Player) continue;

		return dynamic_cast<Player*>(obj);
	}

	return nullptr;
}

void ObjectManager::SetGameClear()
{
	// �N���A�t���O��true�ɂ���
	m_isGameClear = true;
	// �N���A���̏������s��
	GameClearUpdate();
}

void ObjectManager::GameClearUpdate()
{
	for (auto& obj : m_pObject)
	{
		// �X�e�[�W�N���A����
		obj->StageClear();
	}
}

void ObjectManager::GameEndUpdate()
{
	for (auto& obj : m_pObject)
	{
		// �I������
		obj->GameEnd();
	}
}
