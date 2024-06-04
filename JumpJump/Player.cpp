#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Stage/StageTest.h"
#include "Util/Input.h"

#include <math.h>
#include <cassert>

/// <summary>
/// 定数定義
/// </summary>
namespace
{
	constexpr float kMoveSpeed = 1.0f;			// 移動速度
	constexpr float kAngleSpeed = 0.2f;			// 回転速度
	constexpr float kJunpPower = 8.5f;			// ジャンプ力
	constexpr float kFallUpPower = 0.6f;		// 足を踏み外したときのジャンプ力
	constexpr float kGravity = 0.5f;			// 重力
	constexpr float kPlayAnimSpeed = 0.5f;	// アニメーションの速度
	constexpr float kAnimBlendSpeed = 0.1f;		// アニメーションのブレンド率の変化速度

}

Player::Player():
	m_pos{0.0f,0.0f,0.0f},
	m_targetDir{1.0f,0.0f,0.0f},
	m_angle(0.0f),
	m_nowJunpPower(0.0f),
	m_modelHandle(-1),
	m_state(State::Idle),
	m_nowPlayAnim(1),
	m_prevPlayAnim(1),
	m_nowAnimCount(0.0f),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f),
	m_isMove(false)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/Player/Knight.mv1");
	assert(m_modelHandle != -1);
}

Player::~Player()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	MV1SetScale(m_modelHandle, VGet(3, 3, 3));

}

void Player::Update(const Input& input, const Camera& camera, StageTest& stage)
{
	// ルートフレームのZ軸方向の移動パラメーターを無効にする
	//DisableRootFrameZMove();

	/* 移動パラメーターの設定 */
	// ↑ボタンを押したときの移動方向ベクトル
	VECTOR upMoveVec;
	// ←ボタンを押したときの移動方向ベクトル
	VECTOR leftMoveVec;
	// このフレームでの移動ベクトル
	VECTOR moveVec;
	// 現在の状態
	State prevState = m_state;
	m_state = UpdateMoveParamerer(input, camera, upMoveVec, leftMoveVec, moveVec);

	// アニメーションステートの更新
	UpdateAnimationState(prevState);

	// 移動方向にモデルを近づける
	UpdateAngle();


	// 移動ベクトルを元に当たり判定を考慮しながらプレイヤーを移動させる
	Move(moveVec,stage);

	//アニメーション処理
	UpdateAnimation();

}

void Player::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "Playerx:%f,y:%f,z:%f",m_pos.x, m_pos.y, m_pos.z);

	MV1DrawModel(m_modelHandle);
}

void Player::End()
{

}

void Player::OnHitRoof()
{
	// Y軸方向の速度を反転させる
	m_nowJunpPower = -m_nowJunpPower;

}

void Player::OnHitFloor()
{
	// Y軸方向の移動速度は0にする
	m_nowJunpPower = 0.0f;

	// もしジャンプ中だった場合は着地状態にする
	if (m_state == State::Jump)
	{
		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
		if (m_isMove)
		{
			// 移動している場合は走り状態になる
			m_state = State::Run;
		}
		else
		{
			// 移動していない場合は立ち止まり状態になる
			m_state = State::Idle;
		}

		// 着地時はアニメーションのブレンドを行わない
		
	}

}

void Player::OnFall()
{
	if (m_state != State::Jump)
	{
		// ジャンプ中にする
		m_state = State::Jump;

		// ちょっとだけジャンプする
		m_nowJunpPower = kFallUpPower;

		// アニメーションを落下中のものにする

	}
}

void Player::DisableRootFrameZMove()
{
	MATRIX localMatrix;

	// ユーザー行列を解除する
	MV1ResetFrameUserLocalMatrix(m_modelHandle, 2);

	// 現在のルートフレームの行列を取得する
	localMatrix = MV1GetFrameLocalMatrix(m_modelHandle, 2);

	// Z軸方向の平行移動成分を無効にする
	localMatrix.m[3][2] = 0.0f;

	// ユーザー行列として平行移動成分を無効にした行列をルートフレームにセットする
	MV1SetFrameUserLocalMatrix(m_modelHandle, 2, localMatrix);


}

