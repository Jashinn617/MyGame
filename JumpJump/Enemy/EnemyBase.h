#pragma once
#include "DxLib.h"

class EnemyBase
{
public:
	EnemyBase(int modelHandle);
	virtual ~EnemyBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const { return m_pos; }
	const float GetRad() const { return m_rad; }

protected:	// �֐�
	int GetModelHandle()const { return m_modelHandle; }

protected:	// �ϐ�
	int m_modelHandle;	// ���f���n���h��
	float m_rad;		// ���a
	float m_scale;		// �X�P�[��
	VECTOR m_pos;		// �ʒu
	VECTOR m_angle;		// ��]
};

