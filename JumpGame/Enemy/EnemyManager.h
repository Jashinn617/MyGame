#pragma once
#include <memory>
#include <vector>

using namespace std;

class EnemyBase;
// 敵のマネージャー
class EnemyManager final
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemyes();
	void DestroyEnemyes();

	void Update();
	void Draw();

private:
	// 敵の数
	static constexpr int kEnemyNum = 10;

	vector<shared_ptr<EnemyBase>> m_pEnemy;

	int m_beeModelHandle;

};

