#include "EnemyBase.h"

EnemyBase::EnemyBase(int modelHandle):
	m_modelHandle(-1),
	m_pos{0,0,0},
	m_rad(kRadius)
{
	// ���f���̓ǂݍ���
	m_modelHandle = MV1DuplicateModel(modelHandle);
}

EnemyBase::~EnemyBase()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void EnemyBase::Update()
{
	/*��������*/
}

void EnemyBase::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG

	VECTOR pos =VAdd(MV1GetPosition(m_modelHandle),VGet(0,0.3,0));

	DrawSphere3D(pos, kRadius, 32, 0xff0000, 0xff0000, false);

#endif // _DEBUG
}

const VECTOR& EnemyBase::GetPos() const
{
	return MV1GetPosition(m_modelHandle);
}

void EnemyBase::AdjustmentModelPos()
{
	// ���f���̃X�P�[�������肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// ���f���̈ʒu�ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
}



