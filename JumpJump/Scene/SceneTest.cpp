#include "DxLib.h"
#include "SceneTest.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Stage/StageTest.h"
#include "../Enemy/EnemyManager.h"

/// <summary>
/// 定数定義
/// </summary>
namespace
{

}

SceneTest::SceneTest():
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_back(-1)
{
}

SceneTest::~SceneTest()
{
	DeleteGraph(m_back);
}

void SceneTest::Init()
{
	m_pPlayer = make_shared<Player>();
	m_pCamera = make_shared<Camera>();
	m_pStage = make_shared<StageTest>();
	m_pEnemy = make_shared<EnemyManager>(1);

	m_pStage->Init();
	m_pPlayer->Init();
	m_pCamera->Init();

	// 敵の生成
	m_pEnemy->CreateEnemyes();
	m_pEnemy->Init();

	// ライトの設定
	ChangeLightTypeDir(VGet(0.0f, 10.0f, 0.0f));

	m_back = LoadGraph("Data/img/Sky.png");

}

shared_ptr<SceneBase> SceneTest::Update(Input& input)
{
	m_pPlayer->Update(input, *m_pCamera, *m_pStage);
	m_pCamera->Update(input, *m_pPlayer, *m_pStage);
	m_pEnemy->Update();


	return shared_from_this();
}

void SceneTest::Draw()
{
	DrawGraph(0, 0, m_back, false);

	m_pStage->Draw();
	m_pPlayer->Draw();
	m_pEnemy->Draw();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Test");
	DrawGrid();
#endif // _DEBUG
}

void SceneTest::End()
{
	m_pEnemy->DestroyEnemyes();
}

void SceneTest::DrawGrid()
{
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
}