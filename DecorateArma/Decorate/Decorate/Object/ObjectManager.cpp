#include "ObjectManager.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"

#include "../Shader/ToonShader.h"

ObjectManager::ObjectManager(Game::StageKind stageKind) :
	m_pCollision(std::make_shared<Collision>()),
	m_pToon(std::make_shared<ToonShader>())
	//m_pShadowMap(std::make_shared<ShadowMapShader>())
{
	// �I�u�W�F�N�g�̒ǉ�
	AddObject(new Player);
}

ObjectManager::~ObjectManager()
{
	// �I�u�W�F�N�g�|�C���^���
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pObject.erase(it);
	}
}

void ObjectManager::Update()
{
	// �I�u�W�F�N�g�z��̍ŏ��̃C�e���[�^���擾����
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		// �I�u�W�F�N�g�̍X�V
		auto obj = (*it);
		obj->Update();
		// �I�u�W�F�N�g�����݂��Ă��Ȃ��ꍇ
		if (!obj->GetInfo().isExist)
		{
			// �|�C���^���������
			delete obj;
			obj = nullptr;
			it = m_pObject.erase(it);
			// �C�e���[�^��i�߂�
			it++;
		}
		else
		{
			// �C�e���[�^��i�߂�
			it++;
		}
	}
}

void ObjectManager::Draw()
{
	// �J�����ʒu���Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();

	// �I�u�W�F�N�g�`��
	for (auto& obj : m_pObject)
	{
		// �J�����Ɉڂ��Ă��Ȃ����͕`�悵�Ȃ�
		if (!CheckCameraViewClip(obj->GetInfo().pos))
		{
			obj->Draw(m_pToon);
		}
	}

	// �J�����ʒu���Z�b�g
	GetPlayer()->GetCamera()->ResetCamera();

	// 2D�`��
	for (auto& obj : m_pObject)
	{
		obj->Draw2D();
	}
}

Player* const ObjectManager::GetPlayer()
{
	// �S�I�u�W�F�N�g���������ăv���C���[��������
	for (auto& obj : m_pObject)
	{
		if (obj->GetColType() != ObjectBase::ColType::Player) continue;

		return dynamic_cast<Player*>(obj);
	}

	return nullptr;
}