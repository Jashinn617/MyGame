#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>

class EnemyBase;

class EnemyManager
{
public:
	EnemyManager(int enemyNum);
	~EnemyManager();

	void CreateEnemyes();
	void DestroyEnemyes();

	void Init();
	void Update();
	void Draw();

private:	// 関数

private:	// 変数
	int m_beeModelHandle;		// ハチの3Dモデル
	int m_crabModelHandle;		// カニの3Dモデル
	int m_ogreModelHandle;		// オニの3Dモデル
	int m_skullModelHandle;		// ホネの3Dモデル

	std::vector<VECTOR> m_pos;

	std::vector<std::shared_ptr<EnemyBase>> m_pEnemy;
};

