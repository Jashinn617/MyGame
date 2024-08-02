#include "DxLib.h"
#include "Player.h"
#include "PlayerState.h"
#include "Stamina.h"
#include "../Model.h"
#include "../Camera.h"
#include "../../Util/Input.h"
#include "../../Util/Time.h"
#include "../ObjectManager.h"
#include "../ObjectBase.h"

#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";	// プレイヤーモデルファイル名
	constexpr float kSize = 15.0f;	// プレイヤーサイズ
	constexpr float kModelSize = 20.0f;	// プレイヤーモデルのサイズ
	/*スピード関係*/
	constexpr float kMoveSpeedDashRate = 2.2f;	// 走っているときのスピード
	constexpr float kAccelerationRate = 0.5f;	// 加速度
	/*ジャンプ関係*/
	constexpr float kJumpMaxSpeed = 8.0f;		// ジャンプ時の最大速度
	constexpr float kGravity = 0.8f;			// 重力
	constexpr float kFallMaxSpeed = -15.0f;		// 落下最大速度
	/*ジャンプ時のアニメーション変更用変数*/
	constexpr float kJumpRise = 1.0f;
	constexpr float kJumpIdleNum = -5.0f;
	constexpr float kJumpDown = -15.0f;

	constexpr float kPlayerAngleSpeed = 0.2f;		// プレイヤーの回転速度
	constexpr int kInvinvibleTime = 60;				// 無敵時間
	constexpr float kKnockBackSpeed = 3.0f;			// ノックバックのスピード
	constexpr float kKnockBackSpeedDecrease = 0.2f;	// ノックバックスピード減少量
	constexpr float kHeight = 35.0f;				// 高さ

	/*移動の補完値*/
	constexpr float kNowVecNum = 0.8f;
	constexpr float kNextVecNum = 0.2f;

	/*アニメーション速度*/
	enum kAnimSpeed
	{
		Idle = 2,
		Walk = 2,
		Dash = 1,
		KnockBack = 1
	};
}

Player::Player():
	m_walkSpeed(0),
	m_dashSpeed(0),
	m_acc(0),
	m_isStageClear(false),
	m_moveDirectVec{0,0,0},
	m_cameraToPlayerVec{0,0,0}	
{
	/*ポインタの作成*/
	m_pStamina = std::make_shared<Stamina>();
	m_pState = std::make_shared<PlayerState>(m_pStamina);
	m_pInvincibleTime = std::make_shared<Time>(kInvinvibleTime);
	m_pCamera = std::make_shared<Camera>();

	/*状態の追加*/
	// 待機
	m_pState->AddState([=] {IdleInit(); },
		[=] {IdleUpdate(); },
		PlayerState::StateKind::Idle);
	// 歩き
	m_pState->AddState([=] {WalkInit(); },
		[=] {WalkUpdate(); },
		PlayerState::StateKind::Walk);
	// ダッシュ
	m_pState->AddState([=] {DashInit(); },
		[=] {DashUpdate(); },
		PlayerState::StateKind::Dash);
	// ジャンプ
	m_pState->AddState([=] {JumpInit(); },
		[=] {JumpUpdate(); },
		PlayerState::StateKind::Jump);
	// ノックバック
	m_pState->AddState([=] {KnockBackInit(); },
		[=] {KnockBackUpdate(); },
		PlayerState::StateKind::KnockBack);

	// 初期状態の設定
	// 初期は待機状態から始まる
	m_pState->SetState(PlayerState::StateKind::Idle);
	
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update(Input& input)
{
	// ステージクリア時
	if (m_isStageClear)
	{
		// カメラをステージクリア用にする
		m_pCamera->StageClearUpdate();

	}

	// 状態更新
	m_pState->Update(input);

	// スタミナの値を変更させるかどうか
	if (ChangeStaminaValue())
	{
		// ダッシュ中かジャンプの時以外はスタミナを使わない
		bool useStamina = (m_pState->GetState() == PlayerState::StateKind::Dash);

		// スタミナ更新
		m_pStamina->Update(useStamina);
	}

	// 移動更新
	m_info.vec = MoveUpdate();

	// 重力を考慮した更新
	GravityUpdate();

	// 攻撃を受けた時のシェーダの更新
	// 後でする

	// 攻撃を受けた時
	if (m_isDamage)
	{
		// 無敵時間を計測して無敵時間が終わったらダメージを受ける状態を解除する
		if (m_pInvincibleTime->Update())
		{
			m_pInvincibleTime->Reset();
			m_isDamage = false;
		}
	}

	// アニメーションの更新
	m_pModel->Update();

	// モデルの座標を設定する
	m_pModel->SetPos(m_info.pos);

	// モデルの角度を設定する
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));

	// カメラの更新
	CameraUpdate();

	// プレイヤーからカメラまでの距離の更新
	m_cameraToPlayerVec = VSub(m_info.pos, m_pCamera->GetPos());
}

void Player::Draw()
{
	// モデルのフレームごとに描画をする
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// 攻撃を受けた時はダメージシェーダを適応する
		
	}
}

void Player::OnDamage(VECTOR targetPos)
{
	// ゲームクリア状態だったら何もせずに終了する
	if (m_pObjectManager->IsGameClear())return;

}

void Player::EndJump()
{
}

bool Player::ChangeStaminaValue()
{
	return false;
}

void Player::CameraUpdate()
{
}

void Player::AngleUpdate()
{
}

void Player::MoveDirectionUpdate()
{
}

VECTOR Player::MoveUpdate()
{
	return VECTOR();
}

void Player::IdleUpdate()
{
}

void Player::WalkUpdate()
{
}

void Player::DashUpdate()
{
}

void Player::JumpUpdate()
{
}

void Player::KnockBackUpdate()
{
}
