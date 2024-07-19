#pragma once
#include "EnemyBase.h"
class EnemyBee : public EnemyBase
{
public:
	EnemyBee(int modelHandle);
	virtual ~EnemyBee();

	virtual void Init();
	virtual void Update();

private:
	bool UpdateAnim(int attachNo);
	void Move();

private:
	int m_currentAnimNo;	// ���݂̃A�j���[�V�����ԍ�
	bool m_isTurn;		// ���]�����ǂ���
};