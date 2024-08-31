#include "Player_.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"
#include "../Model.h"
#include "../Camera.h"
#include "../Circle.h"

#include "../../Util/Input.h"
#include "../../Util/Pad.h"
#include "../../Util/Time.h"
#include "../../Util/MoveDirectionVec.h"
#include "../../Util/CsvLoad.h"

#include "../../Shader/ToonShader.h"

#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";
	constexpr float kSize = 15.0f;
	constexpr float kModelScale = 0.11f;
	constexpr float kFallBackPosY = -800.0f;
	/*スピード関係*/
	constexpr float kMoveSpeedDashRate = 1.2f;
	constexpr float kAccelerationRate = 0.5f;
	/*ジャンプ関係*/
	constexpr float kJumpMaxSpeed = 8.0f;
	constexpr float kGravity = 0.8f;
	constexpr float kFallMaxSpeed = -15.0f;
	constexpr float kAttackHitJumpSpeed = 3.0f;

	constexpr float kPlayerAngleSpeed = 0.02f;			// プレイヤーの回転速度
	constexpr int kInvinvibleTime = 60;					// 無敵時間
	constexpr float kKnockBackSpeed = 10.0f;			// ノックバックのスピード
	constexpr float kKnockBackSpeedDecrease = 0.2f;		// ノックバックスピード減少量
	constexpr float kHeight = 35.0f;					// 高さ

	/*移動の補完値*/
	constexpr float kNowVecNum = 0.8f;
	constexpr float kNextVecNum = 0.2f;

	constexpr float kDrawDistance = 50.0f;				// 描画可能距離

	constexpr float kEnemyHeadPos = 20;					// 敵の頭の位置

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

Player_::Player_():
	m_walkSpeed(0),
	m_dashSpeed(0),
	m_acc(0),
	m_isMove(false),
	m_isDash(false),
	m_moveDirectVec{0,0,0},
	m_cameraToPlayerVec{0,0,0},
	m_currentState(State::Idle)
{
	// アニメーションの初期化
	CsvLoad::GetInstance().AnimLoad(m_animData, "Player");

	/*移動スピードの初期化*/
	m_walkSpeed = m_statusData.spd;
	m_dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_acc = m_statusData.spd * kAccelerationRate;

	/*情報初期化*/
	m_info.pos = VGet(0.0f, 0.0f, 0.0f);
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;

	/*モデル関係初期化*/
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pModel->SetAnim(m_animData.idle, false, true);
	m_pModel->SetScale(VGet(kModelScale, kModelScale, kModelScale));

	/*ポインタ作成*/
	m_pInvincibleTime = std::make_shared<Time>(kInvinvibleTime);
	m_pCamera = std::make_shared<Camera>();
	m_pCircle = std::make_shared<Circle>(m_info.pos, kSize, kHeight * 0.5f);
}

Player_::~Player_()
{
	/*処理無し*/
}

void Player_::Init()
{
	/*処理無し*/
}

void Player_::Update(Input& input)
{
	/*移動パラメータの設定*/
	VECTOR upMoveVec;
	VECTOR leftMoveVec;
	VECTOR moveVec;

	/*現在の状態更新*/
	// 前フレームの状態をいれる
	State prevState = m_currentState;
	// 現在の状態をいれる
	m_currentState = UpdateMoveParamerer(upMoveVec, leftMoveVec, moveVec);

	// アニメーションの更新
	m_pModel->Update();

	// カメラの更新
	m_pCamera->Update(m_info.pos);
	// プレイヤーからカメラまでの処理の更新
	m_cameraToPlayerVec = VSub(m_info.pos, m_pCamera->GetPos());

	// 落ちたら初期位置に戻る
	if (m_info.pos.y <= kFallBackPosY)
	{
		m_info.pos = VGet(0.0f, 0.0f, 0.0f);
		EndJump();
	}

}

void Player_::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	//モデルのフレームごとに描画をする
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		pToonShader->SetShader(shaderType);

		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	pToonShader->ShaderEnd();

	// デバッグ用当たり判定の球
	m_pCircle->DebugDraw();
}

