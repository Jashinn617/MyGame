#include "MainScene.h"
#include "../Player.h"
#include "../Map.h"
#include "../Camera.h"
#include "DxLib.h"

MainScene::MainScene():
	m_pPlayer(nullptr)
{
	// ポインタの生成
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	m_pMap = make_shared<Map>();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	// マップのロード
	m_pMap->Load();
}

shared_ptr<SceneBase> MainScene::Update()
{
	m_pPlayer->Update();
	m_pMap->Update();
	m_pCamera->Update(*m_pPlayer);

	// シーン移動しないときは自身のポインタを返す
	return shared_from_this();
}

void MainScene::Draw()
{
	m_pMap->Draw();	
	m_pPlayer->Draw();

	// デバッグ描画
#ifdef _DEBUG
		// XYZ軸
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

	DrawString(8, 8, "MainScene", 0xffffff);
#endif // DEBUG

	
}

void MainScene::End()
{
}
