#pragma once
#include "DxLib.h"

class MoveDirectionVec
{
public:
	MoveDirectionVec();
	~MoveDirectionVec();

	void Update();

	/// <summary>
	/// �ړ�������ݒ肷��
	/// </summary>
	void SetDirectionVec();

	/// <summary>
	/// �ړ������̎擾
	/// </summary>
	/// <returns>�ړ�����</returns>
	VECTOR GetDirectionVec()const { return m_directionVec; }

private:
	VECTOR m_directionVec;	// �����x�N�g��
};

