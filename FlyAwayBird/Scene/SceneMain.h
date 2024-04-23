#pragma once
#include "SceneBase.h"

class Player;
class Camera;

/// <summary>
/// ���C���V�[���N���X
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:	// �ϐ�

	/*�|�C���^*/
	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
};

