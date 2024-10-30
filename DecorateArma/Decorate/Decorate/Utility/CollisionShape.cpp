#include "CollisionShape.h"

CollisionShape::CollisionShape(const VECTOR& topPos, const VECTOR& bottomPos, float radius):
	m_radius(radius),
	m_height(0.0f),
	m_center(nullptr),
	topPos(&topPos),
	bottomPos(&bottomPos),
	m_shapeType(ShapeType::Capsule)
{
	/*処理無し*/
}

CollisionShape::CollisionShape(const VECTOR& center, float radius, float height):
	m_radius(radius),
	m_height(m_height),
	m_center(&center),
	topPos(nullptr),
	bottomPos(nullptr),
	m_shapeType(ShapeType::Sphere)
{
	/*処理無し*/
}

CollisionShape::~CollisionShape()
{
	/*処理無し*/
}

void CollisionShape::DebugDraw(unsigned int color)
{
	// デバッグ表示
#ifdef _DEBUG

	// 図形のタイプによって処理を変える

#endif // _DEBUG
}

bool CollisionShape::IsCollide(const std::shared_ptr<CollisionShape> target) const
{
	// 自分と相手の図形のタイプによって処理を変える


	return false;
}
