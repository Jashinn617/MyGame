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
	void JumpUpdate();
	void KnockBackUpdate();

private:	// 変数
	float m_walkSpeed;	// 移動速度
	float m_dashSpeed;	// ダッシュ時の速度
	float m_acc;	// 加速度

	bool m_isStageClear;	// ステージをクリアしたかどうか

	VECTOR m_moveDirectVec;	// 移動方向ベクトル
	VECTOR m_cameraToPlayer;	// プレイヤーからカメラまでの距離

	std::shared_ptr<PlayerState> m_pState;		// 状態のポインタ
	std::shared_ptr<Stamina> m_pStamina;		// スタミナのポインタ
	std::shared_ptr<Time> m_pInvincibleTime;	// 攻撃を食らった後の無敵時間
	std::shared_ptr<Camera> m_pCamera;			// カメラポインタの取得
};

