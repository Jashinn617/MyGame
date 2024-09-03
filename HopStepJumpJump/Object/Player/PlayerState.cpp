#include "PlayerState.h"

#include "../../Util/Input.h"
#include "../../Util/Pad.h"
#include "../../Util/SoundManager.h"

PlayerState::PlayerState():
	m_isAction(false)
{
}

void PlayerState::Update(Input& input)
{
	// ��ԑJ��
	StateTransition(input);

	m_pNowState.stateUpdate();

	// �����A�����Ԃł͂Ȃ��Ƃ��̓T�E���h���~�߂�
	if (m_pNowState.stateKind != StateKind::Walk)
	{
		SoundManager::GetInstance().DesignationStopSound("Walk");
	}
	if (m_pNowState.stateKind != StateKind::Dash)
	{
		SoundManager::GetInstance().DesignationStopSound("Dash");
	}
}

void PlayerState::OnDamage()
{
	// ���݂̏�Ԃ��m�b�N�o�b�N�̎��͉��������ɏI������
	if (m_pNowState.stateKind == StateKind::KnockBack) return;

	// �m�b�N�o�b�N��ԂɑJ�ڂ���
	for (auto& changeState : m_pState)
	{
		// ��Ԃ��m�b�N�o�b�N�̎�
		if (changeState.stateKind == StateKind::KnockBack)
		{
			m_isAction = true;
			// ��ԕύX
			m_pNowState = changeState;
			// ��Ԃ̏�����
			m_pNowState.stateInit();
			return;
		}
	}
}

void PlayerState::StageClear()
{
	// ���݂̏�Ԃ��X�e�[�W�N���A�̎��͉��������ɏI������
	if (m_pNowState.stateKind == StateKind::StateClear) return;

	// �X�e�[�W�N���A��ԂɑJ�ڂ���
	for (auto& changeState : m_pState)
	{
		// ��Ԃ��X�e�[�W�N���A�̎�
		if (changeState.stateKind == StateKind::StateClear)
		{
			m_isAction = true;
			// ��ԕύX
			m_pNowState = changeState;
			// ��Ԃ̏�����
			m_pNowState.stateInit();
			return;
		}
	}
}

void PlayerState::AddState(std::function<void(void)> stateInit, std::function<void(void)> stateUpdate, StateKind stateKind)
{
	// ��Ԓǉ��p�̕ϐ��̐ݒ�
	StateData state;
	state.stateInit = stateInit;
	state.stateUpdate = stateUpdate;
	state.stateKind = stateKind;

	// ��Ԓǉ�
	m_pState.push_back(state);
}

void PlayerState::SetState(StateKind stateKind)
{
	for (auto& changeState : m_pState)
	{
		// ��Ԃ̎�ނ������̏�Ԃ̎�
		if (changeState.stateKind == stateKind)
		{
			// ��Ԃ̕ύX
			m_pNowState = changeState;
			return;
		}
	}
}

void PlayerState::EndState()
{
	// �A�N�V�����̏I��
	m_isAction = false;
}

void PlayerState::StateTransitionIdle(Input& input)
{
	// �A�N�V�������̏ꍇ�͉��������ɏI������
	if (m_isAction) return;

	// �ړ��{�^��������������Ă��Ȃ������ꍇ
	if (!Pad::isPress(PAD_INPUT_LEFT) && !Pad::isPress(PAD_INPUT_RIGHT) &&
		!Pad::isPress(PAD_INPUT_UP) && !Pad::isPress(PAD_INPUT_DOWN))
	{
		StateChange(StateKind::Idle);
	}
}

void PlayerState::StateTransitionWalk(Input& input)
{
	// �A�N�V�������̏ꍇ�͉��������ɏI������
	if (m_isAction) return;

	// �ړ��{�^�����������牟����Ă����ꍇ
	if (Pad::isPress(PAD_INPUT_LEFT) || Pad::isPress(PAD_INPUT_RIGHT) ||
		Pad::isPress(PAD_INPUT_UP) || Pad::isPress(PAD_INPUT_DOWN))
	{
		StateChange(StateKind::Walk);
	}
}

void PlayerState::StateTransitionDash(Input& input)
{
	// �A�N�V�������̏ꍇ�͉��������ɏI������
	if (m_isAction) return;

	//�ړ��{�^����������Ă��Ȃ������珈����Ԃ�
	if (!Pad::isPress(PAD_INPUT_LEFT) && !Pad::isPress(PAD_INPUT_RIGHT) &&
		!Pad::isPress(PAD_INPUT_UP) && !Pad::isPress(PAD_INPUT_DOWN)) return;

	// RB��������Ă�����_�b�V������
	if (Pad::isPress(PAD_INPUT_6))
	{
		StateChange(StateKind::Dash);
	}
}

void PlayerState::StateTransitionJump(Input& input)
{
	// �A�N�V�������̏ꍇ�͉��������ɏI������
	if (m_isAction) return;

	// A�{�^���������ꂽ��W�����v
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isAction = true;
		StateChange(StateKind::Jump);
	}
}

void PlayerState::StateTransition(Input& input)
{
	// ��ԑJ��
	StateTransitionIdle(input);
	StateTransitionWalk(input);
	StateTransitionDash(input);
	StateTransitionJump(input);
}

void PlayerState::StateChange(StateKind stateKind)
{
	for (auto& changeState : m_pState)
	{
		// ��Ԃ̎�ނ������̏�Ԃ̎�
		if (changeState.stateKind == stateKind)
		{
			// ��ԕύX
			m_pNowState = changeState;
			// ��Ԃ̏���������
			m_pNowState.stateInit();
			return;
		}
	}
}
