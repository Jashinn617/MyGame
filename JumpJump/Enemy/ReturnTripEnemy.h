#pragma once
#include "EnemyBase.h"

class ReturnTripEnemy : public EnemyBase
{
public:
	ReturnTripEnemy(int modelHandle);
	virtual ~ReturnTripEnemy();

	void Init();
	void Update() override;


};

