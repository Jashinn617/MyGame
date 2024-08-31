#pragma once
#include "DxLib.h"
#include "../CharacterBase.h"
#include "../../Util/CharacterData.h"

#include <array>
#include <memory>
#include <vector>

class Input;
class Camera;

class Model;
class Circle;

class Player_ : public CharacterBase
{
public:
	// 状態
	enum class State : int
	{
		Idle = 0,		// 待機
		Walk = 1,		// 歩き
		Dash = 2,		// ダッシュ
		Jump = 3,		// ジャンプ
		KnockBack = 4,	// ノックバック
	};

public:
	Player_();
	~Player_();

	void Init();
	void Update(Input& input) override final;
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	void Draw2D() override final;

	void StageClear() override final;

	/// <summary>
	/// 攻撃を受けた
	/// </summary>
	/// <param name="targetPos"></param>
	void OnDamage(VECTOR targetPos) override final;

	/// <summary>
	/// 攻撃をした
	/// </summary>
	void OnAttack() override final;

	void EndJump() override final;

	void SetJumpPower(float jumpPower) { m_jumpPower = jumpPower; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns></returns>
	const VECTOR& GetPos()const { return m_info.pos; }

	/// <summary>
	/// 当たり判定の種類の取得
	/// </summary>
	/// <returns></returns>
	ColType GetColType()const { return ColType::Player; }

	/// <summary>
	/// カメラの取得
	/// </summary>
	/// <returns></returns>
	const std::shared_ptr<Camera> GetCamera() const { return m_pCamera; }

private:
	void AngleUpdate();

	State UpdateMoveParamerer(VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	VECTOR MoveUpdate(Input& input);

	/// <summary>
	/// 移動方向の更新
	/// </summary>
	void MoveDirectionUpdate(Input& input);

	/// <summary>
	/// アニメーションステートの更新
	/// </summary>
	/// <param name="prevState"></param>
	void UpdateAnimState(State prevState);

private:
	float m_walkSpeed;	// 移動速度
	float m_dashSpeed;	// ダッシュ時の速度
	float m_acc;		// 加速度

	bool m_isMove;	// そのフレームで動いたかどうか
	bool m_isDash;	// ダッシュ中かどうか

	VECTOR m_moveDirectVec;	// 移動方向ベクトル
	VECTOR m_cameraToPlayerVec;	// プレイヤーからカメラまでの距離

	State m_currentState;		// 現在の状態

	std::shared_ptr<Time> m_pInvincibleTime;	// 無敵時間
	std::shared_ptr<Camera> m_pCamera;			// カメラポインタ

};

