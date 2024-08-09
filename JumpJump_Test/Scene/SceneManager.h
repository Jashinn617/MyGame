#pragma once
#include <memory>

class SceneBase;
class Input;

/// <summary>
/// �V�[���J�ړ��A�e�V�[�����Ǘ����邽�߂̃N���X
/// </summary>
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	bool Update(Input& input);
	/// <summary>
	///	�`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void End();

private:	// �ϐ�
	std::shared_ptr<SceneBase> m_pScene;	// �`�悷��V�[���̃|�C���^

	float m_updateTime;		// �X�V�ɂ����鎞��
	float m_drawTime;		// �`��ɂ����鎞��
};
