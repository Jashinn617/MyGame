#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"

SceneMain::SceneMain()
{

	/*É|ÉCÉìÉ^ÇÃê∂ê¨*/
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
}

shared_ptr<SceneBase> SceneMain::Update(Input& input)
{
	m_pPlayer->Update(input);
	m_pCamera->Update(*m_pPlayer);

	return shared_from_this();
}

void SceneMain::Draw()
{

	m_pPlayer->Draw();

#ifdef _DEBUG
	// XYZé≤
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));
	DrawString(8, 8, "MainScene", 0xffffff);
#endif // DEBUG
}

void SceneMain::End()
{
}
