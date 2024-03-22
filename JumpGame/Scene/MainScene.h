#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class Map;

/// <summary>
/// ���C���V�[��
/// </summary>
class MainScene:public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:

	/*�|�C���^�̎擾*/
	// �v���C���[
	shared_ptr<Player> m_pPlayer;
	// �J����
	shared_ptr<Camera> m_pCamera;
	// �}�b�v
	shared_ptr<Map> m_pMap;
};

