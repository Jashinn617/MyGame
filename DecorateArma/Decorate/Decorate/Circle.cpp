#include "Circle.h"

#include <math.h>

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

void Circle::DebugDraw(unsigned int color)
{
	// デバッグ表示
#ifdef _DEBUG
	// 中央座標の取得
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// 描画
	DrawSphere3D(center, m_radius, 32, color, color, false);
#endif // _DEBUG
}

bool Circle::IsCollide(const std::shared_ptr<Circle> target) const
{
	// 真ん中の座標
	VECTOR center = VAdd(*m_center, VGet(0.0f, m_height, 0.0f));
	// 相手の真ん中の座標
	VECTOR targetCenter = VAdd(*target->m_center, VGet(0.0f, target->m_height, 0.0f));

	// 相手の中心と自分の中心の距離の計算
	float distance = static_cast<float>(fabs(VSize(VSub(targetCenter, center))));
	// 半径の合計の計算
	float radius = m_radius + target->m_radius;

	// 相手の中心と自分の中心の距離が半径の合計以下だった場合は当たっている
	return distance <= radius;
}
