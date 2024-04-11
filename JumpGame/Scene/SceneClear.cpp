#include "SceneClear.h"
#include "SceneTitle.h"
#include "DxLib.h"

SceneClear::SceneClear():
	m_clearLogoHandle(-1),
	m_continueLogoHandle(-1),
	m_endLogoHandle(-1)
{
	m_clearLogoHandle = LoadGraph("Data/Image/Logo/Clear.png");
	m_continueLogoHandle = LoadGraph("Data/Image/Logo/Continue.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End2.png");
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_clearLogoHandle);
	DeleteGraph(m_continueLogoHandle);
	DeleteGraph(m_endLogoHandle);
}

void SceneClear::Init()
{
}

shared_ptr<SceneBase> SceneClear::Update()
{
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_O))
	{
		return make_shared<SceneTitle>();
	}
#endif


	return shared_from_this();
}

void SceneClear::Draw()
{
	DrawRotaGraphF(kClearPosX, kClearPosY, kClearExtRate, 0.0, m_clearLogoHandle, true, false);

#ifdef _DEBUG
	DrawString(0, 0, "Clear", 0xffffff);
#endif // _DEBUG
}

void SceneClear::End()
{
}
