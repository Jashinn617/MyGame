#include "EnemyCrab.h"

EnemyCrab::EnemyCrab(int modelHandle):
	EnemyBase(modelHandle)
{
}

EnemyCrab::~EnemyCrab()
{
}

void EnemyCrab::Update()
{
	SetModelPos();
}
