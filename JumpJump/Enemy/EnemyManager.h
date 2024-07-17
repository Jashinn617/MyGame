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

private:	// �֐�

private:	// �ϐ�
	int m_beeModelHandle;		// �n�`��3D���f��
	int m_crabModelHandle;		// �J�j��3D���f��
	int m_ogreModelHandle;		// �I�j��3D���f��
	int m_skullModelHandle;		// �z�l��3D���f��

	std::vector<VECTOR> m_pos;

	std::vector<std::shared_ptr<EnemyBase>> m_pEnemy;
};

