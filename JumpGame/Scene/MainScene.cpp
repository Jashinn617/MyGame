#include "MainScene.h"
#include "../Player.h"
#include "../Map.h"
#include "../Camera.h"
#include "../Enemy/EnemyManager.h"
#include "DxLib.h"

MainScene::MainScene():
	m_pPlayer(nullptr),
	m_time(0)
{
	// ポインタの生成
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	m_pMap = make_shared<Map>();
	m_pEnemy = make_shared<EnemyManager>();
	m_pEnemy->GetPlayer(m_pPlayer);
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	// マップのロード
	m_pMap->Load();

	// 敵の生成
	m_pEnemy->CreateEnemyes();
}

shared_ptr<SceneBase> MainScene::Update()
{
	m_pPlayer->Update();
	m_pMap->Update();
	m_pCamera->Update(*m_pPlayer);
	m_pEnemy->Update();

	m_time++;

#ifdef _DEBUG

	if (m_pEnemy->CollisionPlayer())
	{
		printfDx("当たった");
	}
#endif
	

	// シーン移動しないときは自身のポインタを返す
	return shared_from_this();
}

void MainScene::Draw()
{
	m_pMap->Draw();	
	m_pPlayer->Draw();
	m_pEnemy->Draw();

	DrawFormatString(100, 100, 0xffffff, "%d", m_time/60);
	
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