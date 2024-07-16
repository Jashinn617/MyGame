#pragma once
#include "EnemyBase.h"
class EnemyBee : public EnemyBase
{
public:
	EnemyBee(int modelHandle);
	virtual ~EnemyBee();

	virtual void Init();
	virtual void Update();
};