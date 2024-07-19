#include "ItemRotationMove.h"

#include <math.h>

namespace
{
	constexpr float kAngleZ = 270.0f * DX_PI_F / 180.0f;		// Z軸の角度
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
	// 初期位置の設定
	MV1SetPosition(m_modelHandle, m_pos);
	// 円の中心の設定
	m_centerX = m_pos.x;
	m_centerZ = m_pos.z;
	// 角度の設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, kAngleZ));
}

void ItemRotationMove::Update()
{
	/*移動処理*/
	// 現在の位置
	m_pos.x = m_centerX + m_radius * cosf(m_angle);
	m_pos.z = m_centerZ + m_radius * sinf(m_angle);

	m_angle += m_angleSpeed;

	// 移動
	MV1SetPosition(m_modelHandle, m_pos);

}
