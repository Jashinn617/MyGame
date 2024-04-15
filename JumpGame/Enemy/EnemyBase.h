#pragma once
#include "DxLib.h"

// �G�N���X�̃x�[�X
class EnemyBase abstract
{
public:
	EnemyBase(int modelHandle);
	virtual ~EnemyBase();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() abstract;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// ���f���n���h���̎擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle()const { return m_modelHandle; }

	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns>���݈ʒu</returns>
	const VECTOR& GetPos() const;
	/// <summary>
	/// �ʒu�̃Z�b�g
	/// </summary>
	/// <param name="pos">�Z�b�g�������ʒu</param>
	void SetPos(const VECTOR pos) { m_pos = pos; }
	/// <summary>
	/// ���f���̈ʒu�̒���
	/// </summary>
	void AdjustmentModelPos();
	/// <summary>
	/// ���a�̎擾
	/// </summary>
	/// <returns>���a</returns>
	const float GetRad()const { return m_rad; }	

protected:	// �ϐ�
	int m_modelHandle;		// 3D���f���̃n���h��
	float m_rad;			// ���a
	VECTOR m_pos;			// �ʒu

private: // �萔
	static constexpr float kScale = 0.005f;						// �X�P�[��
	static constexpr float kRadius = 0.3f;						// ���a
	static constexpr float kDirY = 180.0f * DX_PI_F / 270.0f;	// Y�������̌���
};

