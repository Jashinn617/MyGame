#include "EnemyManager.h"
#include "EnemyBase.h"
#include "SpownEnemy.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

namespace
{
	// 敵データcsvファイルパス
	const char* const kCsvDataFile[static_cast<int>(Game::StageKind::StageNum)] =
	{
		"Data/File/Enemy/TestEnemySpown.csv",
		"Data/File/Enemy/Stage1EnemySpown.csv",
		"Data/File/Enemy/Stage2EnemySpown.csv"
	};
}


EnemyManager::EnemyManager(Game::StageKind stageKind, ObjectManager* pObjectManager):
	m_pObjectManager(pObjectManager)
{
	// ステージによって出現する敵を変える
	m_pSpown = std::make_shared<SpownEnemy>(kCsvDataFile[static_cast<int>(stageKind)], m_pObjectManager);
}

EnemyManager::~EnemyManager()
{
	/*処理無し*/
}

void EnemyManager::Init()
{
	// 敵を出現させる
	m_pSpown->Spown();
}

void EnemyManager::Update()
{
	/*処理無し*/
}

void EnemyManager::Draw()
{
	/*処理無し*/
}
