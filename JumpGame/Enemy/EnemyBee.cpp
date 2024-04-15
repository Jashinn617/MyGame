#include "EnemyBee.h"



EnemyBee::EnemyBee(int modelHandle):
	EnemyBase(modelHandle)
{
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Update()
{
	SetModelPos();
}
