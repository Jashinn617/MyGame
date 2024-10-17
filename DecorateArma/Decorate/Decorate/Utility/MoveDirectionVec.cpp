#include "MoveDirectionVec.h"

#include "Pad.h"
#include "CharacterData.h"

namespace
{
	constexpr float kUp = -1.0f;		// ������ړ��x�N�g��
	constexpr float kDown = 1.0f;		// �������ړ��x�N�g��
	constexpr float kRight = 1.0f;		// �E�����ړ��x�N�g��
	constexpr float kLeft = -1.0f;		// �������ړ��x�N�g��
}

MoveDirectionVec::MoveDirectionVec() :
	m_direction{ 0.0f,0.0f,0.0f }
{
	/*��������*/
}

MoveDirectionVec::~MoveDirectionVec()
{
	/*��������*/
}

void MoveDirectionVec::Update()
{
	// �p�b�h�A�i���O���擾
	DINPUT_JOYSTATE input;

	input.X = 0;
	input.Y = 0;

	// �ړ�����
	float moveAngle = 0.0f;

	// ���͏�Ԃ̎擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	// �ړ��x�N�g���̏�����
	m_direction = VGet(0.0f, 0.0f, 0.0f);

	// �X�e�B�b�N�ł̃A�i���O���͏�Ԃ��������Ă���Ƃ��͂�������D�悷��
	if (input.X != 0 || input.Y != 0)
	{
		m_direction.x = 0.001f * input.X;
		m_direction.z = 0.001f * input.Y;
	}
	else
	{
		// ���{�^���������ꂽ��v���C���[�̌���������
		if (Pad::IsPress(PAD_INPUT_LEFT))
		{
			m_direction.x = kLeft;
		}
		// �E�{�^���������ꂽ��v���C���[�̌����E��
		else if (Pad::IsPress(PAD_INPUT_RIGHT))
		{
			m_direction.x = kRight;
		}
		else
		{
			m_direction.x = 0.0f;
		}

		// ��{�^���������ꂽ��v���C���[�̌��������
		if (Pad::IsPress(PAD_INPUT_UP))
		{
			m_direction.z = kUp;
		}
		// ���{�^���������ꂽ��v���C���[�̌�������
		else if (Pad::IsPress(PAD_INPUT_DOWN))
		{
			m_direction.z = kDown;
		}
		else
		{
			m_direction.z = 0.0f;
		}
	}

	// �ړ������x�N�g���̐��K��
	if (VSize(m_direction) >= 1.0f)
	{
		m_direction = VNorm(m_direction);
	}
}
