#pragma once
#include <memory>
#include <vector>

using namespace std;

class EnemyBase;
// �G�̃}�l�[�W���[
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
	// �G�̐�
	static constexpr int kEnemyNum = 10;

	vector<shared_ptr<EnemyBase>> m_pEnemy;

	int m_beeModelHandle;

};

