#pragma once
#include "EnemyBase.h"

#include <memory>

class EnemyBee : public EnemyBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="direction">��������</param>
	/// <param name="turnTime">���]����܂ł̎���</param>
	/// <param name="speed">�ړ��X�s�[�h</param>
	EnemyBee(VECTOR pos, VECTOR direction, int turnTime, float speed);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyBee();

	/// <summary>
	/// ������
	/// </summary>
	void Init()override final;

	/// <summary>
	/// �ړ������X�V
	/// </summary>
	void MoveDirectionUpdate() override final;

	/// <summary>
	/// �ړ��X�V
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate() override final;
};

