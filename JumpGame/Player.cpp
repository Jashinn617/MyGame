#include "Player.h"
#include "Handle/ModelManager.h"


Player::Player() :
	m_pos{ 0,0,0 },
	m_modelHandle(-1)
{
	m_pModel = make_unique<ModelManager>();
	// モデルの読み込み
	m_modelHandle = MV1DuplicateModel(m_pModel->GetPlayerHandle());
}

Player::~Player()
{
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 上を押していたら上に進む
	if (key & PAD_INPUT_UP)
	{
		m_pos.z += 10;
	}

	// 下を押していたら下に進む
	if (key & PAD_INPUT_DOWN)
	{
		m_pos.z -= 10;
	}

	// 右を押していたら右に進む
	if (key & PAD_INPUT_RIGHT)
	{
		m_pos.x += 10;
	}

	// 左を押していたら左に進む
	if (key & PAD_INPUT_LEFT)
	{
		m_pos.x -= 10;
	}

	MV1SetPosition(m_modelHandle, m_pos);

}

void Player::Draw() const
{
	MV1DrawModel(m_modelHandle);
}