void Player_::Draw2D()
{
	m_pCamera->Draw();

#ifdef _DEBUG
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標：%f,%f,%f"
		, m_info.pos.x, m_info.pos.y, m_info.pos.z);
	DrawFormatString(0, 100, 0x000000, "ジャンプ力：%f", m_jumpPower);
#endif // _DEBUG
}

void Player_::StageClear()
{
}

void Player_::OnDamage(VECTOR targetPos)
{
	// ゲームクリア状態だったら何もせずに終了する
	if (m_pObjectManager->IsGameClear())return;
	// 敵のY位置が自分の位置より低かった場合は何もしない
	if (targetPos.y <= m_info.pos.y - kEnemyHeadPos)return;
	// 現在の状態がノックバックの時は何もしない
	if (m_currentState == State::KnockBack) return;

	// 現在の状態をノックバック状態にする
	m_currentState = State::KnockBack;

	// ノックバックのスピードと方向を計算する
	m_moveSpeed = kKnockBackSpeed;
	m_isDamage = true;	

	m_moveDirectVec = VNorm(VSub(
		VGet(m_info.pos.x, 0.0f, m_info.pos.z),
		VGet(targetPos.x, 0.0f, targetPos.z)));

	// シェーダをONにする

	// ダメージ音を鳴らす
}

void Player_::OnAttack()
{
	// 攻撃音を鳴らす


	m_jumpPower = kAttackHitJumpSpeed;
	m_currentState = State::Jump;
}

void Player_::EndJump()
{
	m_isJump = false;
	m_jumpPower = 0.0f;
	// 着地音を鳴らす

	// もしジャンプ中だった場合は着地状態にする
	if (m_currentState == State::Jump)
	{
		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
		if (m_isMove)	// 移動していた場合
		{
			// 歩き状態になる
			m_currentState = State::Walk;
			m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
		}
		else // 移動していなかった場合
		{
			// 待機状態になる
			m_currentState = State::Idle;
			m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		}
	}

}

void Player_::AngleUpdate()
{
}

Player_::State Player_::UpdateMoveParamerer(VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	// 次の状態
	State nextState = m_currentState;

	// プレイヤーの移動方向のベクトルを算出する
	// ↑ボタンを押したときのプレイヤーの移動ベクトルは、
	// カメラの視線方向からY成分を抜いたもの
	upMoveVec = VSub(m_pCamera->GetTarget(), m_pCamera->GetPos());
	upMoveVec.y = 0.0f;
	// ←ボタンを押したときのプレイヤーの移動ベクトルは、
	// 上を押したときの方向ベクトルとY軸のプラス方向のベクトルに垂直な方向
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));
	// 二つのベクトルを正規化する
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);
	// 今のフレームでの移動ベクトルを初期化する
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したかどうかのフラグを作る
	bool isMove = false;
	// ダッシュ中かどうか
	m_isDash = Pad::isPress(PAD_INPUT_1);

	// 移動ボタンが何かしら押されていた場合
	if (Pad::isPress(PAD_INPUT_LEFT) || Pad::isPress(PAD_INPUT_RIGHT) ||
		Pad::isPress(PAD_INPUT_UP) || Pad::isPress(PAD_INPUT_DOWN))
	{
		isMove = true;
	}

	// 移動ボタンが押されていた場合
	if (isMove)
	{
		if (m_currentState == State::Idle ||
			m_currentState == State::Walk ||
			m_currentState == State::Dash)
		{
			// ダッシュボタンが押されていたらダッシュ状態にする
			nextState = m_isDash ? State::Dash : State::Walk;
		}
	}
	else
	{
		// このフレームで動いている状態だった場合
		if (m_currentState == State::Walk || m_currentState == State::Dash)
		{
			// 待機状態にする
			nextState = State::Idle;
		}
	}

	// ジャンプ状態でない状態でジャンプボタンが押されていたらジャンプ状態になる
	if (m_currentState != State::Jump && Pad::isTrigger(PAD_INPUT_2))
	{
		// ジャンプ状態にする
		nextState = State::Jump;
		m_isJump = true;
		m_jumpPower = kJumpMaxSpeed;
		// ジャンプ音を鳴らす

	}

	return nextState;
}

