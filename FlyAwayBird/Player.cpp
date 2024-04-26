#include "DxLib.h"
#include "Player.h"
#include "Util/Game.h"
#include"Util/Input.h"


Player::Player():
	m_pos{0,0,-10},
	m_move{0,0,0},
	m_dirY(90),
	m_modelHandle(-1),
	m_jumpPower(0.0f),
	m_isJump(false)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/Player/chicken.mv1");
}

Player::~Player()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	/*処理無し*/
}

void Player::Update(Input& input)
{
	// 移動値の初期化
	m_move = VGet(0, 0, 0);

	// モデルのスケールを設定する
	MV1SetScale(m_modelHandle, VGet(kScale,kScale,kScale));
	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_dirY * Game::kRadianConversion, 0.0f));

	// 移動
	Move(input);

	// 重力と地面の処理
	GravityAndGround();
	
	// ジャンプ処理
	Jump(input);

	// 位置の更新
	m_pos = VAdd(m_pos, m_move);

	// モデルの位置設定
	MV1SetPosition(m_modelHandle, m_pos);
}

void Player::Draw() const
{
	// 3Dモデルの描画
	MV1DrawModel(m_modelHandle);

	// 当たり判定の表示
#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(m_modelHandle);
	pos.y += 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0x0000ff, 0x0000ff, false);
#endif // _DEBUG
}

void Player::Move(Input& input)
{
	// 移動
	if (input.IsPressing("up"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, kSpeed));
	}
	if (input.IsPressing("down"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, -kSpeed));
	}
	if (input.IsPressing("right"))
	{
		m_move = VAdd(m_move, VGet(kSpeed, 0.0f, 0.0f));
	}
	if (input.IsPressing("left"))
	{
		m_move = VAdd(m_move, VGet(-kSpeed, 0.0f, 0.0f));
	}
}

void Player::Jump(Input& input)
{
	// ジャンプ処理
	if (input.IsTriggered("A") && !m_isJump)
	{
		m_jumpPower = kJumpPower;
		m_isJump = true;
	}
}

void Player::GravityAndGround()
{
	// 重力
	m_pos = VAdd(m_pos, VGet(0.0f, m_jumpPower, 0.0f));
	m_jumpPower -= kGravity;

	// 地面
	if (m_pos.y <= kGroundPosY)
	{
		m_pos.y = kGroundPosY;
		m_jumpPower = 0;
		m_isJump = false;
	}
}
