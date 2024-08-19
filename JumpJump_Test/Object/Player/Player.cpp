#include "DxLib.h"
#include "Player.h"
#include "PlayerState.h"
#include "Stamina.h"
#include "../Model.h"
#include "../Camera.h"
#include "../../Util/Input.h"
#include "../../Util/Time.h"
#include "../../Util/MoveDirectionVec.h"
#include "../ObjectManager.h"
#include "../ObjectBase.h"
#include "../../Shader/ToonShader.h"
#include "../../Shader/DamageShader.h"
#include "../Circle.h"


#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";	// プレイヤーモデルファイル名
	constexpr float kSize = 15.0f;	// プレイヤーサイズ
	constexpr float kModelSize = 0.11f;	// プレイヤーモデルのサイズ
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

	constexpr int kStageClearAnim = 65;				// ステージクリアアニメーション

	constexpr float kDrawDistance = 500.0f;			// 描画可能距離

	/*アニメーション速度*/
	enum kAnimSpeed
	{
		Idle = 2,
		Walk = 2,
		Dash = 1,
		Jump = 1,
		KnockBack = 1,
		StageClear = 1,
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
	// アニメーションの初期化

	/*ポインタの作成*/
	m_pStamina = std::make_shared<Stamina>();
	m_pState = std::make_shared<PlayerState>(m_pStamina);
	m_pInvincibleTime = std::make_shared<Time>(kInvinvibleTime);
	m_pCamera = std::make_shared<Camera>();
	m_pCircle = std::make_shared<Circle>(m_info.pos, kSize, kHeight * 0.5f);
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pDamageShader = std::make_shared<DamageShader>();

	m_pModel->SetAnim(m_animData.idle, false, true);
	m_pModel->SetScale(VGet(kModelSize, kModelSize, kModelSize));

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
	/*処理無し*/
}

void Player::Init()
{
	/*処理無し*/
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
	m_info.vec = MoveUpdate(input);

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

void Player::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// モデルのフレームごとに描画をする
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// 攻撃を受けた時はダメージシェーダを適応する
		if (m_pDamageShader->GetUseShader())
		{
			int triangleType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

			m_pDamageShader->DrawFirst(triangleType);

			// 描画可能な距離を超えていない時のみ描画する
			if (VSize(m_cameraToPlayerVec) > kDrawDistance)
			{
				MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
			}

			// シェーダを元に戻す
			m_pDamageShader->DrawEnd();
		}
		else	// ダメージを食らっていないときはトゥーンシェーダを使う
		{
			for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
			{
				int triangleType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

				pToonShader->SetShader(triangleType);

				MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
			}
		}
	}
}

void Player::Draw2D()
{
	m_pStamina->Draw(m_info.pos);
#ifdef _DEBUG
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標：%f,%f,%f",m_info.pos.x,m_info.pos.y,m_info.pos.z);
#endif // _DEBUG

}

void Player::StageClear()
{
	// 座標をゴールの座標にする
	m_info.pos = VGet(0.0f, 0.0f, 0.0f);

	// 角度を変える
	m_angle = 0.0f;
	m_isStageClear = true;
	m_pCamera->StageClear(m_angle, m_info.pos);
	m_pState->StageClear();
}

void Player::OnDamage(VECTOR targetPos)
{
	// ゲームクリア状態だったら何もせずに終了する
	if (m_pObjectManager->IsGameClear())return;

	// ノックバックのスピードと方向を計算する
	m_moveSpeed = kKnockBackSpeed;
	m_isDamage = true;
	
	m_pState->OnDamage();

	m_moveDirectVec = VNorm(VSub(
		VGet(m_info.pos.x, 0.0f, m_info.pos.z),
		VGet(targetPos.x, 0.0f, targetPos.z)));

	// シェーダをONにする

	// ダメージ音を鳴らす

}

void Player::EndJump()
{
	m_isJump = false;
	m_jumpPower = 0.0f;

	// ジャンプ音を鳴らす

	// ステージクリア時は処理を終了する
	if (m_pState->GetState() == PlayerState::StateKind::StateClear) return;

	m_pState->EndState();
}

