#pragma once
#include "DxLib.h"

// �G�N���X�̃x�[�X
class EnemyBase abstract
{
public:
	EnemyBase(int modelHandle);
	virtual ~EnemyBase();

	virtual void Update() abstract;	// �X�V
	virtual void Draw();	// �`��

	// ���f���n���h���̎擾
	int GetModelHandle()const { return m_modelHandle; }

	// 
	const VECTOR& GetPos() const;
	void SetPos(const VECTOR pos) { m_pos = pos; }
	void SetModelPos();
	const float GetRad()const { return m_rad; }

	

protected:
	int m_modelHandle;
	float m_rad;
	VECTOR m_pos;
};

