#include "Circle.h"

Circle::Circle(const VECTOR& center, float radius, float height):
	m_radius(radius),
	m_height(height),
	m_center(&center)
{
	/*処理無し*/
}

Circle::~Circle()
{
	/*処理無し*/
}

void Circle::DebugDraw()
{
#ifdef _DEBUG
	/*デバッグ表示*/
	// 真ん中の座標
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// 描画
	DrawSphere3D(center, m_radius, 32, 0x00ffff, 0x00ffff, false);
#endif // _DEBUG
}

bool Circle::IsCollide(const std::shared_ptr<Circle> that) const
{
	// 真ん中の座標
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// 相手の真ん中の座標
	VECTOR targetCenter = VAdd(*that->m_center, VGet(0.0f, that->m_height, 0.0f));

	// 相手と自分の中心の距離
	float distance = static_cast<float>(fabs(VSize(VSub(targetCenter, center))));
	// 半径の合計
	float radius = m_radius + that->m_radius;

	// 相手と自分の中心の距離が半径の合計以下だった場合
	return distance <= radius;
}
