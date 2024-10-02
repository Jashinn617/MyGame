#pragma once
#include <memory>

class SceneBase;

/// <summary>
/// �V�[���J�ړ��A�e�V�[�����Ǘ����邽�߂̃N���X
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneManager();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	bool Update();

	/// <summary>
	///	�`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

private:	// �ϐ�
	float m_updateTime;		// �X�V�ɂ����鎞��
	float m_drawTime;		// �`��ɂ����鎞��

	std::shared_ptr<SceneBase> m_pScene;	// �`�悷��V�[���̃|�C���^
};
