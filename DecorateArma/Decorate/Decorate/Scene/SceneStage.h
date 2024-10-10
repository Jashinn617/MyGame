#pragma once
#include "SceneBase.h"

#include "../Utility/Game.h"

#include <list>
#include <array>

class StageManager;

/// <summary>
/// �X�e�[�W�V�[���N���X
/// </summary>
class SceneStage : public SceneBase
{
public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stage">�X�e�[�W�̎��</param>
	SceneStage(Game::StageKind stage);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneStage();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() override final;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���̃V�[��</returns>
	virtual std::shared_ptr<SceneBase> Update() override final;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() override final;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void End() override final {/*��������*/ };

	/// <summary>
	/// �X�e�[�W�̎�ނ̎擾
	/// </summary>
	/// <returns>�X�e�[�W�̎��</returns>
	virtual SceneKind GetSceneKind() override final { return SceneKind::Stage; }

private:	// �ϐ�
	Game::StageKind m_stageKind;					// �X�e�[�W�̎��

	std::shared_ptr<StageManager> m_pStageManager;	// �X�e�[�W�}�l�[�W���[�|�C���^
	std::shared_ptr<SceneBase> m_pNextScene;		// ���̃V�[���̃|�C���^
};