VECTOR Player_::MoveUpdate(Input& input)
{
	// 移動距離が0.01未満の場合は少しずつ移動してバグるため、
	// 0.01以上移動していた場合は移動したかのフラグをtrueにしておく
	// fabs：floatの絶対値(absだとint型になる)
	if (fabs(m_moveSpeed) > 0.01f || fabs(m_moveSpeed) > 0.01f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}
	if (!m_isMove) return VGet(0.0f,0.0f,0.0f);

	// 移動方向の更新
	MoveDirectionUpdate(input);
	// 角度の更新
	AngleUpdate();

	// 移動ベクトルの生成
	VECTOR move = VNorm(m_moveDirectVec);

	// ノックバック中の処理
	if (m_currentState == State::KnockBack)
	{
		move.x *= m_moveSpeed;
		move.z *= m_moveSpeed;

		return move;
	}

	/*状態ごとのスピードの計算*/
	if (m_currentState == State::Idle)
	{
		m_moveSpeed = max(m_moveSpeed - m_acc, 0.0f);
	}
	else if (m_currentState == State::Walk)
	{
		m_moveSpeed = min(m_moveSpeed + m_acc, m_walkSpeed);
	}
	else if (m_currentState == State::Dash)
	{
		m_moveSpeed = m_dashSpeed;
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

void Player_::MoveDirectionUpdate(Input& input)
{
	// ノックバック中は処理をせずに終了する
	if (m_currentState == State::KnockBack) return;

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

void Player_::UpdateAnimState(State prevState)
{
	/*待機から*/
	// 待機から歩き状態
	if (prevState == State::Idle && m_currentState == State::Walk)
	{
		// 歩きアニメーションの再生
		m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
	}
	// 待機から走り状態
	else if (prevState == State::Idle && m_currentState == State::Dash)
	{
		// 走りアニメーションの再生
		m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);
	}
	// 待機からジャンプ
	else if (prevState == State::Idle && m_currentState == State::Jump)
	{
		// ジャンプアニメーションの再生
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// 待機からノックバック
	else if (prevState == State::Idle && m_currentState == State::KnockBack)
	{
		// ノックバックアニメーションの再生
		m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	}

	/*歩きから*/
	// 歩きから待機
	else if (prevState == State::Walk && m_currentState == State::Idle)
	{
		// 待機アニメーションの再生
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
	}
	// 歩きから走り
	else if (prevState == State::Walk && m_currentState == State::Dash)
	{
		// 走りアニメーションの再生
		m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);
	}
	// 歩きからジャンプ
	else if (prevState == State::Walk && m_currentState == State::Jump)
	{
		// ジャンプアニメーションの再生
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// 歩きからノックバック
	else if (prevState == State::Walk && m_currentState == State::KnockBack)
	{
		// ノックバックアニメーションの再生
		m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	}

	/*走りから*/
	// 走りから待機
	else if (prevState == State::Dash && m_currentState == State::Idle)
	{
		// 待機アニメーションの再生
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
	}
	// 走りから歩き
	else if (prevState == State::Dash && m_currentState == State::Walk)
	{
		// 歩きアニメーションの再生
		m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
	}
	// 走りからジャンプ
	else if (prevState == State::Dash && m_currentState == State::Jump)
	{
		// ジャンプアニメーションの再生
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// 走りからノックバック
	else if (prevState == State::Dash && m_currentState == State::KnockBack)
	{
		// ノックバックアニメーションの再生
		m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	}

	// ノックバック状態だった場合
	else if (m_currentState == State::KnockBack)
	{
		// アニメーションが終わったら待機状態に戻る
		if (m_pModel->IsAnimEnd())
		{
			m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		}
	}

	// ジャンプ状態だった場合
	else if (m_currentState == State::Jump)
	{
		if (m_pModel->IsAnimEnd())
		{
			m_pModel->ChangeAnim(m_animData.jumpIdle, true, false, kAnimSpeed::Jump);
		}
	}

}
