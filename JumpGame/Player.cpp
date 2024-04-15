#include "Player.h"
#include "Input.h"

Player::Player() :
	m_pos{ -10,kGroundPosY,0 },
	m_move{ 0,0,0 },
	m_velocity{ 0,0,0 },
	m_dir{ 0,0,1 },
	m_modelHandle(-1),
	m_rad(kRadius),
	m_jumpPower(0.0f),
	m_isJump(false),
	m_jumpSe(-1)
{
	/*3D���f���̃��[�h*/
	m_modelHandle = MV1LoadModel("Data/Model/chicken.mv1");
	/*SE�̃��[�h*/
	m_jumpSe = LoadSoundMem("Data/Sound/SE/Jump.mp3");
}

Player::~Player()
{
	/*���f���̃f���[�g*/
	MV1DeleteModel(m_modelHandle);
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_jumpSe);
}

void Player::Update(Input& input)
{
	// ���f���̃X�P�[�������肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));

	// �E�ړ�
	m_pos = VAdd(m_pos, VGet(0.05f, 0, 0));

	// �d�͂ƒn�ʂ̏���
	GravityAndGround();

	// �W�����v����
	Jump(input);

	// �ʒu�̍X�V
	m_pos = VAdd(m_pos, m_move);

	// ���f���̈ʒu�ݒ�
	MV1SetPosition(m_modelHandle, m_pos);
}

void Player::Draw() const
{
	// 3D���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(m_modelHandle);
	pos.x -= 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0x0000ff, 0x0000ff, false);
#endif // _DEBUG
}

const VECTOR& Player::GetPos() const
{
	return MV1GetPosition(m_modelHandle);
}

void Player::Jump(Input& input)
{
	// �W�����v����
	if (input.IsTriggered("A") && !m_isJump)
	{
		PlaySoundMem(m_jumpSe, DX_PLAYTYPE_BACK);
		m_jumpPower = kJumpHeight;
		m_isJump = true;
	}
}

void Player::GravityAndGround()
{
	// �d��
	m_pos = VAdd(m_pos, VGet(0.0f, m_jumpPower, 0.0f));
	m_jumpPower -= kGravity;

	// �n��
	if (m_pos.y <= kGroundPosY)
	{
		m_pos.y = kGroundPosY;
		m_jumpPower = 0;
		m_isJump = false;
	}
}
