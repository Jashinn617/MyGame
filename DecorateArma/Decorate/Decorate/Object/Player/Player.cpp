﻿#include "Player.h"
#include "PlayerState.h"
#include "Shot.h"

#include "../ObjectManager.h"
#include "../Model.h"
#include "../Camera.h"
#include "../Enemy/EnemyBase.h"

#include "../../Shader/SetVertexShader.h"
#include "../../Shader/ToonShader.h"

#include "../../Utility/CollisionShape.h"
#include "../../Utility/MoveDirectionVec.h"
#include "../../Utility/Time.h"
#include "../../Utility/Pad.h"

#include "../../UI/HpBar/HpBarBase.h"
#include "../../UI/HpBar/HpBarPlayer.h"

#include "../../Common/CsvLoad.h"

#include <cassert>


namespace
{
	const char* const kFileName = "Data/Model/Player/Player.mv1";	// プレイヤーモデルファイルパス

	constexpr int kAttackStanTime = 20;						// 攻撃硬直時間
	constexpr int kattackInvokeTime = 30;					// 強攻撃発動時間
	constexpr int kHardAttackRate = 3;						// 強攻撃時の攻撃力倍率
	constexpr int kKnockBackDamage = 10.0f;					// ノックバックするダメージ量
	constexpr float kMoveSpeedDashRate = 1.7f;				// ダッシュ時速度
	constexpr float kAccelerationRate = 0.5f;				// 加速度
	constexpr float kJumpMaxSpeed = 8.0f;					// ジャンプ時の最大速度
	constexpr float kGravity = 0.8f;						// 重力
	constexpr float kFallMaxSpeed = -15.0f;					// 最大落下速度
	constexpr float kNowVecNum = 0.8f;						// 現在の方向
	constexpr float kNextVecNum = 0.2f;						// 進みたい方向
	constexpr float kMinJumpRiseNum = 1.0f;					// 上昇中と判断される最低値
	constexpr float kAngleSpeed = 0.02f;					// 回転速度
	constexpr float kAttackDistance = 30.0f;				// 攻撃距離
	constexpr float kHeight = 140.0f;						// 高さ
	constexpr float kSize = 50.0f;							// サイズ
	constexpr float kTopPos = 60.0f;						// 頭高さ
	constexpr float kBottomPos = 0.0f;						// 足元座標
	constexpr float kCapsuleRadius = 15.0f;					// カプセル半径
	constexpr float kAttackRadius = 60.0f;					// 攻撃判定半径
	constexpr float kAttackHeight = 100.0f;					// 攻撃判定高さ
	constexpr float kHardRadius = 90.0f;					// 強攻撃当たり判定半径
	constexpr float kHardHeight = -50.0f;					// 強攻撃当たり判定高さ
	constexpr float kKnockBackSpeed = 5.0f;					// ノックバック速度
	constexpr float kKnockBackDecreaseSpeed = 0.2f;			// ノックバック速度減少量
	constexpr VECTOR kScaleVec = { 0.5f,1.0f,0.5f };		// スケール
	
	/// <summary>
	/// アニメーション切り替え速度
	/// </summary>
	enum kAnimChangeFrameNum
	{
		Idle = 2,
		Walk = 2,
		Dash = 2,
		Attack1 = 1,
		Attack2 = 1,
		Attack3 = 1,
		HardAttack = 1,
		JumpStart = 2,
		JumpIdle = 2,
		Damage = 2,
	};
}

