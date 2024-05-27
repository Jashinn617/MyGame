#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class StageTest;

using namespace std;

/// <summary>
/// ���C���V�[���N���X
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�n���h��</param>
	virtual void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	/// <returns>�V�[���|�C���^</returns>
	virtual shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="handle">�n���h��</param>
	virtual void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	virtual void End();

private:

	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
	shared_ptr<StageTest> m_pStage;


private:

	void DrawGrid();
};