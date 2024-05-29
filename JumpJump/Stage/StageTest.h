#pragma once

class Player;

class StageTest
{
public:
	StageTest();
	~StageTest();

	int GetModelHandle() const { return -1; }

	void Init();

	void Draw();

	void End();

	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);

private:	// �֐�
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);

	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:	// �ϐ�
	int m_wallNum;		// �ǃ|���S�����Ɣ��f���ꂽ�|���S���̐�
	int m_floorNum;		// ���|���S�����Ɣ��f���ꂽ�|���S���̐�


private:	// �萔

};

