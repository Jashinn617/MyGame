#include "EnemyManager.h"
#include "DxLib.h"
#include "EnemyBase.h"
#include "EnemyBee.h"

namespace
{
	// 敵のスケール
	constexpr float kScale = 0.002f;
}


EnemyManager::EnemyManager():
	m_beeModelHandle(-1)
{
	m_beeModelHandle = MV1LoadModel("Data/Model/Enemy/BeeEnemy.mv1");

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemy[i] = make_shared<EnemyBee>(m_beeModelHandle);
	}
}

EnemyManager::~EnemyManager()
{
	// 処理無し
}

void EnemyManager::CreateEnemyes()
{
	

	// 敵の位置の初期化
	float band = 5.0f;
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemy[i]->SetPos(VGet(band * (i - kEnemyNum * 0.01), 0.3, -1.0f));
	}
}

void EnemyManager::DestroyEnemyes()
{
	MV1DeleteModel(m_beeModelHandle);
}

void EnemyManager::Update()
{
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != NULL)
		{
			enemy->Update();
		}
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != NULL)
		{
			enemy->Draw();
		}
	}
}
