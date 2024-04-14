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

	int m_noticeLogoHandle1;
	int m_noticeLogoHandle2;
	int m_noticeLogoHandle3;
	int m_noticeLogoHandle4;

	int m_tutorialHandle;

	int m_timeFrame;
	int m_time;

	int m_bgmHandle;
	int m_clearSeHandle;
	int m_noticeSeHandle;
	int m_missSeHandle;


	int m_timeFontHandle;
	int m_timeBackFontHandle;

	int m_blinkingNoticeFrame;	// 秒数通知の点滅フレーム
	bool m_isNotice;	// 秒数通知が表示されているか

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

	static constexpr int kScreenWidth = 1600;	// 画面の横サイズ
	static constexpr int kScreenHeight = 900;	// 画面の縦サイズ

	static constexpr int kFadeSpeed = 3;	// フェードのスピード

	static constexpr int kNoticeBlinkingSpeed = 30;	// 秒数通知の点滅速度
	static constexpr int kNoticeBlinkingFrequency = 20; // 秒数通知の点滅頻度

	/*秒数通知の描画位置*/
	static constexpr float kNoticePosX = 850;	// X位置
	static constexpr float kNoticePosY = 400;	// Y位置
	static constexpr double kNoticeExtRate = 0.3;	// 拡大率

	/*秒数の表示位置*/
	static constexpr int kTimePosX = 750;
	static constexpr int kTimePosY = 80;

	/*秒数通知をする間隔*/
	static constexpr int kTimeInterval1 = 20;
	static constexpr int kTimeInterval2 = kTimeInterval1 + 20;
	static constexpr int kTimeInterval3 = kTimeInterval2 + 20;
	static constexpr int kTimeInterval4 = kTimeInterval3 + 20;

	/*秒数通知を表示する秒数*/
	static constexpr int kNoticeDisplayTime = 3;

	static constexpr int kClearTime = 90;	// クリアタイム

};

