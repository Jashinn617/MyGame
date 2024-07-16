#include "DxLib.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyBee.h"



EnemyManager::EnemyManager(int enemyNum):
	m_beeModelHandle(-1),
	m_crabModelHandle(-1),
	m_ogreModelHandle(-1),
	m_skullModelHandle(-1)
{
	// モデルのロード
	m_beeModelHandle = MV1LoadModel("Data/Model/Enemy/Bee.mv1");
	m_crabModelHandle = MV1LoadModel("Data/Model/Enemy/Crab.mv1");
	m_ogreModelHandle = MV1LoadModel("Data/Model/Enemy/Ogre.mv1");
	m_skullModelHandle = MV1LoadModel("Data/Model/Enemy/Skull.mv1");

	m_pEnemy.resize(1);
	m_pEnemy[0] = std::make_shared<EnemyBee>(m_beeModelHandle);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::CreateEnemyes()
{
	m_pEnemy[0]->SetPos(VGet(0, 40, 0));
}

void EnemyManager::DestroyEnemyes()
{
	// モデルのデリート
	MV1DeleteModel(m_beeModelHandle);
	MV1DeleteModel(m_crabModelHandle);
	MV1DeleteModel(m_ogreModelHandle);
	MV1DeleteModel(m_skullModelHandle);
}

void EnemyManager::Init()
{
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != nullptr)
		{
			enemy->Init();
		}
	}
}

void EnemyManager::Update()
{
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != nullptr)
		{
			enemy->Update();
		}
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != nullptr)
		{
			enemy->Draw();
		}
	}
}