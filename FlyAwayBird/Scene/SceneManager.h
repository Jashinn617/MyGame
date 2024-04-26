#pragma once
#include <memory>

using namespace std;

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
	///  ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	void Update(Input& input);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �Q�[���I�����̏���
	/// </summary>
	void End();

private:	// �ϐ�
	shared_ptr<SceneBase> m_pScene;			// �`�悷��V�[���̃|�C���^
};
