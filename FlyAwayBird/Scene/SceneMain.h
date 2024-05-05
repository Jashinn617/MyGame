#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class RecoveredItem;

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
	int m_backHandle;
	bool m_isStart;
	bool m_isPlay;
	bool m_isGoal;

	/*ポインタ*/
	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
	//shared_ptr<RecoveredItem> m_pItem;
	vector<shared_ptr<RecoveredItem>> m_pItem;

private:	 // 定数

	static constexpr float kWallZ = 30;				// z軸の壁
	static constexpr float kWallX = 50;				// x軸の壁
};

