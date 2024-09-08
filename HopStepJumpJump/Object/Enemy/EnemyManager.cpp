#include "EnemyManager.h"
#include "EnemyBase.h"
#include "SpownEnemy.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

namespace
{
	// �X�|�[���t�@�C����
	const char* const kSpownFile[static_cast<int>(Game::Stage::StageNum)] =
	{
		"Data/File/Enemy/TestEnemySpown.csv",
		"Data/File/Enemy/Stage1EnemySpown.csv",
		"Data/File/Enemy/Stage2EnemySpown.csv",
		"Data/File/Enemy/TestEnemySpown.csv"
	};
}


EnemyManager::EnemyManager(Game::Stage stage, ObjectManager* pObjectManager):
	m_isSpown(true),
	m_isClear(false),
	m_pObjectManager(pObjectManager)
{
	// ���x���ɂ���ďo������G��ς���
	m_pSpown = std::make_shared<SpownEnemy>(kSpownFile[static_cast<int>(stage)], m_pObjectManager);

	// �`���[�g���A�����͌ォ��G���o��
	if (stage == Game::Stage::Tutorial)
	{
		m_isSpown = false;
	}
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	m_pSpown->Spown();
}

void EnemyManager::Update()
{
	/*��������*/
}

void EnemyManager::Draw()
{
	/*��������*/
}
