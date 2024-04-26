#pragma once

class Input;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update(Input& input);
	void Draw()const;

	/// <summary>
	/// 位置の取得
	/// </summary>
	/// <returns>現在位置</returns>
	const VECTOR GetPos()const { return m_pos; }

	/// <summary>
	/// 半径の取得
	/// </summary>
	/// <returns>半径</returns>
	const float GetRadius()const { return kRadius; }

private:	// 関数
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="input">入力</param>
	void Move(Input& input);

	/// <summary>
	/// ジャンプ処理
	/// </summary>
	/// <param name="input">入力</param>
	void Jump(Input& input);

	/// <summary>
	/// 重力と地面に関する処理
	/// </summary>
	void GravityAndGround();

private:	// 変数
	VECTOR m_pos;	// 位置
	VECTOR m_move;	// 移動量
	float m_dirY;	// Y方向の向き

	int m_modelHandle;	// 3Dモデル	

	float m_jumpPower;	// ジャンプ力
	bool m_isJump;		// ジャンプ中かどうか

private:	// 定数
	static constexpr float kSpeed = 0.3f;			// 速度
	static constexpr float kScale = 0.002f;			// 拡大率
	static constexpr float kRadius = 0.5f;			// 半径
	static constexpr float kGravity = 0.025f;		// 重力
	static constexpr float kJumpPower = 0.35f;		// ジャンプ力
	static constexpr float kGroundPosY = 0.4f;		// 地面のY位置
};

