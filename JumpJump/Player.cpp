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
	constexpr float kMoveSpeed = 1.0f;				// 移動速度
	constexpr float kDashSpeed = 2.0f;				// ダッシュ時の移動速度
	constexpr float kLackStaminaSpeed = 0.1f;		// スタミナ不足状態時の移動速度
	constexpr float kAngleSpeed = 0.2f;				// 回転速度
	constexpr float kJunpPower = 5.0f;				// ジャンプ力
	constexpr float kFallUpPower = 2.0f;			// 足を踏み外したときのジャンプ力
	constexpr float kGravity = 0.3f;				// 重力
	constexpr float kPlayAnimSpeed = 0.5f;			// アニメーションの速度
	constexpr float kAnimBlendSpeed = 0.1f;			// アニメーションのブレンド率の変化速度
	constexpr float kModelScale = 0.02f;				// モデルのスケール
	constexpr float kFall = 3.0f;					// 落下判定が入る高さ
	constexpr float kMaxStamina = 100.0f;			// スタミナの最大値
	constexpr float kDecreaseStaminaSpeed = 0.5f;	// スタミナが減る速度
	constexpr float kIncreaseStaminaSpeed = 0.5f;	// スタミナが増える速度
	constexpr float kDecreaseJumpStamina = 30.0f;	// ジャンプで減るスタミナの量
	constexpr float kRadius = 2.5f;					// 半径
	

	// アニメーションの切り替えにかかるフレーム数
	static constexpr float kAnimChangeFrame = 8.0f;
	// アニメーションを切り替える速度
	static constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

}

Player::Player() :
	m_pos{ 0.0f,100.0f,0.0f },
	m_targetDir{ 1.0f,0.0f,0.0f },
	m_angle(0.0f),
	m_nowJunpPower(0.0f),
	m_stamina(kMaxStamina),
	m_modelHandle(-1),
	m_currentState(State::Idle),
	m_currentAnimNo(-1),
	m_prevAnimNo(-1),
	m_nowAnimCount(0.0f),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f),
	m_isMove(false),
	m_isLackStamina(false),
	m_isDash(false)
{
	/*処理無し*/
}

Player::~Player()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
	// シェーダのデリート
	InitShader();
}

void Player::Init()
{
	// モデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/Player/Character.mv1");
	assert(m_modelHandle != -1);
	// シェーダのロード
	m_psHs.push_back(LoadPixelShader("MV1PixelShader.pso"));
	assert(m_psHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader4Frame.vso"));
	assert(m_vsHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader8Frame.vso"));
	assert(m_vsHs.back() != -1);

	// モデルのスケールの設定
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));

	// 初期のアニメーションの設定
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, static_cast<int>(AnimKind::Idle), -1, false);

	// モデルのトライアングルリスト毎に対応するシェーダを設定する
	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		switch (MV1GetTriangleListVertexType(m_modelHandle, i))
		{
		case DX_MV1_VERTEX_TYPE_4FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(0);
			break;
		case DX_MV1_VERTEX_TYPE_8FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(1);
			break;
		default:
			m_pixelShaderNumbers.push_back(-1);
			m_vertexShaderNumbers.push_back(-1);
			break;
		}
	}
}

void Player::Update(const Input& input, const Camera& camera, StageTest& stage)
{
	// ルートフレームのZ軸方向の移動パラメーターを無効にする
	DisableRootFrameZMove();

	/* 移動パラメーターの設定 */
	// ↑ボタンを押したときの移動方向ベクトル
	VECTOR upMoveVec;
	// ←ボタンを押したときの移動方向ベクトル
	VECTOR leftMoveVec;
	// このフレームでの移動ベクトル
	VECTOR moveVec;
	// 現在の状態の更新
	State prevState = m_currentState;
	m_currentState = UpdateMoveParamerer(input, camera, upMoveVec, leftMoveVec, moveVec);

	// アニメーションの切り替え
	if (m_prevAnimNo != -1)
	{
		// 8フレームでアニメーションを切り替える
		m_animBlendRate += kAnimChangeRateSpeed;
		if (m_animBlendRate >= 1.0f) m_animBlendRate = 1.0f;

		// 変更後のアニメーション割合を設定する
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);
	}

	// アニメーションの更新
	UpdateAnimationState(prevState);
	// アニメーションを進める
	LoopAnim(m_currentAnimNo);

	// 移動方向にモデルを近づける
	UpdateAngle();

	// 移動ベクトルを元に当たり判定を考慮しながらプレイヤーを移動させる
	Move(moveVec, stage);

	Stamina();
}

