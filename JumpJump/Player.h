#pragma once

class Input;
class Camera;
class Stage;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	enum class State : int
	{
		Idle = 0,
		Run = 1,
		Jump = 2,
	};

public:
	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera);
	void Draw();
	void End();

	const VECTOR& GetPos()const { return m_pos; }
	bool GetIsMove() const { return m_isMove; }
	State GetState()const { return m_state; }
	float GetJumpPower()const { return m_nowJunpPower; }

	void OnHitRoof();
	void OnHitFloor();
	void OnFall();


private:	// 変数
	VECTOR m_pos;			// 座標
	VECTOR m_targetDir;		// 向きたい方向のベクトル
	float m_angle;			// 向いている角度
	float m_nowJunpPower;		// ジャンプ時の現在の速度
	int m_modelHandle;		// モデルのハンドル

	State m_state;		// 現在の状態


	bool m_isMove;		// そのフレームで動いたかどうか
	


private:	// 定数
	static constexpr float kMoveSpeed = 1.0f;		// 移動速度
	static constexpr float kAngleSpeed = 0.2f;		// 回転速度
	static constexpr float kJunpPower = 3.0f;		// ジャンプ力
	static constexpr float kFallUpPower = 0.6f;		// 足を踏み外したときのジャンプ力
	static constexpr float kGravity = 3.0f;			// 重力

private:	// 関数

	void DisableRootFrameZMove();

	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	void Move(const VECTOR& moveVec);
	
	/// <summary>
	/// 回転制御
	/// </summary>
	void UpdateAngle();

};

