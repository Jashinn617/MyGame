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
		Walk = 1,		// 歩き
		Run = 2,		// 走り
		Jump = 3,		// ジャンプ
	};

	// アニメーション種別
	enum class AnimKind :int
	{
		None = -1,		// 無し
		Unknown = 0,	// 不明
		Walk = 10,		// 歩く
		Run = 6,		// 走る
		Jump = 3,		// ジャンプ
		Idle = 2,		// 立ち止まり
	};

public:
	Player();
	~Player();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="camera">カメラ</param>
	/// <param name="stage">現在の状態</param>
	void Update(const Input& input, const Camera& camera, StageTest& stage);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// 位置の取得
	/// </summary>
	/// <returns>現在位置</returns>
	const VECTOR& GetPos()const { return m_pos; }

	/// <summary>
	/// 現在移動中かの取得
	/// </summary>
	/// <returns>現在移動中か</returns>
	bool GetIsMove() const { return m_isMove; }

	/// <summary>
	/// 状態の取得
	/// </summary>
	/// <returns>現在の状態</returns>
	State GetState()const { return m_currentState; }

	/// <summary>
	/// ジャンプの高さの取得
	/// </summary>
	/// <returns>ジャンプの高さ</returns>
	float GetJumpPower()const { return m_nowJunpPower; }

	/// <summary>
	/// 天井に当たった時の処理
	/// </summary>
	void OnHitRoof();

	/// <summary>
	/// 床に当たった時の処理
	/// </summary>
	void OnHitFloor();

	/// <summary>
	/// 落下処理
	/// </summary>
	void OnFall();

private:	// 関数

	/// <summary>
	/// ルートフレームのZ軸方向の移動パラメータを無効にする
	/// アニメーションや、当たり判定に不具合が起きないようにするために使用する
	/// </summary>
	void DisableRootFrameZMove();

	/// <summary>
	/// 入力によるパラメータを設定する
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="camera">カメラ</param>
	/// <param name="upMoveVec">上方向の移動ベクトル</param>
	/// <param name="leftMoveVec">左方向の移動ベクトル</param>
	/// <param name="moveVec">移動ベクトル</param>
	/// <returns>現在の状態</returns>
	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="moveVec">移動ベクトル</param>
	/// <param name="stage">現在の状態</param>
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
	/// アニメーションの更新
	/// </summary>
	/// <param name="attachNo">現在のアニメーション番号</param>
	/// <returns>ループしているかどうか</returns>
	bool LoopAnim(int attachNo);

	/// <summary>
	/// アニメーションの入れ替え
	/// </summary>
	/// <param name="animIndex">入れ替えるアニメーションの番号</param>
	void ChangeAnim(int animIndex);



private:	// 変数
	VECTOR m_pos;					// 座標
	VECTOR m_targetDir;				// 向きたい方向のベクトル
	float m_angle;					// 向いている角度
	float m_nowJunpPower;			// ジャンプ時の現在の速度
	int m_modelHandle;				// モデルのハンドル
	int m_ps;
	int m_vs;

	State m_currentState;				// 現在の状態

	int m_currentAnimNo;			// 今再生しているアニメーションの番号
	int m_prevAnimNo;				// 前の再生アニメーションの番号
	float m_nowAnimCount;			// 再生しているアニメーションの再生時間
	float m_prevAnimCount;			// 前の再生アニメーションの再生時間
	float m_animBlendRate;			// 前と今のアニメーションのブレンド率

	bool m_isMove;					// そのフレームで動いたかどうか
};