Player::Player() :
	m_attackCount(0),
	m_isColl(false),
	m_isAttack(false),
	m_isHardAttack(false),
	m_isNextAttack(false),
	m_isLockOn(false),
	m_moveDirection{ 0.0f,0.0f,0.0f },
	m_attackPos{0.0f,0.0f,0.0f},
	m_pState(std::make_shared<PlayerState>(this)),
	m_pCamera(std::make_shared<Camera>()),
	m_attackStanTime(std::make_shared<Time>(kAttackStanTime)),
	m_attackInvokeTime(std::make_shared<Time>(kattackInvokeTime))
{
	// アニメーションロード
	CsvLoad::GetInstance().AnimLoad(m_animData, "Player");
	// ステータス情報初期化
	CsvLoad::GetInstance().StatusLoad(m_statusData, "Player");
	// ステータス追加
	CsvLoad::GetInstance().AddStatusLoad(m_statusData, "Player");

	// ショット作成
	m_pShot = std::make_shared<Shot>(this, m_statusData.shotAtk);

	/*移動速度初期化*/
	m_moveData.walkSpeed = m_statusData.spd;
	m_moveData.dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_moveData.acc = m_statusData.spd * kAccelerationRate;
	m_moveData.rotSpeed = kAngleSpeed;

	// モデルポインタ作成
	m_pModel = std::make_shared<Model>(kFileName);
	// モデルスケール設定
	m_pModel->SetScale(kScaleVec);
	// アニメーション初期化
	m_pModel->SetAnim(m_animData.idle, true, false);

	// モデル頂点の取得
	m_topFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(), "mixamorig:HeadTop_End");
	assert(m_topFrameIndex != -1);
	assert(m_topFrameIndex != -2);
	// モデル底辺の取得
	m_bottomFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(), "MaleBruteA_Eyes");
	assert(m_bottomFrameIndex != -1);
	assert(m_bottomFrameIndex != -2);
	// 初期ステイトの設定(待機状態から)
	m_pState->SetState(PlayerState::StateKind::Idle);

	/*情報初期化*/
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.topPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_topFrameIndex);
	m_characterInfo.bottomPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_bottomFrameIndex);
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;


	/*当たり判定ポインタ作成*/
	// プレイヤー
	m_pCollShape = std::make_shared<CollisionShape>(m_characterInfo.topPos, m_characterInfo.bottomPos, kCapsuleRadius);
	// 剣
	m_attackColl = std::make_shared<CollisionShape>(m_attackPos, kAttackRadius, kAttackHeight);
	// 強攻撃
	m_hardAtkColl = std::make_shared<CollisionShape>(m_characterInfo.topPos, kHardRadius, kHardHeight);

	// 最大HP設定
	m_maxHp = m_statusData.hp;

	// HPバー作成
	m_pHpBar = std::make_shared<HpBarPlayer>(m_statusData.hp);


	// モデルの頂点タイプの取得
	//for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	//{
	//	// 頂点タイプの取得
	//	//m_vertexShaderType.push_back(MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i));

	//	// 頂点シェーダハンドルの取得
	//	m_vertexShaderH.push_back(m_pVertexShader->
	//		SetVertexShaderH(MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i)));
	//}
}

Player::~Player()
{
	/*処理無し*/
}

void Player::Update()
{
	// ステイト更新
	m_pState->Update();
	UpdateState();

	// 移動更新
	m_characterInfo.vec = Move();
	// 重力による落下処理
	UpdateGravity();

	// アニメーション更新
	m_pModel->Update();
	// モデル座標の設定
	m_pModel->SetPos(m_characterInfo.pos);
	// モデル回転の設定
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));

	// HPバー更新
	m_pHpBar->Update();

	// カメラ更新
	UpdateCamera();

	// カメラの角度行列の取得
	MATRIX rotMtx = MGetRotY(m_pCamera->GetCameraAngleX());
	// ショットにカメラの角度行列を渡す
	m_pShot->SetCameraRot(rotMtx);
	// 遠距離攻撃武器更新
	m_pShot->Update(m_characterInfo.pos, m_angle);

	// フレーム座標の更新
	m_characterInfo.topPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_topFrameIndex);
	m_characterInfo.bottomPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_bottomFrameIndex);
	AttackPosUpdate(m_angle);
}

void Player::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	//// モデルをフレームごとに描画する
	//for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	//{
	//	// シェーダの設定
	//	pToonShader->SetShader(m_vertexShaderH[i]);

	//	// 描画
	//	MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	//}
	//// シェーダを使わない設定にする
	//pToonShader->ShaderEnd();

	m_pModel->Draw();

	// 遠距離攻撃武器描画
	m_pShot->Draw();

	// 当たり判定の描画
	m_pCollShape->DebugDraw(0xff0000);

	if (m_isAttack)
	{
		m_attackColl->DebugDraw(0x0000ff);
	}
	if (m_isHardAttack)
	{
		m_hardAtkColl->DebugDraw(0xff00ff);
	}
}