void Player::Draw()
{
	// プレイヤーの位置とスタミナのデバッグ表示
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "PlayerPos x:%f,y:%f,z:%f	Stamina %f", m_pos.x, m_pos.y, m_pos.z, m_stamina);

	DrawSphere3D(VAdd(m_pos, VGet(0, kRadius, 0)), kRadius, 32, 0x00ffff, 0x00ffff, false);
#endif // _DEBUG	

	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		if (m_vertexShaderNumbers[i] && m_pixelShaderNumbers[i] == -1)
		{
			MV1SetUseOrigShader(false);
			SetUseVertexShader(-1);
			SetUsePixelShader(-1);
		}
		else
		{
			MV1SetUseOrigShader(true);
			SetUseVertexShader(m_vsHs[m_vertexShaderNumbers[i]]);
			SetUsePixelShader(m_psHs[m_pixelShaderNumbers[i]]);
		}
		MV1DrawTriangleList(m_modelHandle, i);
	}
}

void Player::End()
{
	/*処理無し*/
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
	if (m_currentState == State::Jump)
	{
		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
		if (m_isMove)
		{
			// 移動している場合は歩き状態になる
			m_currentState = State::Walk;
			ChangeAnim(static_cast<int>(AnimKind::Walk));
		}
		else
		{
			// 移動していない場合は立ち止まり状態になる
			m_currentState = State::Idle;
			ChangeAnim(static_cast<int>(AnimKind::Idle));
		}
		// 着地時はアニメーションのブレンドを行わない
		m_animBlendRate = 1.0f;
	}
}

void Player::OnFall()
{
	// 現在の状態がジャンプ中じゃなかったとき
	if (m_currentState != State::Jump)
	{
		// ジャンプ中にする
		m_currentState = State::Jump;

		// 少しだけジャンプする
		m_nowJunpPower = kFallUpPower;

		// アニメーションを落下中のものにする
		ChangeAnim(static_cast<int>(AnimKind::Fall));
	}
}

