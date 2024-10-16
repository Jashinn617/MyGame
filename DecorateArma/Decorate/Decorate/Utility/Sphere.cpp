#include "Sphere.h"

#include <math.h>

Sphere::Sphere(const VECTOR& center, float radius, float height):
	m_radius(radius),
	m_height(height),
	m_center(&center)
{
	/*��������*/
}

Sphere::~Sphere()
{
	/*��������*/
}

void Sphere::DebugDraw(unsigned int color)
{
	// �f�o�b�O�\��
#ifdef _DEBUG
	// �������W�̎擾
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// �`��
	DrawSphere3D(center, m_radius, 32, color, color, false);
#endif // _DEBUG
}

bool Sphere::IsCollide(const std::shared_ptr<Sphere> target) const
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
