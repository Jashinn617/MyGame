#include "Camera.h"
#include "Player.h"
#include <vector>

Camera::Camera():
	m_pos{0,0,0}
{
	// ���s0.1�`1000�܂ł��J�����̕`��͈͂ɂ���
	SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera()
{
	// ��������
}

void Camera::Update(const Player& playr)
{
	// �傫��0.5�̃}�b�v�`�b�v���A�ۑ蓖����StageData1ColNum��(16)�z�u����
	// �v���C���[�̒n�ʂ�Y�ʒu��0�Ƃ������̂ŁA�n�㕔�̃}�b�v�`�b�v�̐��͓���炵���ʒu�Œ���
	// ���̐^�񒆂ɕ\������̂Ŕ������v�Z�ŏo��
	// �v���C���[��X���W�ɂ͒Ǐ]�������̂�player��X���g��
}
