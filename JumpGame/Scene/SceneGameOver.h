#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	~SceneGameOver();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	int m_gameOverLogoHandle;
	int m_continueLogoHandle;
	int m_endLogoHandle;
	int m_selectCursorHandle;
	int m_bgmHandle;
	int m_cursorMoveSeHandle;
	int m_startSeHandle;
	int m_endSeHandle;

	double m_continueExtRate;
	double m_endExtRate;

	float m_cursorSinCount;
	float m_cursorSinPosX;
	int m_cursorPosY;

	int m_cursorCount;

private:	// 定数
	static constexpr float kGameOverPosX = 800.0f;	// ゲームオーバーロゴのX位置
	static constexpr float kGameOverPosY = 250.0f;	// ゲームオーバーロゴのY位置
	static constexpr double kGameOverExtRate = 0.8;	// ゲームオーバーロゴの拡大率

	static constexpr float kContinuePosX = kGameOverPosX;	// コンテニューのX位置
	static constexpr float kContinuePosY = kGameOverPosY + 250.0f;	// コンテニューのX位置
	static constexpr double kSmallContinueExtRate = 0.5f;	// コンテニューの拡大率(通常時)
	static constexpr double kBigContinueExtRate = 0.55f;	// コンテニューの拡大率(拡大時)

	static constexpr float kEndPosX = kGameOverPosX;	// エンドのX位置
	static constexpr float kEndPosY = kContinuePosY + 200.0f;	// エンドのY位置
	static constexpr double kSmallEndExtRate = kSmallContinueExtRate;	// エンドの拡大率(通常時)
	static constexpr double kBigEndExtRate = kBigContinueExtRate;	// エンドの拡大率(拡大時)

	static constexpr float kCursorPosX = kGameOverPosX - 450.0f;	// カーソルのX位置
	static constexpr double kCursorExtRate = 0.15;	// カーソルの拡大率

	static constexpr float kCursorSinSpeed = 0.08f;	// カーソルの移動スピード
	static constexpr float kCursorAnimationSwing = 30.0f;	// カーソルの移動幅

	static constexpr int kBgmVolume = 130;	// BGMの音量
	static constexpr int kSeVolume = 255;	// SEの音量
};

