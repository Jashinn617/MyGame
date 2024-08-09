#include "EnemyBase.h"

EnemyBase::EnemyBase():
	m_createTime(0)

{
}

EnemyBase::EnemyBase(VECTOR pos)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update(Input& input)
{
}

void EnemyBase::Draw()
{
}

void EnemyBase::Draw2D()
{
}

void EnemyBase::StageClear()
{
}

void EnemyBase::OnDamage(VECTOR targetPos)
{
}

void EnemyBase::EndJump()
{
}

void EnemyBase::InitMoveSpeed(float moveSpeed)
{
}

void EnemyBase::AngleUpdate()
{
}

void EnemyBase::MoveDirectionUpdate()
{
}

VECTOR EnemyBase::MoveUpdate()
{
	return VECTOR();
}

void EnemyBase::StateTransitionUpdate()
{
}

bool EnemyBase::TransitionMove()
{
	return false;
}

bool EnemyBase::TransitionKnockBack()
{
	return false;
}

bool EnemyBase::TransitionDead()
{
	return false;
}

void EnemyBase::IdleStateUpdate()
{
}

void EnemyBase::MoveStateUpdate()
{
}

void EnemyBase::KnockBackStateUpdate()
{
}

void EnemyBase::DeadStateUpdate()
{
}
