#pragma once
#include "SceneBase.h"
#include "DxLib.h"

class Player;
class Camera;
class Map;
class EnemyManager;
class Input;

/// <summary>
/// メインシーン
/// </summary>
class MainScene:public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	void BackDraw();

	VECTOR m_bgPos;	// 背景の表示位置
	int m_bgHandle;	// 背景画像
	int m_bgFrame;

	int m_time;

	int m_bgmHandle;


	struct BgSize	// 背景画像のサイズ
	{
		int width;
		int height;
	};

	/*ポインタの取得*/
	// プレイヤー
	shared_ptr<Player> m_pPlayer;
	// カメラ
	shared_ptr<Camera> m_pCamera;
	// マップ
	shared_ptr<Map> m_pMap;
	// 敵キャラクター
	shared_ptr<EnemyManager> m_pEnemy;

private:	// 定数
	static constexpr float kBgScale = 0.5f;		// 背景画像のスケールサイズ
	static constexpr float kBgSpeed = -1.0f;	// 背景の移動スピード

	/*背景の描画位置*/
	static constexpr float kBgPosX = 0.0f;
	static constexpr float kBgPosY = 0.0f;
	static constexpr float kBgPosZ = 200.0f;

	static constexpr int kBgmVolume = 130;	// BGMの音量
	static constexpr int kSeVolume = 255;	// SEの音量
};

