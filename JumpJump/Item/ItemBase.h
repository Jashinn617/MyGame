#include "DxLib.h"
#pragma once
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const {}

protected:	// �ϐ�
	int m_modelHandle;	// ���f���n���h��
	int  m_psH;			// �s�N�Z���V�F�[�_�n���h��
	int m_vsH;			// ���_�V�F�[�_�n���h��
	float m_rad;		// ���a
	float m_scale;		// �X�P�[��
	VECTOR m_pos;		// �ʒu
	VECTOR m_angle;
};