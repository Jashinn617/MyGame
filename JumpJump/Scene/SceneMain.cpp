#include "DxLib.h"
#include "SceneMain.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Stage/StageTest.h"

/// <summary>
/// 定数定義
/// </summary>
namespace
{

}

SceneMain::SceneMain():
	m_pPlayer(nullptr),
	m_pCamera(nullptr)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	m_pStage = make_shared<StageTest>();

	m_pStage->Init();
	m_pPlayer->Init();
	m_pCamera->Init();

	// ライトの設定
	ChangeLightTypeDir(VGet(0.0f, -0.5f, 0.0f));

}

shared_ptr<SceneBase> SceneMain::Update(Input& input)
{
	m_pPlayer->Update(input, *m_pCamera, *m_pStage);
	m_pCamera->Update(input, *m_pPlayer, *m_pStage);


	return shared_from_this();
}

void SceneMain::Draw()
{
	m_pStage->Draw();
	m_pPlayer->Draw();

	DrawGrid();

}

void SceneMain::End()
{
}

void SceneMain::DrawGrid()
{
#ifdef _DEBUG
	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
#endif // _DEBUG
}