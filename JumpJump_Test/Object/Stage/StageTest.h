#pragma once

class Player;

class StageTest
{
public:
	StageTest();
	~StageTest();

	void Init();

	void Draw();

	void End();

	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);

	int GetModelHandle() const { return -1; }

private:	// �֐�
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);

	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:	// �萔
	static constexpr int kMaxHitColl = 2048;	// ��������R���W�����|���S���̍ő吔

private:	// �ϐ�
	int m_modelHandle;	// ���f���n���h��
	int m_vs;			// ���_�V�F�[�_
	int m_ps;			// �s�N�Z���V�F�[�_

	int m_wallNum;		// �ǃ|���S�����Ɣ��f���ꂽ�|���S���̐�
	int m_floorNum;		// ���|���S�����Ɣ��f���ꂽ�|���S���̐�

	MV1_COLL_RESULT_POLY* m_wall[kMaxHitColl];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ�����z��
	MV1_COLL_RESULT_POLY* m_floor[kMaxHitColl];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ�����z��
};

