#pragma once
#include "DxLib.h"

/// <summary>
/// �ړ������x�N�g�����擾����N���X
/// </summary>
class MoveDirectionVec
{
public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MoveDirectionVec();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~MoveDirectionVec();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ������̎擾
	/// </summary>
	/// <returns>�ړ�����</returns>
	VECTOR GetDirectionVec()const { return m_direction; }

private:	// �ϐ�
	VECTOR m_direction;		// ����

};

