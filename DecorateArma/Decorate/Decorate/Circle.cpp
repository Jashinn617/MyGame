#include "Circle.h"

#include <math.h>

Circle::Circle(const VECTOR& center, float radius, float height):
	m_radius(radius),
	m_height(height),
	m_center(&center)
{
	/*��������*/
}

Circle::~Circle()
{
	/*��������*/
}

void Circle::DebugDraw(unsigned int color)
{
	// �f�o�b�O�\��
#ifdef _DEBUG
	// �������W�̎擾
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// �`��
	DrawSphere3D(center, m_radius, 32, color, color, false);
#endif // _DEBUG
}

bool Circle::IsCollide(const std::shared_ptr<Circle> target) const
{
	// �^�񒆂̍��W
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// ����̐^�񒆂̍��W
	VECTOR targetCenter = VAdd(*target->m_center, VGet(0.0f, target->m_height, 0.0f));

	// ����̒��S�Ǝ����̒��S�̋����̌v�Z
	float distance = static_cast<float>(fabs(VSize(VSub(targetCenter, center))));
	// ���a�̍��v�̌v�Z
	float radius = m_radius + target->m_radius;

	// ����̒��S�Ǝ����̒��S�̋��������a�̍��v�ȉ��������ꍇ�͓������Ă���
	return distance <= radius;
}
