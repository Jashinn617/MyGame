#include "PlayerState.h"

#include "../../Utility/Pad.h"

PlayerState::PlayerState():
	m_isAction(false)
{
	/*処理無し*/
}

PlayerState::~PlayerState()
{
	/*処理無し*/
}

void PlayerState::Update()
{
	// 状態遷移
	StateTransition();

	// ステイト更新
}

void PlayerState::OnDamage()
{
}

void PlayerState::SetState(StateKind stateKind)
{
}

void PlayerState::EndState()
{
}

void PlayerState::StateTransitionIdle()
{
}

void PlayerState::StateTransitionWalk()
{
}

void PlayerState::StateTransitionDash()
{
}

void PlayerState::StateTransitionJump()
{
}

void PlayerState::StateTransition()
{
}

void PlayerState::StateChange(StateKind stateKind)
{
}
