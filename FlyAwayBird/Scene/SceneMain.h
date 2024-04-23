#pragma once
#include "SceneBase.h"

class Player;
class Camera;

/// <summary>
/// メインシーンクラス
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

private:	// 変数

	/*ポインタ*/
	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
};

