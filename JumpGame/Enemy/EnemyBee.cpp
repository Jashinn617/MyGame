#include "EnemyBee.h"



EnemyBee::EnemyBee(int modelHandle):
	EnemyBase(modelHandle)
{
	/*処理無し*/
}

EnemyBee::~EnemyBee()
{
	/*処理無し*/
}

void EnemyBee::Update()
{
	AdjustmentModelPos();
}
