#include "DxLib.h"
#include "SceneTitle.h"
#include "../Util/Input.h"

#include "../Object/SkyDome.h"
#include "../Object/Camera.h"

SceneTitle::SceneTitle()
{
	m_pSky = std::make_shared<SkyDome>();
	m_pCamera = std::make_shared<Camera>();
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_pCamera->Update(VGet(0, 0, 0));
	m_pSky->Update(VGet(0, 0, 0));

	return shared_from_this();
}

void SceneTitle::Draw()
{
	m_pSky->Draw();
	m_pCamera->Draw();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG   
}

void SceneTitle::End()
{
}
