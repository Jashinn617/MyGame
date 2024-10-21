#pragma once

#include "../Utility/Game.h"

#include <memory>
#include <list>

class ObjectBase;
class Collision;
class Player;
class ToonShader;
class ShadowMapShader;

class ObjectManager
{
public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stageKind">�X�e�[�W�̎��</param>
	ObjectManager(Game::StageKind stageKind);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ObjectManager();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g�̒ǉ�
	/// </summary>
	/// <typeparam name="T">�I�u�W�F�N�g�x�[�X���p�������^</typeparam>
	/// <param name="pObj">�ǉ�����I�u�W�F�N�g</param>
	template <class T>
	void AddObject(T* pObj)
	{
		m_pObject.push_back(pObj);
		m_pObject.back()->SetObjectManager(this);
	}


	/// <summary>
	/// �v���C���[�|�C���^�̎擾
	/// </summary>
	/// <returns>�v���C���[�|�C���^</returns>
	Player* const GetPlayer();

	

private:	// �ϐ�

	std::shared_ptr<Collision> m_pCollision;		// �����蔻��
	std::shared_ptr<ToonShader> m_pToon;			// �g�D�[���V�F�[�_
	//std::shared_ptr<ShadowMapShader> m_pShadowMap;	// �V���h�E�}�b�v�V�F�[�_

	std::list<ObjectBase*> m_pObject;				// �I�u�W�F�N�g
};

