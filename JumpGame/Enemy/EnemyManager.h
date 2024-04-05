#pragma once
#include <memory>
#include <vector>

using namespace std;

class EnemyBase;
class Player;
// �G�̃}�l�[�W���[
class EnemyManager final
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemyes();
	void DestroyEnemyes();

	void GetPlayer(shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	void Update();
	void Draw();

	bool CollisionPlayer();

private:
	// �G�̐�
	static constexpr int kEnemyNum = 10;

	vector<shared_ptr<EnemyBase>> m_pEnemy;
	shared_ptr<Player> m_pPlayer;

	int m_beeModelHandle;

};

