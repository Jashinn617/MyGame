#include "DxLib.h"
#include "Player.h"
#include "Util/Game.h"
#include "Util/Input.h"
#include "Util/HandleManager.h"


Player::Player():
	m_pos{0,0,-kWallZ},
	m_dir(0),
	m_jumpPower(0.0f),
	m_isJump(false),
	m_cameraAngle(0.0f)
{
	/*��������*/
}

Player::~Player()
{
}

void Player::Init(HandleManager& handle)
{
	// ���f���������ʒu�ɖ߂�
	MV1SetPosition(handle.GetModel("player"), m_pos);
}

void Player::Update(Input& input, HandleManager& handle)
{
	// ���f���̃X�P�[����ݒ肷��
	MV1SetScale(handle.GetModel("player"), VGet(kScale,kScale,kScale));
	// ��]
	MV1SetRotationXYZ(handle.GetModel("player"), VGet(0.0f, m_dir, 0.0f));

	// �ړ�
	Move(input);

	// �d�͂ƒn�ʂ̏���
	GravityAndGround();
	
	// �W�����v����
	Jump(input,handle);

	// �ǂ̏���
	Wall();

	// ���f���̈ʒu�ݒ�
	MV1SetPosition(handle.GetModel("player"), m_pos);
}

void Player::Draw(HandleManager& handle) const
{
	// ���f���̕`��
	MV1DrawModel(handle.GetModel("player"));

	// �����蔻��̕\��
#ifdef _DEBUG
	VECTOR pos = MV1GetPosition(handle.GetModel("player"));
	pos.y += 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0x0000ff, 0x0000ff, false);
	// �v���C���[�̈ʒu
	DrawFormatString(0, 0, 0xffffff, "(%.2f,%.2f,%.2f)\n", m_pos.x, m_pos.y, m_pos.z);		
#endif // _DEBUG
}

void Player::Move(Input& input)
{
	// �A�i���O�X�e�B�b�N���g���Ă̈ړ�
	int analogX = 0;
	int analogY = 0;
	// �R���g���[���[�̃A�i���O�X�e�B�b�N�̓��͒l���擾����
	GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

	// �A�i���O�X�e�B�b�N�̓��͂�10�`80%�͈̔͂��g�p����
	VECTOR move = VGet(analogX, 0.0f, -analogY);
	// �x�N�g���̒������擾����
	float len = VSize(move);

	/* �x�N�g���̒�����0.0�`1.0�̊����ɕϊ�����*/
	float rate = len / kAnalogInputMax;
	// �A�i���O�X�e�B�b�N�������ɂȂ�͈͂����O����
	rate = (rate - kAnalogRangeMim) / (kAnalogInputMax - kAnalogRangeMim);
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	// ���x�����肵�A�ړ��x�N�g���ɔ��f����
	move = VNorm(move);
	float speed = kMaxSpeed * rate;
	move = VScale(move, speed);

	// �J�����̂���ꏊ(�p�x)����R���g���[���[�ɂ��ړ����������肷��
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
	move = VTransform(move, mtx);

	// �ړ���������v���C���[�̌������������肷��
	// �ړ����Ă��Ȃ��ꍇ(0�x�N�g���̏ꍇ)�͕ύX���Ȃ�
	if (VSquareSize(move) > 0.0f)
	{
		m_dir = -atan2f(move.z, move.x) - DX_PI_F;
	}

	// �ʒu�̍X�V
	m_pos = VAdd(m_pos, move);
}

void Player::Jump(Input& input, HandleManager& handle)
{
	// �W�����v����
	if (input.IsTriggered("A") && !m_isJump)
	{
		PlaySoundMem(handle.GetSound("jumpSE"), DX_PLAYTYPE_BACK);
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