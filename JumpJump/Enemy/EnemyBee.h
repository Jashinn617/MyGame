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

private:
	int m_currentAnimNo;	// 現在のアニメーション番号
	bool m_isTurn;		// 反転中かどうか
};