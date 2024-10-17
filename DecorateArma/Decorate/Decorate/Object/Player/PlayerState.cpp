#include "PlayerState.h"

#include "Player.h"

#include "../../Utility/Pad.h"

PlayerState::PlayerState(Player* player):
	m_isAction(false),
	m_nowState(StateKind::Idle),
	m_pPlayer(player)
{
	/*��������*/
}

PlayerState::~PlayerState()
{
	// �|�C���^�̉��
	delete(m_pPlayer);
	m_pPlayer = nullptr;
}

void PlayerState::Update()
{
	// ��ԑJ��
	StateTransition();

	// ����A������ԂłȂ��Ƃ��̓T�E���h���~�߂�
}

void PlayerState::OnDamage()
{
	// ���݂̏�Ԃ��_���[�W��Ԃ������ꍇ�͉������Ȃ�
	if (m_nowState == StateKind::Damage) return;

}

void PlayerState::SetState(StateKind stateKind)
{
	for (int i = 0; i < static_cast<int>(StateKind::StateNum); i++)
	{
		// �X�e�C�g�̎�ނ��w��̃X�e�C�g�̏ꍇ
		if (static_cast<int>(stateKind) == i)
		{
			// ��Ԃ�ύX����
			m_nowState = static_cast<StateKind>(i);
			return;
		}
	}
}

void PlayerState::EndState()
{
	// �A�N�V������Ԃ̏I��
	m_isAction = false;
}

void PlayerState::StateTransitionIdle()
{
	// �A�N�V�������̏ꍇ�͉������Ȃ�
	if (m_isAction) return;

	// �ړ��{�^��������������Ă��Ȃ������ꍇ
	if (!Pad::IsPress(PAD_INPUT_LEFT) && !Pad::IsPress(PAD_INPUT_RIGHT) &&
		!Pad::IsPress(PAD_INPUT_UP) && !Pad::IsPress(PAD_INPUT_DOWN))
	{
		// �X�e�C�g��ҋ@��Ԃɂ���
		ChangeState(StateKind::Idle);
	}
}

void PlayerState::StateTransitionWalk()
{
	// �A�N�V�������̏ꍇ�͉������Ȃ�
	if (m_isAction) return;

	// �ړ��{�^�����������牟����Ă����ꍇ
	if (Pad::IsPress(PAD_INPUT_LEFT) || Pad::IsPress(PAD_INPUT_RIGHT) ||
		Pad::IsPress(PAD_INPUT_UP) || Pad::IsPress(PAD_INPUT_DOWN))
	{
		// �X�e�C�g�������Ԃɂ���
		ChangeState(StateKind::Walk);
	}
}

void PlayerState::StateTransitionDash()
{
	// �A�N�V�������̏ꍇ�͉������Ȃ�
	if (m_isAction) return;

	//�ړ��{�^����������Ă��Ȃ������牽�����Ȃ�
	if (!Pad::IsPress(PAD_INPUT_LEFT) && !Pad::IsPress(PAD_INPUT_RIGHT) &&
		!Pad::IsPress(PAD_INPUT_UP) && !Pad::IsPress(PAD_INPUT_DOWN)) return;

	// RB��������Ă����ꍇ
	if (Pad::IsPress(PAD_INPUT_6))
	{
		// �X�e�C�g���_�b�V����Ԃɂ���
		ChangeState(StateKind::Dash);
	}
}

void PlayerState::StateTransitionJump()
{
	// �A�N�V�������̏ꍇ�͉������Ȃ�
	if (m_isAction) return;

	// A�{�^���������ꂽ�ꍇ
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// �A�N�V�����t���O�𗧂Ă�
		m_isAction = true;
		// �X�e�C�g���W�����v��Ԃɂ���
		ChangeState(StateKind::Jump);
	}
}

void PlayerState::StateTransition()
{
	// ��ԑJ��
	StateTransitionIdle();
	StateTransitionWalk();
	StateTransitionDash();
	StateTransitionJump();
}

void PlayerState::ChangeState(StateKind stateKind)
{
	for (int i = 0; i < static_cast<int>(StateKind::StateNum); i++)
	{
		// �X�e�C�g�̎�ނ��w��̃X�e�C�g�̏ꍇ
		if (static_cast<int>(stateKind) == i)
		{
			// ���݂̃X�e�C�g���w��̃X�e�C�g�ɕύX
			m_nowState = static_cast<StateKind>(i);
			// �X�e�C�g�̏�����
			m_pPlayer->InitState();
			return;
		}
	}
}
