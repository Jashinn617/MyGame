#include "EnemySkull.h"

EnemySkull::EnemySkull(int modelHandle):
	EnemyBase(modelHandle)
{
	/*処理無し*/
}

EnemySkull::~EnemySkull()
{
	/*処理無し*/
}

void EnemySkull::Update()
{
	AdjustmentModelPos();
}
