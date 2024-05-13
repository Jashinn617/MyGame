#include "DxLib.h"
#include "Camera.h"
#include "Player.h"

#include "Util/Input.h"

Camera::Camera(shared_ptr<Player> player):
	m_pos{0,0,0},
	m_angle(-DX_PI_F/2),
	m_pPlayer(player)
{
	
}

Camera::~Camera()
{
	/*��������*/
}

void Camera::Update(Input& input)
{
	// �J�����̉�]
	if (input.IsPressing("R"))
	{
		m_angle += kSpeed;
	}
	if (input.IsPressing("L"))
	{
		m_angle -= kSpeed;
	}
	m_pPlayer->SetCameraAngle(m_angle);

	// �J�����̕`��͈͂̐ݒ�
	SetCameraNearFar(kCameraNear, kCameraFar);
	VECTOR playerPos = m_pPlayer->GetPos();

	// �J�����̉�]����
	m_pos.x = playerPos.x + cosf(m_angle) * kCameraDist;
	m_pos.y = kCameraHeight;
	m_pos.z = playerPos.z + sinf(m_angle) * kCameraDist;

	VECTOR targetPos = VGet(playerPos.x, 1.0f, playerPos.z);

	// �J�����̈ʒu�ݒ�
	SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
}
