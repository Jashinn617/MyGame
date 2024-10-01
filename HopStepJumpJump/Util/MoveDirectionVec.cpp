#include "MoveDirectionVec.h"
#include "../Util/Pad.h"
#include "CharacterData.h"

namespace
{
	constexpr float kUp = -1.0f;	// ��ړ������x�N�g��
	constexpr float kDown = 1.0f;	// ���ړ������x�N�g��
	constexpr float kRight = 1.0f;	// �E�ړ������x�N�g��
	constexpr float kLeft = -1.0f;	// ���ړ������x�N�g��
	constexpr float kZero = 0.0f;	// �ړ������x�N�g���Ȃ�
}

MoveDirectionVec::MoveDirectionVec():
	m_directionVec{0.0f,0.0f,0.0f}
{
	/*��������*/
}

MoveDirectionVec::~MoveDirectionVec()
{
	/*��������*/
}

void MoveDirectionVec::Update()
{
	//�p�b�h�A�i���O���擾
	DINPUT_JOYSTATE input;

	input.X = 0;
	input.Y = 0;

	//�ړ��p�x
	float moveAngle = 0.0f;

	// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	// �ړ��x�N�g���̏�����
	m_directionVec = VGet(0.0f, 0.0f, 0.0f);

	//�X�e�B�b�N�ł̃A�i���O���͏�Ԃ��������Ă���Ƃ��͂�������D�悷��
	if (input.X != 0 || input.Y != 0)
	{
		m_directionVec.x = 0.001f * input.X;
		m_directionVec.z = 0.001f * input.Y;
	}
	else
	{
		// ���{�^���������ꂽ��v���C���[�̌���������
		if (Pad::isPress(PAD_INPUT_LEFT))
		{
			m_directionVec.x = kLeft;
		}
		// �E�{�^���������ꂽ��v���C���[�̌����E��
		else if (Pad::isPress(PAD_INPUT_RIGHT))
		{
			m_directionVec.x = kRight;
		}
		else
		{
			m_directionVec.x = kZero;
		}

		// ��{�^���������ꂽ��v���C���[�̌��������
		if (Pad::isPress(PAD_INPUT_UP))
		{
			m_directionVec.z = kUp;
		}
		// ���{�^���������ꂽ��v���C���[�̌�������
		else if (Pad::isPress(PAD_INPUT_DOWN))
		{
			m_directionVec.z = kDown;
		}
		else
		{
			m_directionVec.z = kZero;
		}
	}

	//�ړ������x�N�g���𐳋K��
	if (VSize(m_directionVec) >= 1.0f)
	{
		m_directionVec = VNorm(m_directionVec);
	}
}

void MoveDirectionVec::SetDirectionVec()
{
	// �ړ������x�N�g����������
	m_directionVec = VGet(0.0f, kUp, 0.0f);
}