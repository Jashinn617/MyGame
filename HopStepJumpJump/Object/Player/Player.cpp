#include "DxLib.h"
#include "Player.h"
#include "PlayerState.h"

#include "../ObjectManager.h"
#include "../ObjectBase.h"
#include "../Model.h"
#include "../Camera.h"
#include "../Circle.h"

#include "../../Util/Pad.h"
#include "../../Util/Time.h"
#include "../../Util/MoveDirectionVec.h"
#include "../../Util/CsvLoad.h"
#include "../../Util/SoundManager.h"

#include "../../Shader/ToonShader.h"

#include "../../Effect/Effekseer3DManager.h"

#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";	// プレイヤーモデルファイルパス
	/*スピード関係*/
	constexpr float kMoveSpeedDashRate = 1.2f;		// 走っているときのスピード
	constexpr float kAccelerationRate = 0.5f;		// 加速度
	/*ジャンプ関係*/
	constexpr float kJumpMaxSpeed = 8.0f;			// ジャンプ時の最大速度
	constexpr float kGravity = 0.8f;				// 重力
	constexpr float kFallMaxSpeed = -15.0f;			// 落下最大速度
	constexpr float kAttackHitJumpSpeed = 3.0f;		// 敵を踏んだ際に跳ねる速度
	/*移動の補完値*/
	constexpr float kNowVecNum = 0.8f;				// 現在の方向
	constexpr float kNextVecNum = 0.2f;				// 進みたい方向

	constexpr int kStageClearAnim = 16;						// ステージクリアアニメーション
	constexpr int kInvinvibleTime = 30;						// 無敵時間
	constexpr float kMinJumpRiseNum = 1.0f;					// 上昇中と判断される最低値
	constexpr float kPlayerAngleSpeed = 0.02f;				// プレイヤーの回転速度
	constexpr float kKnockBackSpeed = 10.0f;				// ノックバックのスピード
	constexpr float kKnockBackSpeedDecrease = 0.2f;			// ノックバックスピード減少量
	constexpr float kHeight = 35.0f;						// 高さ
	constexpr float kSize = 15.0f;							// プレイヤーサイズ
	constexpr float kModelSize = 0.11f;						// プレイヤーモデルのサイズ
	constexpr float kFallSEPosY = -300.0f;					// 落下SEが流れるY位置
	constexpr float kFallBackPosY = -800.0f;				// スタート地点に戻される位置Y
	constexpr float kDrawDistance = 50.0f;					// 描画可能距離
	constexpr float kEnemyHeadPos = 20;						// 敵の頭の位置
	constexpr VECTOR kStartPos = { 0.0f, 0.0f, 0.0f };		// 初期位置

	// アニメーション速度
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

Player::Player() :
	m_walkSpeed(0),
	m_dashSpeed(0),
	m_acc(0),
	m_isStageClear(false),
	m_moveDirectVec{ 0,0,0 },
	m_cameraToPlayerVec{ 0,0,0 },
	m_pState(std::make_shared<PlayerState>()),
	m_pCamera(std::make_shared<Camera>()),
	m_pInvincibleTime(std::make_shared<Time>(kInvinvibleTime))
{
	// アニメーションロード
	CsvLoad::GetInstance().AnimLoad(m_animData, "Player");
	// 移動スピード初期化
	m_walkSpeed = m_statusData.spd;
	m_dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_acc = m_statusData.spd * kAccelerationRate;
	// 情報初期化
	m_info.pos = kStartPos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;

	// 当たり判定用ポインタ作成
	m_pCircle = std::make_shared<Circle>(m_info.pos, kSize, kHeight * 0.5f);
	// モデルポインタ作成
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	// モデルサイズ設定
	m_pModel->SetScale(VGet(kModelSize, kModelSize, kModelSize));
	// アニメーション初期化
	m_pModel->SetAnim(m_animData.idle, false, true);

	/*ステイト追加*/
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
	// ステージクリア
	m_pState->AddState([=] {StageClearInit(); },
		[=] {StageClearUpdate(); },
		PlayerState::StateKind::StateClear);

	// 初期状態の設定
	// 初期は待機状態から始まる
	m_pState->SetState(PlayerState::StateKind::Idle);
}

Player::~Player()
{
	/*処理無し*/
}

