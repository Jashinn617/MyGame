#include "SceneClear.h"
#include "SceneTitle.h"
#include "MainScene.h"
#include "DxLib.h"

SceneClear::SceneClear():
	m_clearLogoHandle(-1),
	m_continueLogoHandle(-1),
	m_endLogoHandle(-1),
	m_selectCursorHandle(-1),
	m_continueExtRate(kSmallContinueExtRate),
	m_endExtRate(kSmallEndExtRate),
	m_cursorSinPosX(0),
	m_cursorPosY(kContinuePosY),
	m_cursorSinCount(0),
	m_cursorCount(0)
{
	m_clearLogoHandle = LoadGraph("Data/Image/Logo/Clear.png");
	m_continueLogoHandle = LoadGraph("Data/Image/Logo/Continue.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End2.png");
	m_selectCursorHandle = LoadGraph("Data/Image/SelectCursor.png");
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_clearLogoHandle);
	DeleteGraph(m_continueLogoHandle);
	DeleteGraph(m_endLogoHandle);
	DeleteGraph(m_selectCursorHandle);
}

void SceneClear::Init()
{
}

shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	if (input.IsTriggered("up"))
	{
		m_cursorCount--;
	}
	else if (input.IsTriggered("down"))
	{
		m_cursorCount++;
	}

	if (m_cursorCount % 2 == 0)
	{
		m_cursorPosY = kContinuePosY;
		m_continueExtRate = kBigContinueExtRate;
		m_endExtRate = kSmallEndExtRate;
	}
	else if (m_cursorCount % 2 == 1)
	{
		m_cursorPosY = kEndPosY;
		m_continueExtRate = kSmallContinueExtRate;
		m_endExtRate = kBigEndExtRate;
	}

	// カーソルのアニメーション
	m_cursorSinCount += kCursorSinSpeed;
	m_cursorSinPosX = sinf(m_cursorSinCount) * kCursorAnimationSwing;

	if (input.IsTriggered("A"))
	{
		if (m_cursorCount % 2 == 0)
		{
			return make_shared<MainScene>();
		}
		else if (m_cursorCount % 2 == 1)
		{
			return make_shared<SceneTitle>();
		}
	}

	return shared_from_this();
}

void SceneClear::Draw()
{
	DrawRotaGraphF(kClearPosX, kClearPosY, kClearExtRate, 0.0, m_clearLogoHandle, true, false);
	DrawRotaGraphF(kContinuePosX, kContinuePosY, m_continueExtRate, 0.0, m_continueLogoHandle, true, false);
	DrawRotaGraphF(kEndPosX, kEndPosY, m_endExtRate, 0.0, m_endLogoHandle, true, false);

	float curosrX = kCursorPosX + m_cursorSinPosX;
	DrawRotaGraphF(curosrX, m_cursorPosY, kCursorExtRate, 0.0, m_selectCursorHandle, true, false);

#ifdef _DEBUG
	DrawString(0, 0, "Clear", 0xffffff);
	DrawFormatString(0, 50, 0xffffff, "Count：%d", m_cursorCount % 2);
#endif // _DEBUG
}

void SceneClear::End()
{
}
