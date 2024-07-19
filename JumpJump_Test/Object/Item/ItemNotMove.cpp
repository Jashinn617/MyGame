#include "ItemNotMove.h"

#include <math.h>

namespace
{
	constexpr float kAngleZ = 270.0f * DX_PI_F / 180.0f;		// Z���̊p�x
	constexpr float kMoveSinSpeed = 0.05f;						// �㉺�ړ��̑��x
	constexpr float kMoveSwing = 0.1f;							// �㉺�ړ��̈ړ���
}


ItemNotMove::ItemNotMove(int modelHandle):
	ItemBase(modelHandle),
	m_angleX(0),
	m_moveSinCount(0),
	m_posY(0)
{
	/*��������*/
}

ItemNotMove::~ItemNotMove()
{
	/*��������*/
}

void ItemNotMove::Init()
{
	MV1SetPosition(m_modelHandle, m_pos);
}

void ItemNotMove::Update()
{
	/*��]����*/
	m_angleX += m_angleSpeed;
	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(m_angleX, 0.0f, kAngleZ));

	/*�ړ�����*/
	m_moveSinCount += kMoveSinSpeed;
	m_posY = sinf(m_moveSinCount) * kMoveSwing;
	m_pos.y = m_pos.y + m_posY;
	// �ړ�
	MV1SetPosition(m_modelHandle, m_pos);
}