void Player::Update()
{
	// ステージクリア時
	if (m_isStageClear)
	{
		// カメラをステージクリア用にする
		m_pCamera->StageClearUpdate();
	}

	// 状態更新
	m_pState->Update();
	// 移動更新
	m_info.vec = MoveUpdate();
	// 重力による落下処理
	GravityUpdate();

	// 攻撃を受けた時
	if (m_isDamage)
	{
		// 無敵時間を計測して無敵時間が終わったらダメージを受ける状態を解除する
		if (m_pInvincibleTime->Update())
		{
			// 無敵時間のリセット
			m_pInvincibleTime->Reset();
			// ダメージフラグのリセット
			m_isDamage = false;
		}
	}
	// アニメーションの更新
	m_pModel->Update();
	// モデルの座標を設定する
	m_pModel->SetPos(m_info.pos);
	// モデルの角度を設定する
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));

	// カメラ更新
	m_pCamera->Update(m_info.pos);

	// プレイヤーからカメラまでの距離の更新
	m_cameraToPlayerVec = VSub(m_info.pos, m_pCamera->GetPos());

	// 落ちたら初期位置に戻る
	if (m_info.pos.y <= kFallSEPosY)
	{
		if (!m_isStageClear)	// ステージクリア時で無かった場合
		{
			// 落下SEが流れていなかったら
			if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Fall"))
			{
				// 落下SEを流す
				SoundManager::GetInstance().Play("Fall");
			}
		}
		
		// 規定地点まで落ちたら
		if (m_info.pos.y <= kFallBackPosY)
		{
			// 初期位置に戻る
			m_info.pos = kStartPos;
			// ジャンプ状態を解除する
			EndJump();
		}
	}	
}

void Player::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	 //モデルのフレームごとに描画をする
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// 頂点タイプの取得
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		// シェーダの設定
		pToonShader->SetShader(shaderType);

		// 描画
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// シェーダを使わない設定にする
	pToonShader->ShaderEnd();

	// 当たり判定用の球の表示
	m_pCircle->DebugDraw();
}

void Player::Draw2D()
{
	// カメラ2D部分の描画
	m_pCamera->Draw();

#ifdef _DEBUG
	// デバッグ用描画
	DrawFormatString(0, 20, 0x000000, "プレイヤー座標：%f,%f,%f"
		, m_info.pos.x, m_info.pos.y, m_info.pos.z);
	DrawFormatString(0, 100, 0x000000, "ジャンプ力：%f", m_jumpPower);
#endif // _DEBUG
}

void Player::StageClear()
{
	// 角度のリセット
	m_angle = 0.0f;

	// クリアフラグを立てる
	m_isStageClear = true;
	// カメラをクリア状態にする
	m_pCamera->StageClear(m_angle, m_info.pos);
	// ステイト状態をクリア状態にする
	m_pState->StageClear();
}

void Player::StageEnd()
{
	// ステージ終了フラグを立てる
	m_isStageEnd = true;

	/*プレイヤー操作が効かないようにする*/
	// 重力を考慮した更新
	GravityUpdate();
	// アニメーションの更新
	m_pModel->Update();
	// モデルの座標を設定する
	m_pModel->SetPos(m_info.pos);
	// モデルの角度を設定する
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	// カメラの更新
	m_pCamera->Update(m_info.pos);
	// プレイヤーからカメラまでの距離の更新
	m_cameraToPlayerVec = VSub(m_info.pos, m_pCamera->GetPos());
}

void Player::OnDamage(VECTOR targetPos)
{
	// ゲームクリア状態かステージ終了状態だったら何もせずに終了する
	if (m_pObjectManager->IsGameClear())return;
	if (m_pObjectManager->IsGameEnd())return;

	// 敵のY位置が自分の位置より低かった場合は何もしない
	if (targetPos.y <= m_info.pos.y - kEnemyHeadPos)return;

	// ダメージ中は何もしない
	if (m_isDamage) return;

	// ノックバックのスピードと方向を計算する
	m_moveSpeed = kKnockBackSpeed;
	m_isDamage = true;

	// ダメージ処理
	m_pState->OnDamage();

	// 移動方向の設定
	m_moveDirectVec = VNorm(VSub(
		VGet(m_info.pos.x, 0.0f, m_info.pos.z),
		VGet(targetPos.x, 0.0f, targetPos.z)));

	// ダメージ音を鳴らす
	SoundManager::GetInstance().Play("Damage");

	// エフェクトを流す
	Effekseer3DManager::GetInstance().Add("Damage", Effekseer3DManager::PlayType::Normal, this, m_info.pos);
}

void Player::OnAttack()
{
	// 少しだけ跳ねる
	m_jumpPower = kAttackHitJumpSpeed;
}

void Player::EndJump()
{
	// ジャンプフラグをfalseにする
	m_isJump = false;
	// ジャンプ力を0にする
	m_jumpPower = 0.0f;

	// ステージクリア時は処理を終了する
	if (m_pState->GetState() == PlayerState::StateKind::StateClear) return;
	// ステイトの終了処理
	m_pState->EndState();
}

