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
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/Player/chicken.mv1");
}

Player::~Player()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	/*��������*/
}

void Player::Update(Input& input)
{
	// �ړ��l�̏�����
	m_move = VGet(0, 0, 0);

	// ���f���̃X�P�[����ݒ肷��
	MV1SetScale(m_modelHandle, VGet(kScale,kScale,kScale));
	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_dirY * Game::kRadianConversion, 0.0f));

	// �ړ�
	Move(input);

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

	// �����蔻��̕\��
#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(m_modelHandle);
	pos.y += 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0x0000ff, 0x0000ff, false);
#endif // _DEBUG
}

void Player::Move(Input& input)
{
	// �ړ�
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
	// �W�����v����
	if (input.IsTriggered("A") && !m_isJump)
	{
		m_jumpPower = kJumpPower;
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
