#include "PlayerState.h"

#include "../../Utility/Pad.h"

PlayerState::PlayerState():
	m_isAction(false)
{
	/*��������*/
}

PlayerState::~PlayerState()
{
	/*��������*/
}

void PlayerState::Update()
{
	// ��ԑJ��
	StateTransition();

	// �X�e�C�g�X�V
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
