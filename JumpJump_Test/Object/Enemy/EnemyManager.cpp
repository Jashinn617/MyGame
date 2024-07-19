#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyBee.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>


EnemyManager::EnemyManager(int enemyNum):
	m_beeModelHandle(-1),
	m_crabModelHandle(-1),
	m_ogreModelHandle(-1),
	m_skullModelHandle(-1)
{
	// モデルのロード
	m_beeModelHandle = MV1LoadModel("Data/Model/Enemy/Bee.mv1");
	assert(m_beeModelHandle != -1);
	m_crabModelHandle = MV1LoadModel("Data/Model/Enemy/Crab.mv1");
	assert(m_crabModelHandle != -1);
	m_ogreModelHandle = MV1LoadModel("Data/Model/Enemy/Ogre.mv1");
	assert(m_ogreModelHandle != -1);
	m_skullModelHandle = MV1LoadModel("Data/Model/Enemy/Skull.mv1");
	assert(m_skullModelHandle != -1);

	// 敵のポインタの設定
	m_pEnemy.resize(enemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<EnemyBee>(m_beeModelHandle);
	}
	
}

EnemyManager::~EnemyManager()
{
	/*処理無し*/
}

void EnemyManager::CreateEnemyes()
{
	// ファイルの読み込み
	std::ifstream file;
	file.open("Data/File/Enemy/EnemyPosTest.csv");
	assert(file.is_open());

	// 読み取り元
	std::string path;
	while (std::getline(file, path))
	{
		std::istringstream istream(path);
		std::string line;
		VECTOR pos = VGet(0.0f, 0.0f, 0.0f);

		if (std::getline(istream, line, ',') &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.x) &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.y) &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.z))
		{
			// 位置をm_posに入れる
			m_pos.push_back(pos);
		}
	}
	file.close();

	// 変数の代入
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->SetPos(m_pos[i]);
	}	
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