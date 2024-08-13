#include "ItemBase.h"
#include "../Player/Player.h"
#include "../ObjectBase.h"
#include "../Model.h"
#include "../Circle.h"
#include "../../Util/Time.h"
#include "../../Util/Input.h"
#include <assert.h>

ItemBase::ItemBase()
{
}

ItemBase::ItemBase(VECTOR pos)
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Init()
{
}

void ItemBase::Update(Input& input)
{
}

void ItemBase::Draw()
{
}

void ItemBase::Draw2D()
{
}

void ItemBase::OnGet()
{
}

void ItemBase::StageClear()
{
}

void ItemBase::InitMoveSpeed(float moveSpeed)
{
}

void ItemBase::AngleUpdate()
{
}

void ItemBase::MoveDirectionUpdate()
{
}

VECTOR ItemBase::MoveUpdate()
{
	return VECTOR();
}

void ItemBase::StateTransitionUpdate()
{
}

bool ItemBase::StateTransitionMove()
{
	return false;
}

bool ItemBase::StateTransitionDead()
{
	return false;
}

void ItemBase::IdleStateUpdate()
{
}

void ItemBase::MoveStateUpdate()
{
}

void ItemBase::DeadStateUpdate()
{
}
