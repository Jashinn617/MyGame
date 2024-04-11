#include "SceneTitle.h"
#include "MainScene.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_titleLogoHandle(-1),
	m_startLogoHandle(-1),
	m_endLogoHandle(-1),
	m_selectCursorHandle(-1),
	m_startExtRate(kSmallStartExtRate),
	m_endExtRate(kSmallEndExtRate),
	m_cursorPosY(kStartPosY),
	m_cursorCount(0)
{
	m_titleLogoHandle = LoadGraph("Data/Image/Logo/Title.png");
	m_startLogoHandle = LoadGraph("Data/Image/Logo/Start.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End.png");
	m_selectCursorHandle = LoadGraph("Data/Image/SelectCursor.png");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogoHandle);
	DeleteGraph(m_startLogoHandle);
	DeleteGraph(m_endLogoHandle);
	DeleteGraph(m_selectCursorHandle);
}

void SceneTitle::Init()
{
	m_cursorCount = 0;
}

shared_ptr<SceneBase> SceneTitle::Update()
{
	if (CheckHitKeyAll())
	{
		return make_shared<MainScene>();
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
	DrawRotaGraphF(kTitlePosX, kTitlePosY, kTitleExtRate, 0.0, m_titleLogoHandle, true, false);
	DrawRotaGraphF(kStartPosX, kStartPosY, m_startExtRate, 0.0, m_startLogoHandle, true, false);
	DrawRotaGraphF(kEndPosX, kEndPosY, m_endExtRate, 0.0, m_endLogoHandle, true, false);
	DrawRotaGraphF(kCursorPosX, m_cursorPosY, kCursorExtRate, 0.0, m_selectCursorHandle, true, false);

#ifdef _DEBUG
	DrawString(0, 0, "Title", 0xffffff);
#endif	
}

void SceneTitle::End()
{
}
