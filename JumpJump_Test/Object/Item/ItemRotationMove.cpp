#include "ItemRotationMove.h"

#include <math.h>

namespace
{
	constexpr float kAngleZ = 270.0f * DX_PI_F / 180.0f;		// Z���̊p�x
}

ItemRotationMove::ItemRotationMove(int modelHandle):
	ItemBase(modelHandle),
	m_centerX(0),
	m_centerZ(0)
{
}

ItemRotationMove::~ItemRotationMove()
{
}

void ItemRotationMove::Init()
{
	// �����ʒu�̐ݒ�
	MV1SetPosition(m_modelHandle, m_pos);
	// �~�̒��S�̐ݒ�
	m_centerX = m_pos.x;
	m_centerZ = m_pos.z;
	// �p�x�̐ݒ�
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, kAngleZ));
}

void ItemRotationMove::Update()
{
	/*�ړ�����*/
	// ���݂̈ʒu
	m_pos.x = m_centerX + m_radius * cosf(m_angle);
	m_pos.z = m_centerZ + m_radius * sinf(m_angle);

	m_angle += m_angleSpeed;

	// �ړ�
	MV1SetPosition(m_modelHandle, m_pos);

}
