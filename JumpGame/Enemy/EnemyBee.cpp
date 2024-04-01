#include "EnemyBee.h"

namespace
{
	// �G�̃X�P�[��
	constexpr float kScale = 0.005f;
}

EnemyBee::EnemyBee(int modelHandle):
	EnemyBase(modelHandle)
{
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Update()
{
	
	// ���f���̃X�P�[�������肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// ���f���̈ʒu�ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 90.0f, 0.0f));
}
