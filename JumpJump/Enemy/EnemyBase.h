#pragma once
#include "DxLib.h"
#include <vector>

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
	void SetPos(const VECTOR pos) { m_pos = pos; }

protected:	// �֐�
	int GetModelHandle()const { return m_modelHandle; }

	/// <summary>
	/// ���f���̈ʒu����
	/// </summary>
	void AdjustmentModelPos()const;

	// �p�x�̍X�V
	void UpdateAngle();

protected:	// �ϐ�
	int m_modelHandle;	// ���f���n���h��
	std::vector<int> m_psHs;		// �s�N�Z���V�F�[�_�n���h��
	std::vector<int> m_vsHs;		// ���_�V�F�[�_�n���h��
	std::vector<int> m_pixelShaderNumbers;	// �ǂ̃s�N�Z���V�F�[�_���g����
	std::vector<int> m_vertexShaderNumbers;	// �ǂ̒��_�V�F�[�_���g����
	float m_rad;		// ���a
	float m_scale;		// �X�P�[��
	VECTOR m_pos;		// �ʒu
	float m_angle;		// �p�x
	VECTOR m_targetDir;	// �������������̃x�N�g��
};

