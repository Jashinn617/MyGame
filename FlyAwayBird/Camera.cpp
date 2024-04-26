#include "Camera.h"
#include "Player.h"

Camera::Camera():
	m_pos{0,0,0}
{
	// �J�����̕`��͈͂̐ݒ�
	// ���s0.1�`1000�܂ł�`��͈͂ɂ���
	SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera()
{
	/*��������*/
}

void Camera::Update(const Player& player)
{
	VECTOR playerPos = player.GetPos();
	VECTOR cameraPos = VGet(playerPos.x, 3.0f, playerPos.z - 6);

	VECTOR targetPos = VGet(playerPos.x, 1.0f, playerPos.z);

	m_pos = cameraPos;

	// �J�����Ɉʒu�𔽉f����
	SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
}