void Player::AngleUpdate()
{
	// ノックバック中は処理をしない
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack) return;

	// 目標角度の計算
	float nextAngle = atan2(m_moveDirectVec.z, m_moveDirectVec.x)
		+ DX_PI_F * 0.5f + m_pCamera->GetCameraAngleX();

	// 角度を滑らかに変更する
	SmoothAngle(m_angle, nextAngle);
}

void Player::MoveDirectionUpdate()
{
	// ステージ終了処理中は何もしない
	if (m_isStageEnd) return;
	// ノックバック中は何もしない
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack) return;

	// 移動方向ベクトルクラスを生成
	MoveDirectionVec moveVec;

	// 移動方向アップデート
	moveVec.Update();

	// 進みたい方向と今の方向の線形補完
	m_moveDirectVec = VAdd(VScale(m_moveDirectVec, kNowVecNum),
		VScale(moveVec.GetDirectionVec(), kNextVecNum));

	// 進みたい方向のY軸を省く
	m_moveDirectVec.y = 0.0f;
}

VECTOR Player::MoveUpdate()
{
	// ステージ終了処理中は何もしない
	if (m_isStageEnd) return VGet(0.0f, 0.0f, 0.0f);

	// 移動スピードが0の場合は何もしない
	if (m_moveSpeed == 0.0f)return VGet(0.0f, 0.0f, 0.0f);

	// 移動方向の更新
	MoveDirectionUpdate();
	// 角度の更新
	AngleUpdate();

	// 移動ベクトル生成
	VECTOR move = VNorm(m_moveDirectVec);

	// ノックバック中の処理
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack)
	{
		// 移動ベクトルにスピードをかける
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
	// ステージ終了処理中は何もしない
	if (m_isStageEnd) return;

	// ジャンプフラグを立てる
	m_isJump = true;
	// ジャンプ力を設定する
	m_jumpPower = kJumpMaxSpeed;
	// ジャンプ音を鳴らす
	SoundManager::GetInstance().Play("Jump");
}

void Player::IdleUpdate()
{
	// 段々減速する
	m_moveSpeed = max(m_moveSpeed - m_acc, 0.0f);
	// アニメーションを待機状態に変更する
	m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
}

void Player::WalkUpdate()
{
	// ステージ終了処理中は何もしない
	if (m_isStageEnd) return;

	// X軸方向の移動ベクトルに歩き状態の速度を代入する
	m_moveSpeed = min(m_moveSpeed + m_acc, m_walkSpeed);

	// アニメーションを歩きアニメーションに変更する
	m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);

	// 歩きサウンドが流れていなかった場合
	if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Walk"))
	{
		// 足音を鳴らす
		SoundManager::GetInstance().Play("Walk");
	}
}

void Player::DashUpdate()
{
	// ステージ終了処理中は何もしない
	if (m_isStageEnd) return;

	// 移動速度をダッシュ時の速度にする
	m_moveSpeed = m_dashSpeed;

	// アニメーションをダッシュアニメーションに変更する
	m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);

	// ダッシュサウンドが流れていなかった場合
	if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Dash"))
	{
		// ダッシュ時の足音を鳴らす
		SoundManager::GetInstance().Play("Dash");
	}
}

void Player::JumpUpdate()
{
	// ステージ終了処理中は何もしない
	if (m_isStageEnd) return;

	// 上昇中
	if (m_jumpPower > kMinJumpRiseNum)
	{
		// アニメーションをジャンプ開始アニメーションに切り替える
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// 空中にとどまっている、下降中
	else
	{
		// アニメーションをジャンプ待機アニメーションに切り替える
		m_pModel->ChangeAnim(m_animData.jumpIdle, false, false, kAnimSpeed::Jump);
	}
}

void Player::KnockBackUpdate()
{
	// 段々減速していく
	m_moveSpeed = max(m_moveSpeed - kKnockBackSpeedDecrease, 0.0f);
	// アニメーションをノックバックアニメーションに切り替える
	m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);

	if (m_pModel->IsAnimEnd())		// アニメーションが終了した場合
	{
		// 待機アニメーションに切り替える
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		// ステイトの終了処理
		m_pState->EndState();
	}
}

void Player::StageClearUpdate()
{
	// 速度を0にする
	m_moveSpeed = 0.0f;
	// モデルをステージクリア状態に変更する
	m_pModel->ChangeAnim(kStageClearAnim, true, false, kAnimSpeed::StageClear);
}