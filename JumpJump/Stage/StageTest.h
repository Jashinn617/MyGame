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

private:	// ŠÖ”
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);

	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:	// •Ï”
	int m_wallNum;		// •Çƒ|ƒŠƒSƒ“‚¾‚Æ”»’f‚³‚ê‚½ƒ|ƒŠƒSƒ“‚Ì”
	int m_floorNum;		// °ƒ|ƒŠƒSƒ“‚¾‚Æ”»’f‚³‚ê‚½ƒ|ƒŠƒSƒ“‚Ì”


private:	// ’è”

};

