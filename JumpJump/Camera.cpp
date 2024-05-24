#include "DxLib.h"
#include "Camera.h"
#include "Util/Input.h"
#include "Player.h"
#include "Stage/StageTest.h"

void Camera::Init()
{
	m_angle = DX_PI_F;

}

void Camera::Update(const Input& input, const Player& player, const StageTest& stage)
{
	if (input.IsPressing("R"))
	{
		m_angle -= kSpeed;

		// �p�x��-180����菬�����Ȃ����ꍇ�A�p�x�l���傫���Ȃ肷���Ȃ��悤��360���𑫂�
		if (m_angle < -DX_PI_F)
		{
			m_angle += DX_TWO_PI_F;
		}
	}
	if (input.IsPressing("L"))
	{
		m_angle += kSpeed;

		// �p�x��-180�����傫���Ȃ����ꍇ�A�p�x�l���傫���Ȃ肷���Ȃ��悤��360��������
		if (m_angle > DX_PI_F)
		{
			m_angle -= DX_TWO_PI_F;
		}
	}

	// �J�����̒����_�̐ݒ�
	// �^�[�Q�b�g�������������ʒu�𒍎��_�ɂ���
	m_targetpos = VAdd(player.GetPos(), VGet(0.0f, kTargetH, 0.0f));

	// �J�����̍��W��ݒ肷��
	/*��Ŋ֐���������*/
	{
		MATRIX RotY;				// �J�����̉�]�Ɏg���s��
		float CameraToTargetDir;	// �J�����ƃ^�[�Q�b�g�̋���

		// �J������Y����]�̎擾
		RotY = MGetRotY(m_angle);

		// �J��������^�[�Q�b�g�܂ł̏����̋���
		CameraToTargetDir = kStartTargetDir;

		// �J�������W�̌v�Z
		m_pos = VAdd(VTransform(VGet(-CameraToTargetDir, 0.0f, 0.0f), RotY));

		/*�X�e�[�W�Ƃ̓����蔻��*/
		// ��ł��
		// �֐�������̂͂��̕���������������Ȃ�

	}

	// �J�����̈ʒu��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetpos);

}
