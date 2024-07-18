#include "ItemNotMove.h"

#include <math.h>

namespace
{
	constexpr float kAngleZ = 270.0f * DX_PI_F / 180.0f;		// Z²‚ÌŠp“x
	constexpr float kMoveSinSpeed = 0.05f;						// ã‰ºˆÚ“®‚Ì‘¬“x
	constexpr float kMoveSwing = 0.1f;							// ã‰ºˆÚ“®‚ÌˆÚ“®•
}


ItemNotMove::ItemNotMove(int modelHandle):
	ItemBase(modelHandle),
	m_angleX(0),
	m_moveSinCount(0),
	m_posY(0)
{
	/*ˆ—–³‚µ*/
}

ItemNotMove::~ItemNotMove()
{
	/*ˆ—–³‚µ*/
}

void ItemNotMove::Init()
{
	MV1SetPosition(m_modelHandle, m_pos);
}

void ItemNotMove::Update()
{
	/*‰ñ“]ˆ—*/
	m_angleX += m_angleSpeed;
	// ‰ñ“]
	MV1SetRotationXYZ(m_modelHandle, VGet(m_angleX, 0.0f, kAngleZ));

	/*ˆÚ“®ˆ—*/
	m_moveSinCount += kMoveSinSpeed;
	m_posY = sinf(m_moveSinCount) * kMoveSwing;
	m_pos.y = m_pos.y + m_posY;
	// ˆÚ“®
	MV1SetPosition(m_modelHandle, m_pos);
}
