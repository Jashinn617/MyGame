#pragma
#include "SceneBase.h"
#include "../Util/Game.h"

#include <list>
#include <array>

class StageSceneManager;

class SceneStage : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stage">�X�e�[�W�̎��</param>
	SceneStage(Game::Stage stage);

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
	virtual void End() override final;

	/// <summary>
	/// �X�e�[�W�̎�ނ̎擾
	/// </summary>
	/// <returns>�X�e�[�W�̎��</returns>
	virtual SceneKind GetSceneKind()  override final { return SceneKind::Stage; }

private:	// �֐�

	/// <summary>
	/// �I�v�V�����̕`��
	/// </summary>
	void DrawOption();

	/// <summary>
	/// �I�v�V�����̍X�V
	/// </summary>
	void UpdateOption();

private:	// �ϐ�
	int m_cursorCount;					// �I�v�V�������̃J�[�\���J�E���g
	bool m_isOption;					// �I�v�V��������
	bool m_isSceneEnd;					// �V�[�����I���������ǂ���
	std::array<int, 4> m_optionH;		// �I�v�V�����摜�n���h��
	std::array<float, 3> m_buttonSize;	// �{�^���T�C�Y
	Game::Stage m_stageKind;			// �X�e�[�W�̎��

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;	// �X�e�[�W�V�[���}�l�[�W���[�|�C���^
	std::shared_ptr<SceneBase> m_nextScene;						// ���̃V�[���̃|�C���^
};