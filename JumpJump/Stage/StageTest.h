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

private:	// 関数
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);

	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:	// 定数
	static constexpr int kMaxHitColl = 2048;	// 処理するコリジョンポリゴンの最大数

private:	// 変数
	int m_modelHandle;	// モデルハンドル
	int m_vs;			// 頂点シェーダ
	int m_ps;			// ピクセルシェーダ

	int m_wallNum;		// 壁ポリゴンだと判断されたポリゴンの数
	int m_floorNum;		// 床ポリゴンだと判断されたポリゴンの数

	MV1_COLL_RESULT_POLY* m_wall[kMaxHitColl];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存する配列
	MV1_COLL_RESULT_POLY* m_floor[kMaxHitColl];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存する配列
};