void Player::Draw2D()
{
	// HPバー描画
	m_pHpBar->Draw();

	// カメラ2D部分の描画
	m_pCamera->Draw();

#ifdef _DEBUG
	// デバッグ用描画
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標：%f,%f,%f"
		, m_characterInfo.pos.x, m_characterInfo.pos.y, m_characterInfo.pos.z);
	DrawFormatString(0, 40, 0xffffff, "ジャンプ力：%f", m_jumpPower);
	DrawFormatString(0, 180, 0xffffff, "攻撃カウント：%d", m_attackCount);
	DrawFormatString(0, 200, 0xffffff, "次攻撃フラグ：%d", m_isAttack);

	DrawFormatString(1200, 20, 0x000000, "HP:%d", m_statusData.hp);
	DrawFormatString(1200, 40, 0x000000, "MATK:%d", m_statusData.meleeAtk);
	DrawFormatString(1200, 80, 0x000000, "SATK:%d", m_statusData.shotAtk);
	DrawFormatString(1200, 100, 0x000000, "DEF:%d", m_statusData.def);
#endif // _DEBUG
}

void Player::OnDamage(VECTOR targetPos, int damagePoint)
{
	// HPを減らす
	m_statusData.hp -= damagePoint;

	// HPが0以下になって死亡状態でなかった場合
	if (m_statusData.hp <= 0 && !m_isDead)
	{
		// 死亡する
		m_isDead = true;
	}

	// ダメージを受けた状態にする
	m_isDamage = true;
}

void Player::EndJump()
{
	// ジャンプフラグをfalseにする
	m_isJump = false;
	// ジャンプ力を0にする
	m_jumpPower = 0.0f;

	// ステージクリア時は処理を終了する


	// ステイトの終了処理
	m_pState->EndState();
}

void Player::UpdateAngle()
{
	// ダメージ中は処理をしない
	if (m_pState->GetState() == PlayerState::StateKind::Damage) return;

	float nextAngle = 0.0f;

	// ロックオン状態で、ダッシュ状態ではなかった場合は
	// ロックオンされている敵の方向を向くようにする
	if (m_isLockOn && m_pState->GetState() != PlayerState::StateKind::Dash)
	{
		// ロックオンされている敵がいなかったら返る
		if (m_pObjectManager->GetLockOnEnemy() == nullptr) return;
		// プレイヤーから敵までのベクトルを出す
		VECTOR enemyToPlayer = VSub(m_pObjectManager->GetLockOnEnemy()->GetInfo().pos, m_characterInfo.pos);

		// 目標角度の計算
		nextAngle = static_cast<float>(atan2(-enemyToPlayer.z, enemyToPlayer.x) - DX_PI_F * 0.5f);
	}
	else
	{
		// 目標角度の計算(ベクトル(z,x)の角度 + 90°+ カメラ角度)
		nextAngle = static_cast<float>(atan2(static_cast<double>(m_moveDirection.z), static_cast<double>(m_moveDirection.x))
			+ DX_PI_F * 0.5f + m_pCamera->GetCameraAngleX());
	}

	// 角度を滑らかに変更する
	SmoothAngle(m_angle, nextAngle);
}

void Player::UpdateMoveDirection()
{
	// ダメージ中は処理をしない
	if (m_pState->GetState() == PlayerState::StateKind::Damage) return;

	// 移動方向ベクトルクラスの作成
	MoveDirectionVec moveDirectionVec;
	// 移動方向更新
	moveDirectionVec.Update();

	// 進みたい方向と現在の方向の線形補完
	m_moveDirection = VAdd(VScale(m_moveDirection, kNowVecNum),
		VScale(moveDirectionVec.GetDirectionVec(), kNextVecNum));

	// 進みたい方向のY軸を省く
	m_moveDirection.y = 0.0f;
}

void Player::UpdateCamera()
{
	// 左スティックが押し込まれた場合
	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		// ロックオン状態が切り替わる
		m_isLockOn = !m_isLockOn;

		// ロックオン状態だった場合
		if (m_isLockOn)
		{
			m_pObjectManager->InitLockOnEnemy();
		}
	}

	// ロックオンされていた敵が消えたらロックオンを解除する
	if (m_pObjectManager->GetLockOnEnemy() != nullptr)
	{
		// 存在フラグが立っていなかった場合
		if (!m_pObjectManager->GetLockOnEnemy()->GetInfo().isExist)
		{
			// ロックオン状態を解除する
			m_isLockOn = false;
		}
	}
	else
	{
		// ロックオン状態を解除する
		m_isLockOn = false;
	}

	// ロックオン状態の場合
	if (m_isLockOn)
	{
		// カメラに敵の座標を渡す
		m_pCamera->SetLockOnEnemyPos(m_pObjectManager->GetLockOnEnemy()->GetInfo().pos);
	}

	// カメラ更新
	m_pCamera->Update(m_characterInfo.pos, m_isLockOn);
}

