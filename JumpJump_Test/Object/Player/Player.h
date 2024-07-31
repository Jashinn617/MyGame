#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

#include <array>
#include <memory>
#include <vector>

class Input;
class Camera;
class StageTest;

class Model;
class Circle;
class PlayerState;
class Stamina;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update() override final;
	virtual void Draw();

private:	// 関数
	/// <summary>
	/// スタミナを変化させるかどうか
	/// </summary>
	/// <returns></returns>
	bool ChangeStaminaValue();

	/// <summary>
	/// カメラの更新
	/// </summary>
	void CameraUpdate();

	/// <summary>
	/// 角度の更新
	/// </summary>
	void AngleUpdate();

	/// <summary>
	/// 移動方向の更新
	/// </summary>
	void MoveDirectionUpdate();

	/// <summary>
	/// 移動
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate();

private:	// メンバ関数用関数

	/*各状態の初期化*/
	void IdleInit() {};
	void WalkInit() {};
	void DashInit() {};
	void JumpInit() {};
	void KnockBackInit() {};

	/*各状態の更新*/
	void IdleUpdate();
	void WalkUpdate();
	void DashUpdate();
	void JumpInit();
	void KnockBackUpdate();

private:	// 変数
	float m_walkSpeed;	// 移動速度
	float m_dashSpeed;	// ダッシュ時の速度
	float m_acc;	// 加速度

	VECTOR m_moveDirectVec;	// 移動方向ベクトル
	VECTOR m_cameraToPlayer;	// プレイヤーからカメラまでの距離

	std::shared_ptr<PlayerState> m_pState;		// 状態のポインタ
	std::shared_ptr<Stamina> m_pStamina;		// スタミナのポインタ
	std::shared_ptr<Time> m_pInvincibleTime;	// 攻撃を食らった後の無敵時間
	std::shared_ptr<Camera> m_pCamera;			// カメラポインタの取得





















//public:
//	// 状態
//	enum class State : int
//	{
//		Idle = 0,		// 立ち止まり
//		Walk = 1,		// 歩き
//		Run = 2,		// 走り
//		Jump = 3,		// ジャンプ
//	};
//
//	// アニメーション種別
//	enum class AnimKind :int
//	{
//		None = -1,		// 無し
//		Unknown = 0,	// 不明
//		Walk = 14,		// 歩く
//		Run = 11,		// 走る
//		Jump = 6,		// ジャンプ
//		Fall = 7,		// 落下
//		Idle = 3,		// 立ち止まり
//	};
//
//public:
//	Player();
//	~Player();
//
//	/// <summary>
//	/// 初期化処理
//	/// </summary>
//	void Init();
//
//	/// <summary>
//	/// 更新処理
//	/// </summary>
//	/// <param name="input">入力</param>
//	/// <param name="camera">カメラ</param>
//	/// <param name="stage">現在の状態</param>
//	void Update(const Input& input, const Camera& camera, StageTest& stage);
//
//	/// <summary>
//	/// 描画処理
//	/// </summary>
//	void Draw();
//
//	/// <summary>
//	/// 終了処理
//	/// </summary>
//	void End();
//
//	/// <summary>
//	/// 位置の取得
//	/// </summary>
//	/// <returns>現在位置</returns>
//	const VECTOR& GetPos()const { return m_pos; }
//
//	/// <summary>
//	/// 現在移動中かの取得
//	/// </summary>
//	/// <returns>現在移動中か</returns>
//	bool GetIsMove() const { return m_isMove; }
//
//	/// <summary>
//	/// 状態の取得
//	/// </summary>
//	/// <returns>現在の状態</returns>
//	State GetState()const { return m_currentState; }
//
//	/// <summary>
//	/// ジャンプの高さの取得
//	/// </summary>
//	/// <returns>ジャンプの高さ</returns>
//	float GetJumpPower()const { return m_nowJunpPower; }
//
//	/// <summary>
//	/// 天井に当たった時の処理
//	/// </summary>
//	void OnHitRoof();
//
//	/// <summary>
//	/// 床に当たった時の処理
//	/// </summary>
//	void OnHitFloor();
//
//	/// <summary>
//	/// 落下処理
//	/// </summary>
//	void OnFall();
//
//private:	// 関数
//
//	/// <summary>
//	/// ルートフレームのZ軸方向の移動パラメータを無効にする
//	/// アニメーションや、当たり判定に不具合が起きないようにするために使用する
//	/// </summary>
//	void DisableRootFrameZMove();
//
//	/// <summary>
//	/// 入力によるパラメータを設定する
//	/// </summary>
//	/// <param name="input">入力</param>
//	/// <param name="camera">カメラ</param>
//	/// <param name="upMoveVec">上方向の移動ベクトル</param>
//	/// <param name="leftMoveVec">左方向の移動ベクトル</param>
//	/// <param name="moveVec">移動ベクトル</param>
//	/// <returns>現在の状態</returns>
//	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
//
//	/// <summary>
//	/// 移動
//	/// </summary>
//	/// <param name="moveVec">移動ベクトル</param>
//	/// <param name="stage">現在の状態</param>
//	void Move(const VECTOR& moveVec, StageTest& stage);
//
//	/// <summary>
//	/// スタミナの処理
//	/// </summary>
//	void Stamina();
//	
//	/// <summary>
//	/// 回転制御
//	/// </summary>
//	void UpdateAngle();
//
//	/// <summary>
//	/// アニメーションステートの更新
//	/// </summary>
//	/// <param name="prevState"></param>
//	void UpdateAnimationState(State prevState);
//
//	/// <summary>
//	/// アニメーションの更新
//	/// </summary>
//	/// <param name="attachNo">現在のアニメーション番号</param>
//	/// <returns>ループしているかどうか</returns>
//	bool LoopAnim(int attachNo);
//
//	/// <summary>
//	/// アニメーションの入れ替え
//	/// </summary>
//	/// <param name="animIndex">入れ替えるアニメーションの番号</param>
//	void ChangeAnim(int animIndex);
//
//
//
//private:	// 変数
//	VECTOR m_pos;					// 座標
//	VECTOR m_targetDir;				// 向きたい方向のベクトル
//	float m_angle;					// 向いている角度
//	float m_nowJunpPower;			// ジャンプ時の現在の速度
//	float m_stamina;				// スタミナ
//	int m_modelHandle;				// モデルハンドル
//
//	std::vector<int> m_psHs;		// ピクセルシェーダハンドル
//	std::vector<int> m_vsHs;		// 頂点シェーダハンドル
//	std::vector<int> m_pixelShaderNumbers;	// どのピクセルシェーダを使うか
//	std::vector<int> m_vertexShaderNumbers;	// どの頂点シェーダを使うか
//
//	State m_currentState;				// 現在の状態
//
//	int m_currentAnimNo;			// 今再生しているアニメーションの番号
//	int m_prevAnimNo;				// 前の再生アニメーションの番号
//	float m_nowAnimCount;			// 再生しているアニメーションの再生時間
//	float m_prevAnimCount;			// 前の再生アニメーションの再生時間
//	float m_animBlendRate;			// 前と今のアニメーションのブレンド率
//
//	bool m_isMove;					// そのフレームで動いたかどうか
//	bool m_isLackStamina;			// スタミナが不足しているかどうか
//	bool m_isDash;					// ダッシュ中かどうか
};

