#include "EnemySkull.h"

EnemySkull::EnemySkull(int modelHandle):
	EnemyBase(modelHandle)
{
}

EnemySkull::~EnemySkull()
{
}

void EnemySkull::Update()
{
	SetModelPos();
}