VECTOR Player::Move()
{
	// 移動速度が0の場合は何もしない
	if (m_moveSpeed == 0.0f)return VGet(0.0f, 0.0f, 0.0f);

	// 移動方向更新
	UpdateMoveDirection();
	// 角度更新
	UpdateAngle();

	// 移動ベクトルの生成
	VECTOR move = VNorm(m_moveDirection);

	// ダメージ中の処理
	if (m_pState->GetState() == PlayerState::StateKind::Damage)
	{
		return move;
	}

	// 移動ベクトルに速度をかける
	// X軸は反転させる(カメラの角度を変えた時に移動方向がおかしくならないように)
	move.x *= -m_moveSpeed;
	move.z *= m_moveSpeed;

	/*カメラの角度によって進む方向を変える*/
	// カメラの角度行列を取得する
	MATRIX rotMtx = MGetRotY(m_pCamera->GetCameraAngleX());

	// 移動ベクトルとカメラ角度行列をかける
	move = VTransform(move, rotMtx);

	return move;
}

void Player::InitState()
{
	/*現在のステイトによって初期化処理を変える*/
	switch (m_pState->GetState())
	{
	case PlayerState::StateKind::Attack:

		m_attackStanTime->Reset();		// 硬直時間のリセット
		m_attackCount = 0;				// 攻撃回数のリセット

		//	攻撃フラグを立てる
		m_isAttack = true;
		// 次の攻撃をするかどうかのフラグをfalseにする
		m_isNextAttack = false;
		// 攻撃判定リセットフラグを立てる
		m_isResetAttack = true;

		break;

	case PlayerState::StateKind::HardAttack:

		// 強攻撃フラグを立てる
		m_isHardAttack = true;

		break;

	case PlayerState::StateKind::Jump:
		// ジャンプフラグを立てる
		m_isJump = true;
		// ジャンプ力を設定する
		m_jumpPower = kJumpMaxSpeed;
		// ジャンプ音を鳴らす

		break;
	default:
		// 上記以外だった場合は何もしない
		break;
	}
}

void Player::OnAttack(CharacterBase* pEnemy)
{
	// 攻撃中以外または衝突中は処理をしない
	if (!m_isAttack || m_isColl) return;
	// 当たり判定は少し時間が経過してから取る
	if (m_attackInvokeTime->Update())
	{
		// 衝突判定
		if (m_attackColl->IsCollide(pEnemy->GetCollShape()))
		{
			// 当たっていたらダメージを与える
			pEnemy->OnDamage(m_characterInfo.pos, m_statusData.meleeAtk);
			m_isColl = true;
			m_isAttack = true;
			// 硬直時間のリセット
			m_attackInvokeTime->Reset();
		}
	}
}

void Player::OnHardAttack(CharacterBase* pEnemy)
{
	// 強攻撃中以外は処理をしない
	if (!m_isHardAttack) return;

	// 当たり判定は少し時間が経過してから取る
	if (m_attackInvokeTime->Update())
	{
		// 衝突判定
		if (m_hardAtkColl->IsCollide(pEnemy->GetCollShape()))
		{
			// 当たっていたらダメージを与える
			pEnemy->OnDamage(m_characterInfo.pos, m_statusData.meleeAtk * kHardAttackRate);
			m_isHardAttack = true;
			// 硬直時間のリセット
			m_attackInvokeTime->Reset();
		}
	}
}

void Player::OnRecovery(int recoveryNum)
{
		// HP回復
		m_statusData.hp += recoveryNum;
		// 最大HP以上にはならないようにする
		if (m_statusData.hp >= m_maxHp)
		{
			m_statusData.hp = m_maxHp;
		}
		// HPバー回復
		m_pHpBar->OnRecoveryHp(recoveryNum);
}

