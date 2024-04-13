#include "SceneTitle.h"
#include "MainScene.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_titleLogoHandle(-1),
	m_startLogoHandle(-1),
	m_endLogoHandle(-1),
	m_selectCursorHandle(-1),
	m_bgmHandle(-1),
	m_startExtRate(kSmallStartExtRate),
	m_endExtRate(kSmallEndExtRate),
	m_cursorSinPosX(0),
	m_cursorPosY(kStartPosY),
	m_cursorCount(0),
	m_cursorSinCount(0)
{
	m_titleLogoHandle = LoadGraph("Data/Image/Logo/Title.png");
	m_startLogoHandle = LoadGraph("Data/Image/Logo/Start.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End.png");
	m_selectCursorHandle = LoadGraph("Data/Image/SelectCursor.png");
	m_bgmHandle = LoadSoundMem("Data/Sound/BGM/Title.ogg");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogoHandle);
	DeleteGraph(m_startLogoHandle);
	DeleteGraph(m_endLogoHandle);
	DeleteGraph(m_selectCursorHandle);
	DeleteSoundMem(m_bgmHandle);
}

void SceneTitle::Init()
{
	// BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

shared_ptr<SceneBase> SceneTitle::Update(Input& input)
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
		m_cursorPosY = kStartPosY;
		m_startExtRate = kBigStartExtRate;
		m_endExtRate = kSmallEndExtRate;
	}
	else if (m_cursorCount % 2 == 1)
	{
		m_cursorPosY = kEndPosY;
		m_startExtRate = kSmallStartExtRate;
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
			DxLib_End();
		}
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
	DrawRotaGraphF(kTitlePosX, kTitlePosY, kTitleExtRate, 0.0, m_titleLogoHandle, true, false);
	DrawRotaGraphF(kStartPosX, kStartPosY, m_startExtRate, 0.0, m_startLogoHandle, true, false);
	DrawRotaGraphF(kEndPosX, kEndPosY, m_endExtRate, 0.0, m_endLogoHandle, true, false);

	float curosrX = kCursorPosX + m_cursorSinPosX;
	DrawRotaGraphF(curosrX, m_cursorPosY, kCursorExtRate, 0.0, m_selectCursorHandle, true, false);

#ifdef _DEBUG
	DrawString(0, 0, "Title", 0xffffff);
	DrawFormatString(0, 50, 0xffffff, "Count：%d", m_cursorCount % 2);
#endif	
}

void SceneTitle::End()
{
	// BGMの停止
	StopSoundMem(m_bgmHandle);
}
