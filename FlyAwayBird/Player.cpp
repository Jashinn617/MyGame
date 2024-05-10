#include "DxLib.h"
#include "Player.h"
#include "Util/Game.h"
#include "Util/Input.h"
#include "Util/HandleManager.h"

#include <cassert>


Player::Player():
	m_pos{0,0,-kWallZ},
	m_move{0,0,0},
	m_dirY(90),
	m_jumpSeHandle(-1),
	m_jumpPower(0.0f),
	m_isJump(false)
{
	/*SE�̃��[�h*/
	m_jumpSeHandle = LoadSoundMem("Data/Sound/SE/JumpSE.mp3");
	assert(m_jumpSeHandle != -1);

}

Player::~Player()
{
	/*��������*/
}

void Player::Init()
{
	/*��������*/
}

void Player::Update(Input& input, HandleManager& handle)
{
	// �ړ��l�̏�����
	m_move = VGet(0, 0, 0);

	// ���f���̃X�P�[����ݒ肷��
	MV1SetScale(handle.GetModel("player"), VGet(kScale,kScale,kScale));
	// ��]
	MV1SetRotationXYZ(handle.GetModel("player"), VGet(0.0f, m_dirY * Game::kRadianConversion, 0.0f));

	// �ړ�
	Move(input);

	// �d�͂ƒn�ʂ̏���
	GravityAndGround();
	
	// �W�����v����
	Jump(input);

	// �ǂ̏���
	Wall();

	// �ʒu�̍X�V
	m_pos = VAdd(m_pos, m_move);

	// ���f���̈ʒu�ݒ�
	MV1SetPosition(handle.GetModel("player"), m_pos);
}

void Player::Draw(HandleManager& handle) const
{
	// 3D���f���̕`��
	MV1DrawModel(handle.GetModel("player"));

	// �����蔻��̕\��
#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(handle.GetModel("player"));
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

void Player::Wall()
{
	// ���
	if (m_pos.z <= -kWallZ)
	{
		m_pos.z = -kWallZ;
	}
	// �O
	if (m_pos.z >= kWallZ)
	{
		m_pos.z = kWallZ;
	}
	// �E
	if (m_pos.x >= kWallX)
	{
		m_pos.x = kWallX;
	}
	// ��
	if (m_pos.x <= -kWallX)
	{
		m_pos.x = -kWallX;
	}
}