void Player::UpdateState()
{
	/*現在のステイトによって更新処理を変える*/
	switch (m_pState->GetState())
	{
	case PlayerState::StateKind::Idle:	// 待機
		// 段々減速する
		m_moveSpeed = max(m_moveSpeed - m_moveData.acc, 0.0f);
		// アニメーションを待機状態に変更する
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimChangeFrameNum::Idle);
		break;

	case PlayerState::StateKind::Walk:	// 歩き
		// 移動速度を歩き状態の速度に変更する
		m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.walkSpeed);
		// アニメーションを歩きアニメーションに変更する
		m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimChangeFrameNum::Walk);
		break;

	case PlayerState::StateKind::Dash:	// ダッシュ
		// 移動速度をダッシュ時の速度にする
		m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.dashSpeed);
		// アニメーションをダッシュアニメーションに変更する
		m_pModel->ChangeAnim(m_animData.run, true, false, kAnimChangeFrameNum::Dash);
		break;

	case PlayerState::StateKind::Attack:	// 攻撃
		// 攻撃更新
		UpdateAttack();
		break;

	case PlayerState::StateKind::HardAttack:	// 強攻撃
		// 強攻撃更新
		UpdateHardAttack();
		break;

	case PlayerState::StateKind::Jump:	// ジャンプ
		// 移動速度を変更する
		//m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.walkSpeed);

		// 上昇中
		//if (m_jumpPower > kMinJumpRiseNum)
		//{
		//	// アニメーションをジャンプ開始アニメーションに切り替える
		//	m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::JumpStart);
		//}
		//// 空中にとどまっている、下降中
		//else
		//{
			// アニメーションをジャンプ待機アニメーションに切り替える
		m_pModel->ChangeAnim(m_animData.jumpIdle, true, false, kAnimChangeFrameNum::JumpIdle);
		//}
		break;

	case PlayerState::StateKind::Damage:	// ダメージ

		break;

	default:
		// 上記以外だった場合は何もしない
		break;
	}
}

void Player::UpdateAttack()
{
	// 止まる
	m_moveSpeed = 0.0f;

	// 攻撃回数によってアニメーションを変更する
	switch (m_attackCount % 3)
	{
	case 0:
		m_pModel->ChangeAnim(m_animData.attack1, false, false, kAnimChangeFrameNum::Attack1);
		break;

	case 1:
		m_pModel->ChangeAnim(m_animData.attack2, false, false, kAnimChangeFrameNum::Attack2);
		break;

	case 2:
		m_pModel->ChangeAnim(m_animData.attack3, false, false, kAnimChangeFrameNum::Attack3);
		break;

	default:
		break;
	}

	if (m_attackStanTime->Update())
	{
		// 攻撃中に攻撃ボタンが押された場合
		if (Pad::IsTrigger(PAD_INPUT_3) && !m_isNextAttack)
		{
			// 次に攻撃するフラグを立てる
			m_isNextAttack = true;
		}
	}

	// アニメーションが終わった段階で次に攻撃するフラグが立っていなかった場合
	if (m_pModel->IsAnimEnd() && !m_isNextAttack)
	{
		// 衝突フラグをfalseにする
		m_isColl = false;
		// 攻撃を終了する
		m_isAttack = false;
		// 硬直時間をリセットする
		m_attackStanTime->Reset();
		// 攻撃カウントをリセットする
		m_attackCount = 0;
		// ステイトを終了する
		m_pState->EndState();
		// 発動時間リセット
		m_attackInvokeTime->Reset();
		
	}
	// アニメーションが終わった段階で次に攻撃するフラグが立っていた場合
	if (m_pModel->IsAnimEnd() && m_isNextAttack)
	{
		// 衝突フラグをfalseにする
		m_isColl = false;
		// 攻撃判定の初期化
		m_isResetAttack = true;
		// 硬直時間のリセット
		m_attackStanTime->Reset();
		// 次の攻撃をするフラグをfalseにする
		m_isNextAttack = false;
		// 攻撃カウントを増やす
		m_attackCount++;
		// 発動時間リセット
		m_attackInvokeTime->Reset();
		// SEを鳴らす
	}
}

void Player::UpdateHardAttack()
{
	// 止まる
	m_moveSpeed = 0.0f;

	// アニメーションを再生する
	m_pModel->ChangeAnim(m_animData.hardAttack, false, false, kAnimChangeFrameNum::HardAttack);

	// アニメーションが終わった場合
	if (m_pModel->IsAnimEnd())
	{
		// ステイト終了
		m_pState->EndState();
		// 強攻撃フラグをfalseにする
		m_isHardAttack = false;
	}
}

void Player::AttackPosUpdate(float angle)
{
	// 向いている方向を出す
	VECTOR vec = VGet(sinf(angle + DX_PI_F), 0.0f, cosf(angle + DX_PI_F));
	// 前に出す
	vec = VScale(vec, kAttackDistance);
	// 出したベクトルを現在位置に足す
	m_attackPos = VAdd(m_characterInfo.bottomPos, vec);
}