Player::State Player::UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	State nextState = m_state;

	// プレイヤーの移動方向のベクトルを算出する
	// ↑ボタンを押したときのプレイヤーの移動ベクトルは、
	// カメラの視線方向からY成分を抜いたもの
	upMoveVec = VSub(camera.GetTarget(), camera.GetPos());
	upMoveVec.y = 0.0f;

	// ←ボタンを押したときのプレイヤーの移動ベクトルは、
	// 上を押したときの方向ベクトルとY軸のプラス方向のベクトルに垂直な方向
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// 二つのベクトルを正規化する
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// 今のフレームでの移動ベクトルを初期化する
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したかのフラグを初期状態ではfalseにする
	bool isMove = false;

	// 左ボタンが入力されたらカメラの見ている方向から見て左に移動する
	if (input.IsPressing("left"))
	{
		// 移動ベクトルに左が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, leftMoveVec);

		// 移動フラグをtrueにする
		isMove = true;
	}
	// 右ボタンが入力されたらカメラの見ている方向から見て右に移動する
	else if(input.IsPressing("right"))
	{
		// 移動ベクトルに左が入力された時の移動ベクトルを反転(マイナス)した物を加算する
		moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));

		// 移動フラグをtrueにする
		isMove = true;
	}

	// 上ボタンが入力されたらカメラの見ている方向に移動する
	if (input.IsPressing("up"))
	{
		// 移動ベクトルに上が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, upMoveVec);

		// 移動フラグをtrueにする
		isMove = true;
	}
	// 下ボタンが入力されたらカメラの方向に移動する
	else if (input.IsPressing("down"))
	{
		// 移動ベクトルに上が入力された時の移動ベクトルを反転(マイナス)した物を加算する
		moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));

		// 移動フラグをtrueにする
		isMove = true;
	}

	// ジャンプしていない状態でAボタンが押されていた場合はジャンプをする
	if (m_state != State::Jump && (input.IsTriggered("A")))
	{
		// Y軸方向の速度をセットする
		m_nowJunpPower = kJunpPower;

		// 状態をジャンプにする
		nextState = State::Jump;
	}

	// ジャンプしている状態だった場合は重力を適用する
	if (m_state == State::Jump)
	{
		m_nowJunpPower -= kGravity;
	}

	if (isMove)// 移動ボタンが押されていた場合
	{
		if (m_state == State::Idle)	// 今の状態が立ち止まっている状態だった場合
		{
			// 今の状態を走り状態にする
			nextState = State::Run;
		}

		// 移動ベクトルを正規化したものをプレイヤーが向く方向として保存する
		m_targetDir = VNorm(moveVec);

		// プレイヤーが向いている方向のベクトルにスピードを掛けたものを移動ベクトルにする
		moveVec = VScale(m_targetDir, kMoveSpeed);
	}
	else
	{
		// このフレームで走っている状態だった場合
		if (m_state == State::Run)
		{
			// 立ち止まる状態にする
			nextState = State::Idle;
		}
	}

	// 移動ベクトルのy成分をy軸方向の速度にする
	moveVec.y = m_nowJunpPower;

	return nextState;
}

void Player::Move(const VECTOR& moveVec, StageTest& stage)
{
	// 移動距離が0.01未満の場合は少しずつ移動してバグるため、
	// 0.01以上移動していた場合は移動したかのフラグをtrueにしておく
	// fabs：floatの絶対値(absだとint型になる)
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	m_pos = stage.CheckCollision(*this, moveVec);

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}

