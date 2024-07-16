#include "EnemyBee.h"

EnemyBee::EnemyBee(int modelHandle):
	EnemyBase(modelHandle)
{
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Init()
{
	AdjustmentModelPos();
}

void EnemyBee::Update()
{
}