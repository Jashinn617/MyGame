#pragma once
#include "SceneBase.h"

#include <array>
#include <string>

/// <summary>
/// �f�o�b�O��p�V�[��
/// �e�V�[���ɔ�ԃN���X
/// </summary>
class SceneDebug : public SceneBase
{
public:		// �񋓌^
	/// <summary>
	/// �V�[���̃^�C�v
	/// </summary>
	enum class SceneType
	{
		Debug,		// �f�o�b�O
		Test,		// �e�X�g
		Title,		// �^�C�g��
		Select,		// �Z���N�g
		Stage1,		// �X�e�[�W1
		Clear,		// �N���A
		GameOver,	// �Q�[���I�[�o�[

		SceneNum,	// �V�[����
	};

public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneDebug();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneDebug() {/*��������*/ }

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() override final {/*��������*/ }

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
	virtual void End() override final {/*��������*/ }

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns>�V�[���̎��</returns>
	virtual SceneKind GetSceneKind() override final { return SceneKind::Debug; }

private:	// �֐�
	/// <summary>
	/// �J�[�\���X�V
	/// </summary>
	void UpdateCursor();

	/// <summary>
	/// ���̃V�[���Ɉړ����鏈��
	/// </summary>
	/// <returns>���̃V�[��</returns>
	std::shared_ptr<SceneBase> MoveNextScene();

private:	// �ϐ�
	int m_cursorCount;		// �J�[�\���J�E���g
	std::array<std::string, static_cast<int>(SceneType::SceneNum)> m_sceneString;	// �V�[���ړ��p�Ɏg������
};

