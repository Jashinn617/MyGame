#include "Capsule.h"

Capsule::Capsule(const VECTOR topPos, const VECTOR bottomPos, float radius):
	m_radius(radius)
{
	m_collInfo.topPos = topPos;
	m_collInfo.bottomPos = bottomPos;
}

Capsule::~Capsule()
{
	/*��������*/
}

void Capsule::DebugDraw(unsigned int color)
{
	// �f�o�b�O�\��
#ifdef _DEBUG
	// �`��
	DrawCapsule3D(m_collInfo.topPos, m_collInfo.bottomPos,
		m_radius, 1, color, color, false);
#endif // _DEBUG
}

bool Capsule::IsCollide(const std::shared_ptr<Capsule> target) const
{
	// �����蔻��
	return HitCheck_Capsule_Capsule(m_collInfo.topPos, m_collInfo.bottomPos, m_radius,
		target->GetCollInfo().topPos, target->GetCollInfo().bottomPos, target->GetRadius());
}
