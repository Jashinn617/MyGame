#include "EnemyBee.h"


namespace
{
	constexpr float kPlayAnimSpeed = 0.5f;	// �A�j���[�V�������x
	constexpr int kAnimNum = 2;				// �A�j���[�V�����ԍ�
}

EnemyBee::EnemyBee(int modelHandle) :
	EnemyBase(modelHandle),
	m_currentAnimNo(-1),
	m_isTurn(false)
{
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Init()
{
	MV1SetPosition(m_modelHandle, m_pos);
	// �A�j���[�V�����̐ݒ�
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, kAnimNum, -1, false);
}

void EnemyBee::Update()
{
	// �A�j���[�V�����̍X�V
	UpdateAnim(m_currentAnimNo);

	// �p�x�̍X�V
	UpdateAngle();
}

bool EnemyBee::UpdateAnim(int attachNo)
{
	bool isLoop = false;

	/*�A�j���[�V������i�s������*/
	// ���݂̍Đ��J�E���g
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);
	// �A�j���[�V������i�߂�
	now += kPlayAnimSpeed;
	// ���ݍĐ����̃A�j���[�V�����̑��J�E���g
	float total = MV1GetAttachAnimTotalTime(m_modelHandle, attachNo);

	// �A�j���[�V���������[�v������
	while (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	// �A�j���[�V������i�߂����Ԃɐݒ肷��
	MV1SetAttachAnimTime(m_modelHandle, attachNo, now);

	return isLoop;
}

void EnemyBee::Move()
{

}

