#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	int m_titleLogoHandle;
	int m_startLogoHandle;
	int m_endLogoHandle;
	int m_selectCursorHandle;

	double m_startExtRate;
	double m_endExtRate;

	int m_cursorPosY;

	int m_cursorCount;

private: // 定数
	static constexpr float kTitlePosX = 800.0f;	// タイトルのX位置
	static constexpr float kTitlePosY = 250.0f;	// タイトルのY位置
	static constexpr double kTitleExtRate = 0.5;	// タイトルの拡大率

	static constexpr float kStartPosX = 800.0f;	// スタートのX位置
	static constexpr float kStartPosY = kTitlePosY + 300.0f;	// スタートのY位置
	static constexpr double kSmallStartExtRate = 0.3;	// スタートの拡大率(通常時)
	static constexpr double kBigStartExtRate = 0.5;	// スタートの拡大率(拡大時)

	static constexpr float kEndPosX = 800.0f;	// エンドのX位置
	static constexpr float kEndPosY = kStartPosY + 200.0f;	// エンドのY位置
	static constexpr double kSmallEndExtRate = 0.3;	// エンドの拡大率(通常時)
	static constexpr double kBigEndExtRate = 0.5;	// エンドの拡大率(拡大時)

	static constexpr float kCursorPosX = 500.0f;	// カーソルのX位置
	static constexpr double kCursorExtRate = 0.15;	// カーソルの拡大率


};

