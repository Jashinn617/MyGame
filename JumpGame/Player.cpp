#include "Player.h"

namespace
{
	// �v���C���[�̑��x
	constexpr float kSpeed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
	// �v���C���[�̃X�P�[��
	constexpr float kScale = 0.002f;

	// �����蔻��p�̉~�̔��a
	constexpr float kRadius = 0.5f;
}

Player::Player() :
	m_pos{ 0,0,0 },
	m_velocity{0,0,0},
	m_dir{0,0,1},
	m_modelHandle(-1),
	m_rad(kRadius)
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

	// ���̓���
#ifdef _DEBUG

	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �P���ɕ����]��
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

	// �[�����Z����
	if (VSquareSize(m_dir) > 0)
	{
		// ���K��
		m_dir = VNorm(m_dir);
	}

	// �ʒu�̍X�V
	m_velocity = VScale(m_dir, kSpeed);
	m_pos = VAdd(m_pos, m_velocity);

	// �͂������I�����velocity�̕�����dir�𒲐�����
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}

	// ���f���̃X�P�[�������肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// ���f���̈ʒu�ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 91.0f, 0.0f));	
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
