#include "Camera.h"
#include "Player.h"

Camera::Camera():
	m_pos{0,0,0}
{
	// ƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚Ìİ’è
	// ‰œs0.1`1000‚Ü‚Å‚ğ•`‰æ”ÍˆÍ‚É‚·‚é
	SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera()
{
	/*ˆ—–³‚µ*/
}

void Camera::Update(const Player& player)
{
	VECTOR playerPos = player.GetPos();
	VECTOR cameraPos = VGet(playerPos.x, 3.0f, playerPos.z - 6);

	VECTOR targetPos = VGet(playerPos.x, 1.0f, playerPos.z);

	m_pos = cameraPos;

	// ƒJƒƒ‰‚ÉˆÊ’u‚ğ”½‰f‚·‚é
	SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
}
