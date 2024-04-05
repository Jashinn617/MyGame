#include "Player.h"

namespace
{
	// プレイヤーの速度
	constexpr float kSpeed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
	// プレイヤーのスケール
	constexpr float kScale = 0.002f;

	// 当たり判定用の円の半径
	constexpr float kRadius = 0.5f;
}

Player::Player() :
	m_pos{ 0,0,0 },
	m_velocity{0,0,0},
	m_dir{0,0,1},
	m_modelHandle(-1),
	m_rad(kRadius)
{
	// 3Dモデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/chicken.mv1");
}

Player::~Player()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{

	// 仮の動き
#ifdef _DEBUG

	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 単純に方向転換
	m_dir = VGet(0, 0, 0);
	if (Key & PAD_INPUT_UP)
	{
		m_dir = VAdd(m_dir, VGet(0, 1, 0));
	}
	else if (Key & PAD_INPUT_DOWN)
	{
		m_dir = VAdd(m_dir, VGet(0, -1, 0));
	}
	if (Key & PAD_INPUT_RIGHT)
	{
		m_dir = VAdd(m_dir, VGet(1, 0, 0));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		m_dir = VAdd(m_dir, VGet(-1, 0, 0));
	}

#endif

	m_dir = VAdd(m_dir, VGet(1, 0, 0));

	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}

	// 位置の更新
	m_velocity = VScale(m_dir, kSpeed);
	m_pos = VAdd(m_pos, m_velocity);

	// 力をかけ終わったvelocityの方向にdirを調整する
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}

	// モデルのスケールを決定する
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// モデルの位置設定
	MV1SetPosition(m_modelHandle, m_pos);

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 91.0f, 0.0f));	
}

void Player::Draw() const
{
	// 3Dモデルの描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(m_modelHandle);

	DrawSphere3D(pos, kRadius, 32, 0x0000ff, 0x0000ff, false);

#endif // _DEBUG

}

const VECTOR& Player::GetPos() const
{
	return MV1GetPosition(m_modelHandle);
	// TODO: return ステートメントをここに挿入します
}
