#include "MainScene.h"
#include "../Player.h"
#include "../Map.h"
#include "../Camera.h"
#include "../Enemy/EnemyManager.h"

#include "SceneGameOver.h"
#include "SceneClear.h"

MainScene::MainScene():
	m_bgPos{kBgPosX,kBgPosY,kBgPosZ},
	m_pPlayer(nullptr),
	m_time(0),
	m_bgFrame(0),
	m_bgImg(-1)
{
	// ポインタの生成
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	m_pMap = make_shared<Map>();
	m_pEnemy = make_shared<EnemyManager>();
	m_pEnemy->GetPlayer(m_pPlayer);

	m_bgImg = LoadGraph("Data/Image/Background/StageBg.png");
}

MainScene::~MainScene()
{
	DeleteGraph(m_bgImg);
}

void MainScene::Init()
{
	// マップのロード
	m_pMap->Load();

	// 敵の生成
	m_pEnemy->CreateEnemyes();
}

shared_ptr<SceneBase> MainScene::Update(Input& input)
{
	m_pPlayer->Update(input);
	m_pMap->Update();
	m_pCamera->Update(*m_pPlayer);
	m_pEnemy->Update();

	m_time++;
	m_bgPos = VAdd(m_bgPos, VGet(kBgSpeed, 0.0f, 0.0f));

	

#ifdef _DEBUG
	if (input.IsTriggered("Y"))
	{
		return make_shared<SceneGameOver>();
	}
	else if (input.IsTriggered("X"))
	{
		return make_shared<SceneClear>();
	}
#endif

	if (m_pEnemy->CollisionPlayer())
	{
		return make_shared<SceneGameOver>();
	}
	

	// シーン移動しないときは自身のポインタを返す
	return shared_from_this();
}

void MainScene::Draw()
{
	BackDraw();
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

void MainScene::BackDraw()
{
	// 画像サイズの取得
	BgSize bgSize;
	GetGraphSize(m_bgImg, &bgSize.width, &bgSize.height);

	// スクロール量の計算
	int scrollBg = static_cast<int>(m_bgPos.x * 0.3f) % static_cast<int>(bgSize.width * kBgScale);

	// 背景の描画
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph3D(scrollBg + i * bgSize.width * kBgScale,
			m_bgPos.y,
			m_bgPos.z,
			kBgScale,
			0.0f,
			m_bgImg,
			true);
	}
}
