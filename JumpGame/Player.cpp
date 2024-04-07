#include "Player.h"

namespace
{
	// �v���C���[�̑��x
	constexpr float kSpeed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
	// �v���C���[�̃X�P�[��
	constexpr float kScale = 0.002f;

	// �����蔻��p�̉~�̔��a
	constexpr float kRadius = 0.3f;
}

Player::Player() :
	m_pos{ -10,0,0 },
	m_move{ 0,0,0 },
	m_velocity{ 0,0,0 },
	m_dir{ 0,0,1 },
	m_modelHandle(-1),
	m_rad(kRadius),
	m_jumpPower(0.0f),
	m_isJump(false)
{
	// 3D���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/chicken.mv1");
}

Player::~Player()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{
	// ���f���̃X�P�[�������肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));

	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �E�ړ�
	m_pos = VAdd(m_pos, VGet(0.05f, 0, 0));

	// �d��
	m_pos = VAdd(m_pos, VGet(0.0f, m_jumpPower, 0.0f));

	m_jumpPower -= kGravity;

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_jumpPower = 0;
		m_isJump = false;
	}

	if (Key & PAD_INPUT_A && !m_isJump)
	{
		m_jumpPower = kJumpHeight;
		m_isJump = true;
	}

	//// �[�����Z����
	//if (VSquareSize(m_dir) > 0)
	//{
	//	// ���K��
	//	m_dir = VNorm(m_dir);
	//}

	// �ʒu�̍X�V
	//m_velocity = VScale(m_dir, kSpeed);
	m_pos = VAdd(m_pos, m_move);

	//// �͂������I�����velocity�̕�����dir�𒲐�����
	//if (VSize(m_velocity) != 0)
	//{
	//	m_dir = VNorm(m_velocity);
	//}


	// ���f���̈ʒu�ݒ�
	MV1SetPosition(m_modelHandle, m_pos);
}

void Player::Draw() const
{
	// 3D���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(m_modelHandle);

	DrawSphere3D(pos, kRadius, 32, 0x0000ff, 0x0000ff, false);

#endif // _DEBUG

}

const VECTOR& Player::GetPos() const
{
	return MV1GetPosition(m_modelHandle);
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}
