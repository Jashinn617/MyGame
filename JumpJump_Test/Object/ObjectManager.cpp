#include "ObjectManager.h"
#include "../Object/ObjectBase.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"
#include "../Util/Input.h"
#include "../Util/Time.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"
#include "../Util/Collision.h"
#include "Model.h"

namespace
{	
	constexpr float kRotSpeed = 0.4f;	// ��]���x
	constexpr int kGameClearTime = 40;	// �S�[���ɂ��Ă��玟�̃V�[���Ɉڍs����܂ł̎���
}


ObjectManager::ObjectManager(Game::Stage stage):
	m_isGameClear(false),
	m_isGoal(false),
	m_isTutorial(false)
{
	m_pCollision = std::make_shared<Collision>();
	m_pSkyDome = std::make_shared<SkyDome>();
	m_pEnemyManager = std::make_shared<EnemyManager>(stage, this);

	AddObject(new Player);
}

ObjectManager::~ObjectManager()
{
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
	while (it!=m_pObject.end())
	{
		// �I�u�W�F�N�g�̍X�V
		auto obj = (*it);
		obj->Update(input);

		// �I�u�W�F�N�g�����݂��Ă��Ȃ��ꍇ
		if (!obj->GetInfo().isExist)
		{
			// ���݂������Ă���̎��Ԃ��J�E���g����
			if (!obj->IsExistCount())
			{
				it++;
				continue;
			}

			// �I�u�W�F�N�g���G�������ꍇ
			if (obj->GetColType() == ObjectBase::ColType::Enemy)
			{

			}
			// �I�u�W�F�N�g���A�C�e���������ꍇ
			if (obj->GetColType() == ObjectBase::ColType::Item)
			{

			}
			// �I�u�W�F�N�g���v���C���[�������ꍇ
			if (obj->GetColType() == ObjectBase::ColType::Player)
			{
				delete obj;
				obj = nullptr;
				it = m_pObject.erase(it);
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}

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

	// �G�l�~�[�}�l�[�W���[�̍X�V

	// �X�J�C�h�[���̍X�V
	m_pSkyDome->Update(GetPlayer()->GetInfo().pos);
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
		obj->Draw();
	}

	// �V���h�E�}�b�v�̏������݊J�n

	// �I��

	// �J�����̈ʒu�̃��Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();

	// �t�B�[���h�ɃV���h�E�}�b�v�𒣂�t���鏀��������

	// ��ƏI��

	// �X�e�[�W�N���A����2D�`������Ȃ�
	if (!m_isGameClear)
	{
		// �J�����̈ʒu�̃��Z�b�g
		GetPlayer()->GetCamera()->ResetCamera();
		for (auto& obj : m_pObject)
		{
			obj->Draw2D();
		}
		
	}

	// �J�����̈ʒu�̃��Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();
}

bool ObjectManager::IsPlayerExist()
{
	if (GetPlayer()->GetInfo().isExist) return true;
	return false;
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
	m_isGameClear = true;
	GameClearUpdate();
}

void ObjectManager::GameClearUpdate()
{
	for (auto& obj : m_pObject)
	{
		obj->StageClear();
	}
}
