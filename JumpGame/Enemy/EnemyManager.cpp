#include "EnemyManager.h"
#include "DxLib.h"
#include "EnemyBase.h"
#include "EnemyBee.h"
#include "../Player.h"

namespace
{
	// ƒXƒP[ƒ‹ƒTƒCƒY
	constexpr float kScale = 0.002f;

	// YˆÊ’u
	constexpr float kPosYDown = 0.3f;	// ‰º‚Ì“G
	constexpr float kPosYUp = 0.6f;	// ã‚Ì“G

	// “G‚ÌŠÔŠu‚ğ•Ï‚¦‚é“G”
	constexpr int kEnemyDifficultyNum1 = 5;
	constexpr int kEnemyDifficultyNum2 = 10;
	constexpr int kEnemyDifficultyNum3 = 20;
	constexpr int kEnemyDifficultyNum4 = 40;
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
	// ˆ—–³‚µ
}

void EnemyManager::CreateEnemyes()
{
	// “G‚ÌˆÊ’u‚Ì‰Šú‰»
	float band = 10.0f;
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (i <= kEnemyDifficultyNum1)
		{
			m_pEnemy[i]->SetPos(VGet((i * 10), kPosYDown, -0.5f));
		}
		else if (i <= kEnemyDifficultyNum2)
		{
			m_pEnemy[i]->SetPos(VGet((i * 10), kPosYDown, -0.5f));
		}
		else if (i <= kEnemyDifficultyNum3)
		{
			m_pEnemy[i]->SetPos(VGet((i * 10), kPosYDown, -0.5f));
		}
		else if (i <= kEnemyDifficultyNum4)
		{
			m_pEnemy[i]->SetPos(VGet((i * 10), kPosYDown, -0.5f));
		}
		else
		{
			m_pEnemy[i]->SetPos(VGet((i  * 10), kPosYDown, -0.5f));
		}

		
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

bool EnemyManager::CollisionPlayer()
{
	VECTOR playerPos = m_pPlayer->GetPos();
	float playerRad = m_pPlayer->GetRad();
	for (auto& enemy : m_pEnemy)
	{
		VECTOR enemyPos=enemy->GetPos();
		float enemyRad=enemy->GetRad();

		float a = playerPos.x - enemyPos.x;
		float b = playerPos.y - enemyPos.y;
		float c = sqrtf((a * a) + (b * b));

		if (c <= playerRad + enemyRad)
		{
			return true;
		}

	}

	return false;
}

