#pragma once

class Input;
class Player;
class StageTest;

class Camera
{
public:
	void Init();
	void Update(const Input& input, const Player& player, const StageTest& stage);


private:	// 変数
	float m_angle;		// 水平角度
	VECTOR m_pos;		// 座標
	VECTOR m_targetpos;	// ターゲット座標

private:	// 定数
	static constexpr float kSpeed = 0.5f;			// 回転速度
	static constexpr float kTargetH = 400.0f;		// ターゲットの座標から注視点までの高さ
	static constexpr float kStartTargetDir = 1600.0f;	// ターゲットとの初期の距離
	static constexpr float kColSize = 50.0f;		// カメラ自体の当たり判定のサイズ

};

