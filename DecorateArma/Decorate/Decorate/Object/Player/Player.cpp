#include "Player.h"
#include "PlayerState.h"

#include "../Model.h"
#include "../Camera.h"

#include "../../Shader/VertexShader.h"

#include "../../Utility/Sphere.h"


namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Player.mv1";	// プレイヤーモデルファイルパス

	constexpr float kMoveSpeedDashRate = 1.2f;	// ダッシュ時速度
	constexpr float kAccelerationRate = 0.5f;	// 加速度
	constexpr float kJumpMaxSpeed = 8.0f;		// ジャンプ時の最大速度
	constexpr float kGravity = 0.8f;			// 重力
	constexpr float kFallMaxSpeed = -15.0f;		// 最大落下速度
	constexpr float kNowVecNum = 0.8f;			// 現在の方向
	constexpr float kNextVecNum = 0.2f;			// 進みたい方向
	constexpr float kMinJumpRiseNum = 1.0f;		// 上昇中と判断される最低値
	constexpr float kAngleSpeed = 0.02f;		// 回転速度

	constexpr float kHeight = 35.0f;			// 高さ
	constexpr float kSize = 15.0f;				// サイズ
	constexpr VECTOR kScale = { 0.11f,0.11f,0.11f };				// スケール

	/// <summary>
	/// アニメーション速度
	/// </summary>
	enum kAnimSpeed
	{
		Idle=2,
		Walk=2,
		Dash=1,
		Jump=1,
		Damage=1,
	};

}

Player::Player():
	m_pState(std::make_shared<PlayerState>()),
	m_pCamera(std::make_shared<Camera>())
{
	/*移動速度初期化*/
	m_moveData.walkSpeed = m_statusData.spd;
	m_moveData.dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_moveData.acceleration = m_statusData.spd * kAccelerationRate;
	m_moveData.rotSpeed = kAngleSpeed;

	/*情報初期化*/
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;

	// 当たり判定ポインタ作成
	m_pSphere = std::make_shared<Sphere>(m_characterInfo.pos, m_objSize, kHeight * 0.5f);

	// モデルポインタ作成
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	// モデルスケール設定
	m_pModel->SetScale(kScale);
	// アニメーション初期化
	m_pModel->SetAnim(m_animData.idle, false, true);

	// 初期ステイトの設定(待機状態から)
	m_pState->SetState(PlayerState::StateKind::Idle);

	// モデルの頂点タイプの取得
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// 頂点タイプの取得
		//m_vertexShaderType.push_back(MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i));

		// 頂点シェーダハンドルの取得
		m_vertexShaderH.push_back(m_pVertexShader->
			SetVertexShaderH(MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i)));
	}
}

Player::~Player()
{
	/*処理無し*/
}

void Player::Update()
{
	// ステイト更新
	m_pState->Update();
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

	
}

void Player::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// モデルをフレームごとに描画する
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// シェーダの設定

		// 描画
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// シェーダを使わない設定にする

	// 当たり判定の球の描画
	m_pSphere->DebugDraw(0xff0000);
}

void Player::Draw2D()
{
	// カメラ2D部分の描画
	m_pCamera->Draw();

#ifdef _DEBUG
	// デバッグ用描画
	DrawFormatString(0, 20, 0x000000, "プレイヤー座標：%f,%f,%f"
		, m_characterInfo.pos.x, m_characterInfo.pos.y, m_characterInfo.pos.z);
	DrawFormatString(0, 100, 0x000000, "ジャンプ力：%f", m_jumpPower);
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
	// if() return;

	// ステイトの終了処理
	m_pState->EndState();
}

void Player::UpdateAngle()
{
	// ダメージ中は処理をしない

}

void Player::UpdateMoveDirection()
{
}

VECTOR Player::Move()
{
	return VECTOR();
}

void Player::InitState()
{
}

void Player::UpdateState()
{
}
