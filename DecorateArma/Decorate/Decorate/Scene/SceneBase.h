#pragma once
#include "DxLib.h"

#include <memory>

/// <summary>
/// �e�V�[���̊��N���X
/// </summary>
class SceneBase: public std::enable_shared_from_this<SceneBase>
{
public:	// �񋓌^

	// �V�[���̎��
	enum class SceneKind
	{
		Debug,		// �f�o�b�O
		Title,		// �^�C�g��
		Select,		// �Z���N�g
		Stage,		// �X�e�[�W
		Clear,		// �N���A
		GameOver,	// �Q�[���I�[�o�[
	};

public:	// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneBase() {/*��������*/ }

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneBase(){/*��������*/ }

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���̃V�[��</returns>
	virtual std::shared_ptr<SceneBase> Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns>�V�[���̎��</returns>
	virtual SceneKind GetSceneKind() = 0;
};