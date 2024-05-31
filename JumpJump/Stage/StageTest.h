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

	int m_wallNum;		// 壁ポリゴンだと判断されたポリゴンの数
	int m_floorNum;		// 床ポリゴンだと判断されたポリゴンの数

	MV1_COLL_RESULT_POLY* m_wall[kMaxHitColl];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存する配列
	MV1_COLL_RESULT_POLY* m_floor[kMaxHitColl];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存する配列

private:	// 定数
	static constexpr float kDefaultSize = 800.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ
	static constexpr float kHitWidth = 200.0f;		// 当たり判定のカプセルの横の半径
	static constexpr float kHitHeight = 700.0f;		// 当たり判定のカプセルの高さ
	static constexpr float kHitSlideLength = 5.0f;	// 一度の壁の押し出し処理でスライドさせる距離
	static constexpr int   kHitTryNum = 16;			// 壁の押し出し処理の最大試行回数

};

