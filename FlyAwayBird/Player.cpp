#include "Player.h"
#include "Util/Game.h"
#include"Util/Input.h"


Player::Player():
	m_pos{0,0,0},
	m_move{0,0,0},
	m_dir(0),
	m_modelHandle(-1)
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
	// モデルのスケールを設定する
	MV1SetScale(m_modelHandle, VGet(kScale,kScale,kScale));
	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));

	// 移動


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
