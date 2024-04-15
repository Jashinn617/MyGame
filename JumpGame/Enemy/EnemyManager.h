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
	vector<shared_ptr<EnemyBase>> m_pEnemy;
	shared_ptr<Player> m_pPlayer;

	int m_beeModelHandle;
	int m_crabModelHandle;
	int m_skullModelHandle;

private:	// �萔
	static constexpr int kEnemyNum = 90;		// �G�̐�
	static constexpr float kScale = 0.002f;		// �T�C�Y

	static constexpr int kEnemyChangeNum1 = 20;
	static constexpr int kEnemyChangeNum2 = 50;
	static constexpr int kEnemyChangeNum3 = 90;

	/*X�ʒu*/
	static constexpr float kPosX0 = 8.0f;
	static constexpr float kPosX1 = kPosX0 + 8.0f;
	static constexpr float kPosX2 = kPosX1 + 8.0f;
	static constexpr float kPosX3 = kPosX2 + 6.0f;
	static constexpr float kPosX4 = kPosX3 + 3.0f;
	static constexpr float kPosX5 = kPosX4 + 3.0f;
	static constexpr float kPosX6 = kPosX5 + 3.0f;
	static constexpr float kPosX7 = kPosX6 + 2.0f;
	static constexpr float kPosX8 = kPosX7 + 1.0f;
	static constexpr float kPosX9 = kPosX8 + 1.0f;
	static constexpr float kPosX10 = kPosX9 + 1.0f;
	static constexpr float kPosX11 = kPosX10 + 1.0f;
	static constexpr float kPosX12 = kPosX11 + 1.0f;
	static constexpr float kPosX13 = kPosX12 + 2.5f;
	static constexpr float kPosX14 = kPosX13 + 2.5f;
	static constexpr float kPosX15 = kPosX14 + 3.0f;
	static constexpr float kPosX16 = kPosX15 + 3.0f;
	static constexpr float kPosX17 = kPosX16 + 3.5f;
	static constexpr float kPosX18 = kPosX17 + 2.5f;
	static constexpr float kPosX19 = kPosX18 + 2.5f;
	static constexpr float kPosX20 = kPosX19 + 5.0f;
	static constexpr float kPosX21 = kPosX20 + 6.0f;
	static constexpr float kPosX22 = kPosX21 + 3.5f;
	static constexpr float kPosX23 = kPosX22 + 2.5f;
	static constexpr float kPosX24 = kPosX23 + 2.0f;
	static constexpr float kPosX25 = kPosX24 + 2.5f;
	static constexpr float kPosX26 = kPosX25 + 3.5f;
	static constexpr float kPosX27 = kPosX26 + 2.5f;
	static constexpr float kPosX28 = kPosX27 + 2.5f;
	static constexpr float kPosX29 = kPosX28 + 2.5f;
	static constexpr float kPosX30 = kPosX29 + 2.5f;
	static constexpr float kPosX31 = kPosX30 + 2.5f;
	static constexpr float kPosX32 = kPosX31 + 2.5f;
	static constexpr float kPosX33 = kPosX32 + 2.5f;
	static constexpr float kPosX34 = kPosX33 + 2.5f;
	static constexpr float kPosX35 = kPosX34 + 2.5f;
	static constexpr float kPosX36 = kPosX35 + 2.5f;
	static constexpr float kPosX37 = kPosX36 + 5.5f;
	static constexpr float kPosX38 = kPosX37 + 2.5f;
	static constexpr float kPosX39 = kPosX38 + 2.5f;
	static constexpr float kPosX40 = kPosX39 + 6.0f;
	static constexpr float kPosX41 = kPosX40 + 2.0f;
	static constexpr float kPosX42 = kPosX41 + 2.0f;
	static constexpr float kPosX43 = kPosX42 + 2.0f;
	static constexpr float kPosX44 = kPosX43 + 2.0f;
	static constexpr float kPosX45 = kPosX44 + 2.0f;
	static constexpr float kPosX46 = kPosX45 + 2.0f;
	static constexpr float kPosX47 = kPosX46 + 2.0f;
	static constexpr float kPosX48 = kPosX47 + 2.0f;
	static constexpr float kPosX49 = kPosX48 + 2.0f;
	static constexpr float kPosX50 = kPosX49 + 2.0f;
	static constexpr float kPosX51 = kPosX50 + 6.0f;
	static constexpr float kPosX52 = kPosX51 + 2.0f;
	static constexpr float kPosX53 = kPosX52 + 2.0f;
	static constexpr float kPosX54 = kPosX53 + 3.5f;
	static constexpr float kPosX55 = kPosX54 + 2.0f;
	static constexpr float kPosX56 = kPosX55 + 2.0f;
	static constexpr float kPosX57 = kPosX56 + 2.0f;
	static constexpr float kPosX58 = kPosX57 + 2.0f;
	static constexpr float kPosX59 = kPosX58 + 2.5f;
	static constexpr float kPosX60 = kPosX59 + 2.0f;
	static constexpr float kPosX61 = kPosX60 + 2.5f;
	static constexpr float kPosX62 = kPosX61 + 2.0f;
	static constexpr float kPosX63 = kPosX62 + 2.0f;
	static constexpr float kPosX64 = kPosX63 + 2.0f;
	static constexpr float kPosX65 = kPosX64 + 2.0f;
	static constexpr float kPosX66 = kPosX65 + 2.0f;
	static constexpr float kPosX67 = kPosX66 + 2.0f;
	static constexpr float kPosX68 = kPosX67 + 2.0f;
	static constexpr float kPosX69 = kPosX68 + 2.5f;
	static constexpr float kPosX70 = kPosX69 + 2.0f;
	static constexpr float kPosX71 = kPosX70 + 2.5f;
	static constexpr float kPosX72 = kPosX71 + 2.5f;
	static constexpr float kPosX73 = kPosX72 + 5.5f;
	static constexpr float kPosX74 = kPosX73 + 3.0f;
	static constexpr float kPosX75 = kPosX74 + 2.0f;
	static constexpr float kPosX76 = kPosX75 + 2.0f;
	static constexpr float kPosX77 = kPosX76 + 5.0f;
	static constexpr float kPosX78 = kPosX77 + 2.0f;
	static constexpr float kPosX79 = kPosX78 + 3.0f;
	static constexpr float kPosX80 = kPosX79 + 2.5f;
	static constexpr float kPosX81 = kPosX80 + 2.5f;
	static constexpr float kPosX82 = kPosX81 + 10.0f;
	static constexpr float kPosX83 = kPosX82 + 2.5f;
	static constexpr float kPosX84 = kPosX83 + 2.5f;
	static constexpr float kPosX85 = kPosX84 + 3.0f;
	static constexpr float kPosX86 = kPosX85 + 2.0f;
	static constexpr float kPosX87 = kPosX86 + 3.5f;
	static constexpr float kPosX88 = kPosX87 + 2.0f;
	static constexpr float kPosX89 = kPosX88 + 3.5f;
	static constexpr float kPosX90 = kPosX89 + 2.5f;

	/*Y�ʒu*/
	static constexpr float kPosYDown = 0.3f;	// ���̓G
	static constexpr float kPosYUp = 1.2f;		// ��̓G

	static constexpr float kPosZ = -0.5f;		// Z�ʒu

};

