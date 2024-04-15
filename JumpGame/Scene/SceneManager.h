#pragma once
#include <memory>

using namespace std;

class SceneBase;
class Input;

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

private:
	shared_ptr<SceneBase> m_pScene;			// �`�悷��V�[���̃|�C���^
};

