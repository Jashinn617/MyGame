#include "Player.h"
#include "PlayerState.h"
#include "Shot.h"

#include "../Model.h"
#include "../Camera.h"

#include "../../Shader/SetVertexShader.h"
#include "../../Shader/ToonShader.h"

#include "../../Utility/Sphere.h"
#include "../../Utility/Capsule.h"
#include "../../Utility/MoveDirectionVec.h"

#include "../../Common/CsvLoad.h"


namespace
{
	const char* const kFileName = "Data/Model/Player/Player.mv1";	// プレイヤーモデルファイルパス

	constexpr float kMoveSpeedDashRate = 1.2f;	// ダッシュ時速度
	constexpr float kAccelerationRate = 0.5f;	// 加速度
	constexpr float kJumpMaxSpeed = 8.0f;		// ジャンプ時の最大速度
	constexpr float kGravity = 0.8f;			// 重力
	constexpr float kFallMaxSpeed = -15.0f;		// 最大落下速度
	constexpr float kNowVecNum = 0.8f;			// 現在の方向
	constexpr float kNextVecNum = 0.2f;			// 進みたい方向
	constexpr float kMinJumpRiseNum = 1.0f;		// 上昇中と判断される最低値
	constexpr float kAngleSpeed = 0.02f;		// 回転速度

	constexpr float kHeight = 63.0f;					// 高さ
	constexpr float kSize = 15.0f;						// サイズ
	constexpr float kTopPos = 60.0f;					// 頭の高さ
	constexpr float kBottomPos = 0.0f;					// 足元の座標
	constexpr float kCapsuleRadius = 8.0f;				// カプセルの半径
	constexpr VECTOR kScaleVec = { 0.8f,1.2f,0.8f };	// スケール

	/// <summary>
	/// アニメーション速度
	/// </summary>
	enum kAnimSpeed
	{
		Idle = 2,
		Walk = 2,
		Dash = 1,
		Jump = 1,
		Damage = 1,
	};
}

Player::Player():
	m_pState(std::make_shared<PlayerState>(this)),
	m_pCamera(std::make_shared<Camera>()),
	m_pShot(std::make_shared<Shot>())
{
	// アニメーションロード
	CsvLoad::GetInstance().AnimLoad(m_animData, "Player");

	/*移動速度初期化*/
	/*m_moveData.walkSpeed = m_statusData.spd;
	m_moveData.dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_moveData.acc = m_statusData.spd * kAccelerationRate;
	m_moveData.rotSpeed = kAngleSpeed;*/

	m_moveData.walkSpeed = 5;
	m_moveData.dashSpeed = 10 * kMoveSpeedDashRate;
	m_moveData.acc = 5 * kAccelerationRate;
	m_moveData.rotSpeed = kAngleSpeed;

	/*情報初期化*/
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.topPos = VAdd(m_characterInfo.pos, VGet(0.0f, kTopPos, 0.0f));
	m_characterInfo.bottomPos = VSub(m_characterInfo.pos, VGet(0.0f, kBottomPos, 0.0f));
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;

	// 当たり判定ポインタ作成
	m_pSphere = std::make_shared<Sphere>(m_characterInfo.pos, m_objSize, kHeight * 0.5f);
	m_pCapsule = std::make_shared<Capsule>(m_characterInfo.topPos, m_characterInfo.bottomPos, kCapsuleRadius);

	// モデルポインタ作成
	m_pModel = std::make_shared<Model>(kFileName);
	// モデルスケール設定
	m_pModel->SetScale(kScaleVec);
	// アニメーション初期化
	m_pModel->SetAnim(m_animData.idle, true, false);

	// 初期ステイトの設定(待機状態から)
	m_pState->SetState(PlayerState::StateKind::Idle);

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

	// ダメージ処理

	// アニメーション更新
	m_pModel->Update();
	// モデル座標の設定
	m_pModel->SetPos(m_characterInfo.pos);
	// モデル回転の設定
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));

	// カメラ更新
	m_pCamera->Update(m_characterInfo.pos);	

	// 遠距離攻撃武器更新
	m_pShot->Update(m_characterInfo.pos, m_angle);

	// 座標設定
	m_characterInfo.topPos = VAdd(m_characterInfo.pos, VGet(0.0f, kTopPos, 0.0f));
	m_characterInfo.bottomPos = VSub(m_characterInfo.pos, VGet(0.0f, kBottomPos, 0.0f));
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
	m_pCapsule->DebugDraw(0xff0000);
}

void Player::Draw2D()
{
	// カメラ2D部分の描画
	m_pCamera->Draw();

#ifdef _DEBUG
	// デバッグ用描画
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標：%f,%f,%f"
		, m_characterInfo.pos.x, m_characterInfo.pos.y, m_characterInfo.pos.z);
	DrawFormatString(0, 40, 0xffffff, "ジャンプ力：%f", m_jumpPower);
#endif // _DEBUG
}

void Player::OnDamage(VECTOR targetPos)
{
}

void Player::OnAttack()
{
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

	// 目標角度の計算(ベクトル(z,x)の角度 + 90°+ カメラ角度)
	float nextAngle = atan2(m_moveDirection.z, m_moveDirection.x)
		+ DX_PI_F * 0.5f + m_pCamera->GetCameraAngleX();

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

void Player::UpdateState()
{
	/*現在のステイトによって更新処理を変える*/
	switch (m_pState->GetState())
	{
	case PlayerState::StateKind::Idle:	// 待機
		// 段々減速する
		m_moveSpeed = max(m_moveSpeed - m_moveData.acc, 0.0f);
		// アニメーションを待機状態に変更する
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		break;

	case PlayerState::StateKind::Walk:	// 歩き
		// 移動速度を歩き状態の速度に変更する
		m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.walkSpeed);
		// アニメーションを歩きアニメーションに変更する
		m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
		break;

	case PlayerState::StateKind::Dash:	// ダッシュ
		// 移動速度をダッシュ時の速度にする
		m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.dashSpeed);
		// アニメーションをダッシュアニメーションに変更する
		m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);
		break;

	case PlayerState::StateKind::Jump:	// ジャンプ
		// 移動速度を変更する
		//m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.walkSpeed);

		// 上昇中
		//if (m_jumpPower > kMinJumpRiseNum)
		//{
		//	// アニメーションをジャンプ開始アニメーションに切り替える
		//	m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
		//}
		//// 空中にとどまっている、下降中
		//else
		//{
			// アニメーションをジャンプ待機アニメーションに切り替える
			m_pModel->ChangeAnim(m_animData.jumpIdle, true, false, kAnimSpeed::Jump);
		//}
		break;

	case PlayerState::StateKind::Damage:	// ダメージ

		break;

	default:
		// 上記以外だった場合は何もしない
		break;
	}
}