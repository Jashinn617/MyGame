#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	// �X�N���[���T�C�Y
	constexpr int kScreenWidth = Game::kScreenWidth;
	constexpr int kScreenHeight = Game::kScreenHeight;

	// �e�}�b�v�̉���
	constexpr int kHorizontalMapWidth = Game::kScreenWidth * 5;
	constexpr int kVerticalMapWidth = Game::kScreenWidth;
	constexpr int kMixtureMapWidth = Game::kScreenWidth;
	// �e�}�b�v�̏c��
	constexpr int kHorizontalMapHeight = Game::kScreenHeight;
	constexpr int kVerticalMapHeight = Game::kScreenHeight * 5;
	constexpr int kMixtureMapHeight = Game::kScreenHeight;

}

Camera::Camera() :
	m_mapWidth(0),
	m_mapHeight(0),
	m_scrollPattern(kHorizontal)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// �}�b�v�̑傫�������߂�
	// MEMO:��ŕς���
	switch (m_scrollPattern)
	{
	case kHorizontal:
		m_mapWidth = kHorizontalMapWidth;
		m_mapHeight = kHorizontalMapHeight;
		break;
	case kHorizontal2:
		m_mapWidth = kScreenWidth * 2;
		m_mapHeight = kScreenHeight;
		break;
	case kVertical:
		m_mapWidth = kVerticalMapWidth;
		m_mapHeight = kVerticalMapHeight;
		break;
	case kMixture:
		m_mapWidth = kMixtureMapWidth;
		m_mapHeight = kMixtureMapHeight;
	default:
		break;
	}
}

int Camera::GetScrollX()
{
	int result = static_cast<int>(m_pPlayer->GetX() - kScreenWidth * 0.5f);
	// �ŏ��l
	result = max(0, result);
	// �ő�l
	result = min(m_mapWidth - kScreenWidth, result);

	return result;
}

int Camera::GetScrollY()
{
	int result = static_cast<int>(m_pPlayer->GetY() - kScreenHeight * 0.5f);

	if (result < 0)
	{
		result = 0;
	}
	if (result > m_mapHeight - kScreenHeight)
	{
		result = m_mapHeight - kScreenHeight;
	}

	return result;
}