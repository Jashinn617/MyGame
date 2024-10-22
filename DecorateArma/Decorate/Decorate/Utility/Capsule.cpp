#include "Capsule.h"

Capsule::Capsule(const VECTOR& topPos, const VECTOR& bottomPos, float radius):
	m_radius(radius),
	topPos(&topPos),
	bottomPos(&bottomPos)
{
	/*処理無し*/
}

Capsule::~Capsule()
{
	/*処理無し*/
}

void Capsule::DebugDraw(unsigned int color)
{
	// デバッグ表示
#ifdef _DEBUG
	// 描画
	DrawCapsule3D(*topPos, *bottomPos,
		m_radius, 32, color, color, false);
#endif // _DEBUG
}

bool Capsule::IsCollide(const std::shared_ptr<Capsule> target) const
{
	// 当たり判定
	return HitCheck_Capsule_Capsule(*topPos, *bottomPos, m_radius,
		*target->topPos, *target->bottomPos, target->GetRadius());
}
