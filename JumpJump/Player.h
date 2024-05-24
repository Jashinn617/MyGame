#pragma once

class Input;
class Camera;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera);
	void Draw();
	void End();

	const VECTOR GetPos()const { return m_pos; }


private:	// 変数
	VECTOR m_pos;			// 座標
	VECTOR m_targetDir;		// 向いている方向のベクトル
	float m_angle;			// 向いている角度
	float m_currentJunpPower;		// ジャンプする際の速度
	int m_modelHandle;		// モデルのハンドル
	


private:	// 定数
	static constexpr float kSpeed = 30.0f;			// 移動速度
	static constexpr float kJunpPower = 100.0f;		// ジャンプ力
	static constexpr float kGravity = 3.0f;			// 重力

private:	// 関数
	
	/// <summary>
	/// 回転制御
	/// </summary>
	void UpdateAngle();

};

