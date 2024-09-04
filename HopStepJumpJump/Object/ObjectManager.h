#pragma once
#include "../Util/Game.h"

#include <memory>
#include <list>
#include <functional>

class Input;
class EnemyBase;
class ItemBase;
class ObjectBase;
class Player;
class Field;
class Camera;
class EnemyManager;
class ItemManager;
class Collision;
class SkyDome;
class Time;
class ToonShader;
class ShadowMapShader;

class ObjectManager
{
public:
	ObjectManager(Game::Stage stage);
	virtual ~ObjectManager();

	void Update(Input& input);

	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g�̒ǉ�
	/// </summary>
	/// <typeparam name="T">ObjectBase���p�����^��</typeparam>
	/// <param name="pObj">���̃I�u�W�F�N�g��ǉ����邩</param>
	template <class T>
	void AddObject(T* pObj)
	{
		m_pObject.push_back(pObj);
		m_pObject.back()->SetMain(this);
	}

	/// <summary>
	/// �v���C���[�����݂��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsPlayerExist();

	/// <summary>
	/// �G�����݂��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsEnemyExist();

	/// <summary>
	/// �A�C�e�������݂��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsItemExist();

	/// <summary>
	/// �G�̐��̎擾
	/// </summary>
	/// <returns></returns>
	int GetItemNum()const;

	/// <summary>
	/// �Q�[�����N���A�������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsGameClear()const { return m_isGameClear; }

	bool IsGameEnd()const { return m_isGameEnd; }

	/// <summary>
	/// �Q�[�����I���������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsObjGameEnd();

	/// <summary>
	/// �v���C���[�|�C���^�̎擾
	/// </summary>
	/// <returns></returns>
	Player* const GetPlayer();

	/// <summary>
	/// �G�l�~�[�}�l�[�W���[�|�C���^�̎擾
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<EnemyManager> const GetEnemyManager() { return m_pEnemyManager; }

	/// <summary>
	/// �����I�ɃQ�[���N���A�ɂ���
	/// </summary>
	void SetGameClear();



private:	// �֐�
	/// <summary>
	/// �X�e�[�W�N���A���̍X�V����
	/// </summary>
	void GameClearUpdate();

	/// <summary>
	/// �Q�[���I�����̍X�V����
	/// </summary>
	void GameEndUpdate();

private:	// �ϐ�
	int m_H;
	bool m_isGameClear;		// �Q�[�����N���A������
	bool m_isGameEnd;		// �Q�[�����I��������ǂ���
	bool m_isGoal;			// �S�[���������ǂ���
	bool m_isTutorial;		// �`���[�g���A�����ǂ���

	std::shared_ptr<Collision> m_pCollision;	// �����蔻��
	std::shared_ptr<SkyDome> m_pSkyDome;		// �X�J�C�h�[��
	std::shared_ptr<EnemyManager> m_pEnemyManager;	// �G�l�~�[�}�l�[�W���[
	std::shared_ptr<ItemManager> m_pItemManager;	// �A�C�e���}�l�[�W���[
	std::shared_ptr<ToonShader> m_pToonShader;		// �g�D�[���V�F�[�_
	std::shared_ptr<ShadowMapShader> m_pShadowMapShader;	// �V���h�E�}�b�v
	std::list<ObjectBase*> m_pObject;		// �I�u�W�F�N�g
	std::shared_ptr<Time> m_gameEndTime;	// �Q�[���I�����Ă���̎���

};