bool Player::ChangeStaminaValue()
{
	// ダッシュ中はスタミナを変更する
	if (m_pState->GetState() == PlayerState::StateKind::Dash) return false;

	// どの条件にも当てはまらない場合はスタミナを変更しない
	return false;
}

void Player::CameraUpdate()
{
	m_pCamera->Update(m_info.pos);
	m_pCamera->Draw();
}

void Player::AngleUpdate()
{
	// ノックバック中は処理をしない
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack) return;

	float nextAngle = atan2(m_moveDirectVec.z, m_moveDirectVec.x) +
		DX_PI_F * 0.5f + m_pCamera->GetCameraAngleX();

	SmoothAngle(m_angle, nextAngle);
	
}

void Player::MoveDirectionUpdate(Input& input)
{
	// ジャンプ中、ノックバック中は処理をせずに終了する
	if (m_pState->GetState() == PlayerState::StateKind::Jump ||
		m_pState->GetState() == PlayerState::StateKind::KnockBack) return;

	// 移動方向ベクトルクラスを生成
	MoveDirectionVec moveVec;

	// 移動方向アップデート
	moveVec.Update(input);
	
	// 進みたい方向と今の方向の線形補完
	m_moveDirectVec = VAdd(VScale(m_moveDirectVec, kNowVecNum),
		VScale(moveVec.GetDirectionVec(), kNextVecNum));

	// 進みたい方向のY軸を省く
	m_moveDirectVec.y = 0.0f;
}

VECTOR Player::MoveUpdate(Input& input)
{
	// 移動スピードが0の場合は移動しない
	if (m_moveSpeed == 0.0f)return VGet(0.0f, 0.0f, 0.0f);
	// 移動方向の更新
	MoveDirectionUpdate(input);
	// 角度の更新
	AngleUpdate();

	// 移動ベクトル生成
	VECTOR move = VNorm(m_moveDirectVec);

	// ノックバック中の処理
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack)
	{
		move.x *= m_moveSpeed;
		move.z *= m_moveSpeed;

		return move;
	}

	// 移動ベクトルにスピードをかける
	// X軸は反転させる
	move.x *= -m_moveSpeed;
	move.z *= m_moveSpeed;

	// カメラの角度によって進む方向を変える
	MATRIX playerRotMtx = MGetRotY(m_pCamera->GetCameraAngleX());

	// 移動ベクトルとカメラ角度行列を乗算する
	move = VTransform(move, playerRotMtx);

	return move;
}

void Player::JumpInit()
{
	m_isJump = true;
	m_jumpPower = kJumpMaxSpeed;
	// ジャンプ音を鳴らす

	m_pStamina->JumpUpdate();
}

void Player::IdleUpdate()
{
	m_moveSpeed = max(m_moveSpeed - m_acc, 0.0f);

	// アニメーションを待機状態に変更する
	m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
}

void Player::WalkUpdate()
{
	// X軸方向の移動ベクトルに歩きスピードを代入する
	m_moveSpeed = min(m_moveSpeed + m_acc, m_walkSpeed);

	// アニメーションを歩きアニメーションに変更する
	m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);

	// 足音を鳴らす

}

void Player::DashUpdate()
{
	m_moveSpeed = m_dashSpeed;

	// アニメーションをダッシュモーションに変更する
	m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);

	// 足音を鳴らす(ダッシュ時)

}

void Player::JumpUpdate()
{
	// 上昇中
	if (m_jumpPower > kJumpRise)
	{
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// 空中にとどまっている、下降中
	else
	{
		m_pModel->ChangeAnim(m_animData.jumpIdle, false, false, kAnimSpeed::Jump);
	}
}

void Player::KnockBackUpdate()
{
	m_moveSpeed = max(m_moveSpeed - kKnockBackSpeedDecrease, 0.0f);
	m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	// アニメーションが終わったら待機状態に戻る
	if (m_pModel->IsAnimEnd())
	{
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		m_pState->EndState();
	}
}

void Player::StageClearUpdate()
{
	m_moveSpeed = 0.0f;
	// モデルをステージクリア状態に変更する
	m_pModel->ChangeAnim(kStageClearAnim, true, false, kAnimSpeed::StageClear);
}