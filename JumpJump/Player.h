#pragma once

class Input;
class Camera;
class StageTest;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	// 状態
	enum class State : int
	{
		Idle = 0,		// 立ち止まり
		Run = 1,		// 走り
		Jump = 2,		// ジャンプ
	};

	// アニメーション種別
	enum class AnimKind :int
	{
		None = -1,		// 無し
		Unknown = 0,	// 不明
		Run = 7,		// 走る
		Jump = 12,		// ジャンプ
		Fall = 13,		// 落下中
		Stop = 1,		// 立ち止まり
	};

public:
	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, StageTest& stage);
	void Draw();
	void End();

	const VECTOR& GetPos()const { return m_pos; }
	bool GetIsMove() const { return m_isMove; }
	State GetState()const { return m_state; }
	float GetJumpPower()const { return m_nowJunpPower; }

	void OnHitRoof();
	void OnHitFloor();
	void OnFall();

private:	// 関数

	void DisableRootFrameZMove();

	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	void Move(const VECTOR& moveVec, StageTest& stage);
	
	/// <summary>
	/// 回転制御
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// アニメーションステートの更新
	/// </summary>
	/// <param name="prevState"></param>
	void UpdateAnimationState(State prevState);

	/// <summary>
	/// 新しいアニメーションの再生
	/// </summary>
	/// <param name="playAnim"></param>
	void PlayAnimation(AnimKind nextPlayAnim);

	/// <summary>
	/// アニメーション処理
	/// </summary>
	/// <param name="playAnim"></param>
	void UpdateAnimation();



private:	// 変数
	VECTOR m_pos;				// 座標
	VECTOR m_targetDir;			// 向きたい方向のベクトル
	float m_angle;				// 向いている角度
	float m_nowJunpPower;		// ジャンプ時の現在の速度
	int m_modelHandle;			// モデルのハンドル
	State m_state;				// 現在の状態

	int m_nowPlayAnim;				// 今再生しているアニメーションの番号
	int m_prevPlayAnim;				// 前の再生アニメーションの番号
	float m_nowAnimCount;			// 再生しているアニメーションの再生時間
	float m_prevAnimCount;			// 前の再生アニメーションの再生時間
	float m_animBlendRate;			// 前と今のアニメーションのブレンド率

	bool m_isMove;		// そのフレームで動いたかどうか
	
};

