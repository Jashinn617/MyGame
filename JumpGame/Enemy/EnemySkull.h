#pragma once
#include "EnemyBase.h"
class EnemySkull : public EnemyBase
{
public:
	EnemySkull(int modelHandle);
	virtual ~EnemySkull();

	void Update();
};