void Player::UpdateAngle()
{
	// プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;		// 目標角度
	float difference;		// 目標角度と現在の角度の差

	// 目標の方向ベクトルから角度値を出す
	// 座標からタンジェントを使って角度を求めている
	targetAngle = static_cast<float>(atan2(m_targetDir.x, m_targetDir.z));

	// 目標の角度と現在の角度との差を割り出す
	// 最初は引き算で出す
	difference = targetAngle - m_angle;

	// ある方向からある方向差が180°以上になることは無い
	// そのため、差の値が180°以上になっていたら修正しておく
	if (difference < -DX_PI_F)// -180以下だったら360を足す
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)// 180以上だったら360を引く
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差を0に近づける
	if (difference > 0.0f)// 差がプラスの場合は引く
	{
		difference -= kAngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else// 差がマイナスの場合は足す
	{
		difference += kAngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新する
	m_angle = targetAngle - difference;
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));

}

void Player::UpdateAnimationState(State prevState)
{
	// 立ち止まり状態から走り状態に変わった
	if (prevState == State::Idle && m_state == State::Run)
	{
		// 走るアニメーションの再生
		PlayAnimation(AnimKind::Run);
	}
	// 走り状態から立ち止まり状態に変わった
	else if (prevState == State::Run && m_state == State::Idle)
	{
		// 立ち止まるアニメーションの再生
		PlayAnimation(AnimKind::Stop);
	}
	// ジャンプ状態だった場合
	else if (m_state == State::Jump)
	{
		// 落下していてアニメーションが上昇中用の物だった場合
		if (m_nowJunpPower < 0.0f)
		{
			bool isJumpAnim = MV1GetAttachAnim(m_modelHandle, m_nowPlayAnim) == static_cast<int>(AnimKind::Jump);
			// 落下中用アニメーションを再生する
			if (isJumpAnim)
			{
				PlayAnimation(AnimKind::Fall);
			}
		}
		else
		{
			PlayAnimation(AnimKind::Jump);
		}
	}
}

void Player::PlayAnimation(AnimKind nextPlayAnim)
{
	// 直前に再生していたアニメーションとの入れ替えをするので、
	// 1つ前のモーションが有効だった場合はデタッチする
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	m_prevPlayAnim = m_nowPlayAnim;
	m_prevAnimCount = m_nowAnimCount;

	// 新しく指定したモーションをモデルにアタッチしてアタッチ番号を保存する
	m_nowPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(nextPlayAnim));

	// Prevが有効ではない場合はm_animBlendRate(ブレンド率)を1.0fにする
	m_animBlendRate = m_prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void Player::UpdateAnimation()
{
	// 再生しているアニメーションの総時間
	float animTotalTime;

	// ブレンド率が1以下の場合は1に近づける
	if (m_animBlendRate < 1.0f)
	{
		m_animBlendRate += kAnimBlendSpeed;
		if (m_animBlendRate > 1.0f)
		{
			m_animBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション1の処理
	if (m_nowPlayAnim != -1)	// 現在のアニメーション番号が-1(無し)でない場合
	{
		// アニメーションの総時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_nowPlayAnim);

		// 再生時間を進める
		m_nowAnimCount += kPlayAnimSpeed;

		// ループ処理
		if (m_nowAnimCount >= animTotalTime)
		{
			// 剰余(%)
			m_nowAnimCount = static_cast<float>(fmod(m_nowAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_modelHandle, m_nowPlayAnim, m_nowAnimCount);

		// アニメーション1のモデルに対する反映率をセットする
		MV1SetAttachAnimBlendRate(m_modelHandle, m_nowPlayAnim, m_animBlendRate);
	}

	// 再生しているアニメーション2の処理
	if (m_prevPlayAnim != -1)
	{
		// アニメーションの総時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_prevPlayAnim);

		// 再生時間を進める
		m_prevAnimCount += kPlayAnimSpeed;

		// ループ処理
		if (m_prevAnimCount > animTotalTime)
		{
			m_prevAnimCount = static_cast<float>(fmod(m_prevAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_modelHandle, m_prevPlayAnim, m_prevAnimCount);

		// アニメーション2のモデルの対する反映率をセットする
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevPlayAnim, 1.0f - m_animBlendRate);
	}


}
