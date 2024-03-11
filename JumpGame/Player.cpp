#include "Player.h"
#include "Handle/ModelManager.h"


Player::Player() :
	m_pos{ 0,0,0 },
	m_modelHandle(-1)
{
	m_pModel = make_unique<ModelManager>();
	// ���f���̓ǂݍ���
	m_modelHandle = MV1DuplicateModel(m_pModel->GetPlayerHandle());
}

Player::~Player()
{
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ��������Ă������ɐi��
	if (key & PAD_INPUT_UP)
	{
		m_pos.z += 10;
	}

	// ���������Ă����牺�ɐi��
	if (key & PAD_INPUT_DOWN)
	{
		m_pos.z -= 10;
	}

	// �E�������Ă�����E�ɐi��
	if (key & PAD_INPUT_RIGHT)
	{
		m_pos.x += 10;
	}

	// ���������Ă����獶�ɐi��
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
