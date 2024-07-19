#pragma once

class Input;
class Player;
class StageTest;

class Camera
{
public:

	Camera();
	~Camera();

	void Init();
	void Update(const Input& input, const Player& player, const StageTest& stage);

	const VECTOR& GetPos()const { return m_pos; }
	const VECTOR& GetTarget()const { return m_targetPos; }

private:	// 変数
	float m_angle;		// 水平角度
	VECTOR m_pos;		// 座標
	VECTOR m_targetPos;	// ターゲット座標
};