void Player::DisableRootFrameZMove()
{
	// ルートフレームの行列を入れる変数
	MATRIX localMatrix;

	// ユーザー行列を解除(リセット)する
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
	// 次の状態
	State nextState = m_currentState;

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
	m_isDash = input.IsPressing("B");

	// 左ボタンが入力されたらカメラの見ている方向から見て左に移動する
	if (input.IsPressing("left"))
	{
		// 移動ベクトルに左が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, leftMoveVec);
		// 移動フラグをtrueにする
		isMove = true;
	}
	// 右ボタンが入力されたらカメラの見ている方向から見て右に移動する
	else if (input.IsPressing("right"))
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


	if (isMove)// 移動ボタンが押されていた場合
	{
		// 移動ベクトルを正規化したものをプレイヤーが向く方向として保存する
		m_targetDir = VNorm(moveVec);

		if (m_currentState == State::Idle || m_currentState == State::Walk || m_currentState == State::Run)
		{
			moveVec = VScale(m_targetDir, m_isDash ? kDashSpeed : kMoveSpeed);
			nextState = m_isDash ? State::Run : State::Walk;
			if (m_isLackStamina)
			{
				moveVec = VScale(m_targetDir, kLackStaminaSpeed);
				nextState = State::Walk;
			}
		}
	}
	else
	{
		// このフレームで走っているか歩いている状態だった場合
		if (m_currentState == State::Walk || m_currentState == State::Run)
		{
			// 立ち止まる状態にする
			nextState = State::Idle;
		}
	}


	// ジャンプしていない状態でAボタンが押されていた場合はジャンプをする
	// スタミナ不足状態だった場合はジャンプはできない
	if (m_currentState != State::Jump && (input.IsTriggered("A")) && !m_isLackStamina)
	{
		// スタミナを減らす
		m_stamina -= kDecreaseJumpStamina;

		// Y軸方向の速度をセットする
		m_nowJunpPower = kJunpPower;

		// 状態をジャンプにする
		nextState = State::Jump;
	}

	// ジャンプしている状態だった場合は重力を適用する
	if (m_currentState == State::Jump)
	{
		m_nowJunpPower -= kGravity;

		if (isMove)
		{
			moveVec = VScale(m_targetDir, m_isDash ? kDashSpeed : kMoveSpeed);
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

	// 現在位置にステージとの当たり判定を行った結果を反映する
	m_pos = stage.CheckCollision(*this, moveVec);

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}

void Player::Stamina()
{
	// ダッシュ中はスタミナが減る
	if (m_currentState == State::Run && m_stamina > 0.0f)
	{
		m_stamina -= kDecreaseStaminaSpeed;
	}
	// ダッシュ中出なかった場合はスタミナは増える
	else
	{
		m_stamina += kIncreaseStaminaSpeed;
	}

	// スタミナが0になったらしばらくスタミナ不足状態になる
	if (m_stamina <= 0.0f)
	{
		m_isLackStamina = true;
	}

	// スタミナはmax値以上にならないようにする
	if (m_stamina >= kMaxStamina)
	{
		m_stamina = kMaxStamina;

		// スタミナ不足状態だった場合はここで不足状態から復帰する
		m_isLackStamina = false;
	}
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
	// 立ち止まり状態から歩き状態に変わった
	if (prevState == State::Idle && m_currentState == State::Walk)
	{
		// 走るアニメーションの再生
		ChangeAnim(static_cast<int>(AnimKind::Walk));
	}
	// 立ち止まり状態から走り状態になった
	else if (prevState == State::Idle && m_currentState == State::Run)
	{
		ChangeAnim(static_cast<int>(AnimKind::Run));
	}
	// 立ち止まり状態からジャンプ状態になった
	else if (prevState == State::Idle && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// 歩き状態から立ち止まり状態に変わった
	else if (prevState == State::Walk && m_currentState == State::Idle)
	{
		// 立ち止まるアニメーションの再生
		ChangeAnim(static_cast<int>(AnimKind::Idle));
	}
	// 歩き状態から走り状態になった
	else if (prevState == State::Walk && m_currentState == State::Run)
	{
		ChangeAnim(static_cast<int>(AnimKind::Run));
	}
	// 歩き状態からジャンプ状態になった
	else if (prevState == State::Walk && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// 走り状態から歩き状態になった
	else if (prevState == State::Run && m_currentState == State::Walk)
	{
		ChangeAnim(static_cast<int>(AnimKind::Walk));
	}
	// 走り状態から立ち止まり状態になった
	else if (prevState == State::Run && m_currentState == State::Idle)
	{
		ChangeAnim(static_cast<int>(AnimKind::Idle));
	}	
	// 走り状態からジャンプ状態になった
	else if (prevState == State::Run && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// ジャンプ状態だった場合
	else if (m_currentState == State::Jump)
	{
		// 落下している
		if (m_nowJunpPower < kFall)
		{
			// アニメーションが上昇中用の物である
			bool isJumpAnim = MV1GetAttachAnim(m_modelHandle, m_currentAnimNo)
				== static_cast<int>(AnimKind::Jump);
			if (isJumpAnim)
			{
				// 落下中用アニメーションを再生する
				ChangeAnim(static_cast<int>(AnimKind::Fall));
			}
		}
	}
}

bool Player::LoopAnim(int attachNo)
{
	// アニメーションが設定されていないため、終了する
	if (attachNo == -1)return false;

	// アニメーションがループしているかどうか
	bool isLoop = false;

	/*アニメーションを進行させる*/
	// 現在の再生カウント
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);
	// アニメーションを進める
	now += kPlayAnimSpeed;

	// 現在再生中のアニメーションの総カウント
	float total = MV1GetAttachAnimTotalTime(m_modelHandle, attachNo);


	// アニメーションをループさせる
	while (now >= total)
	{
		now -= total;

		isLoop = true;
	}

	// アニメーションを進めた時間に設定する
	MV1SetAttachAnimTime(m_modelHandle, attachNo, now);

	return isLoop;
}

void Player::ChangeAnim(int animIndex)
{
	// 前にアニメーションがアタッチされていた場合はこの時点で削除しておく
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevAnimNo);
	}

	// 現在再生中のアニメーションは変更前のアニメーションにする
	m_prevAnimNo = m_currentAnimNo;

	// 変更後のアニメーションを設定する
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, animIndex, -1, false);

	// 切り替えの瞬間は変更前のアニメーションが再生される状態にする
	m_animBlendRate = 0.0f;

	// 変更前のアニメーション100%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	// 変更後のアニメーション0%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);
}
