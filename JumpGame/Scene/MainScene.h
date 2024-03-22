#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class Map;

/// <summary>
/// メインシーン
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

	/*ポインタの取得*/
	// プレイヤー
	shared_ptr<Player> m_pPlayer;
	// カメラ
	shared_ptr<Camera> m_pCamera;
	// マップ
	shared_ptr<Map> m_pMap;
};

