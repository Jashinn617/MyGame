#pragma once
#include "../../Util/Game.h"

#include <vector>
#include <memory>
#include <array>

class SpownEnemy;
class ObjectManager;

class EnemyManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stage">�X�e�[�W�̎��</param>
	/// <param name="pObjectManager">�I�u�W�F�N�g�}�l�[�W���[</param>
	EnemyManager(Game::Stage stage, ObjectManager* pObjectManager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyManager();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	ObjectManager* m_pObjectManager;		// �I�u�W�F�N�g�}�l�[�W���[�|�C���^
	std::shared_ptr<SpownEnemy> m_pSpown;	// �X�|�[���G�l�~�[�|�C���^
};
