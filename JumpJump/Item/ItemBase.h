#include "DxLib.h"
#pragma once
class ItemBase
{
public:
	ItemBase(int modelHandle);
	virtual ~ItemBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const {}
	void SetPos(const VECTOR pos) { m_pos = pos; }

protected:	// �֐�
	void UpdateAngle();

protected:	// �ϐ�
	int m_modelHandle;	// ���f���n���h��
	int  m_psH;			// �s�N�Z���V�F�[�_�n���h��
	int m_vsH;			// ���_�V�F�[�_�n���h��
	float m_rad;		// ���a
	float m_scale;		// �X�P�[��
	VECTOR m_pos;		// �ʒu
	float m_angle;		// �p�x
};