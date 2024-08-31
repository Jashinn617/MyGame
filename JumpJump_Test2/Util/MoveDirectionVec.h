#pragma once
#include "DxLib.h"

class Input;

class MoveDirectionVec
{
public:
	MoveDirectionVec();
	~MoveDirectionVec();

	void Update(Input& input_);

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

