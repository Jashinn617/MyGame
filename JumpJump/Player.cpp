#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Stage/StageTest.h"
#include "Util/Input.h"

#include <math.h>
#include <cassert>

Player::Player():
	m_pos{0.0f,0.0f,0.0f},
	m_targetDir{1.0f,0.0f,0.0f},
	m_angle(0.0f),
	m_nowJunpPower(0.0f),
	m_modelHandle(-1),
	m_state(State::Idle),
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

void Player::Update(const Input& input, const Camera& camera)
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

	// 移動方向にモデルを近づける
	UpdateAngle();


	// 移動ベクトルを元に当たり判定を考慮しながらプレイヤーを移動させる
	Move(moveVec);

	//アニメーション処理


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

void Player::Move(const VECTOR& moveVec)
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

	m_pos = VAdd(m_pos, moveVec);

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
