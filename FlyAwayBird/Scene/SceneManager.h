#pragma once
#include <memory>

using namespace std;

class SceneBase;
class HandleManager;
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
	void Init(HandleManager& handle);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	void Update(Input& input, HandleManager& handle);
	/// <summary>
	///	�`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void Draw(HandleManager& handle);
	/// <summary>
	/// �I������
	/// </summary>
	void End();

private:	// �ϐ�
	shared_ptr<SceneBase> m_pScene;			// �`�悷��V�[���̃|�C���^
};
