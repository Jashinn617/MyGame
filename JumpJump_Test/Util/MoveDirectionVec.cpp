#include "MoveDirectionVec.h"
#include "../Util/Input.h"
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
	m_directionVec{0,0,0}
{
}

MoveDirectionVec::~MoveDirectionVec()
{
}

void MoveDirectionVec::Update(Input& input)
{
	// �ړ��x�N�g���̏�����
	m_directionVec = VGet(0.0f, 0.0f, 0.0f);

	// ���{�^���������ꂽ��v���C���[�̌���������
	if (input.IsPressing("left"))
	{
		m_directionVec.x = kLeft;
	}
	// �E�{�^���������ꂽ��v���C���[�̌������E��
	else if (input.IsPressing("right"))
	{
		m_directionVec.x = kRight;
	}
	else
	{
		m_directionVec.x = kZero;
	}

	// ��{�^���������ꂽ��v���C���[�̌��������
	if (input.IsPressing("up"))
	{
		m_directionVec.z = kUp;
	}
	// ���{�^���������ꂽ��v���C���[�̌���������
	else if (input.IsPressing("down"))
	{
		m_directionVec.z = kDown;
	}
	else
	{
		m_directionVec.z = kZero;
	}

	// �ړ������x�N�g���𐳋K������
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