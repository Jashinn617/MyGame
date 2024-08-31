#include "Context.h"
#include "State.h"

Context::Context(std::function<void(void)> changeState):
	m_pNowState(nullptr),
	m_changeState(changeState)
{
}

void Context::Update()
{
	m_pNowState->Update();
}

void Context::AddState(std::function<void(void)> listener, Context::StateData state)
{
	// �X�e�C�g��ǉ�����
	m_pState.push_back(std::make_shared<State>(listener, state));
}

void Context::ChangeState(StateData stateData)
{
	// �X�e�C�g���ЂƂ��Ȃ��ꍇ�擪�̃X�e�C�g��Ԃɂ�(Idle)�������I������
	if (m_pNowState == nullptr)
	{
		m_pNowState = m_pState.front();
		return;
	}
	// ���݂̏�ԂƕύX�����Ԃ������ꍇ�������I������
	if (m_pNowState->GetStateData() == stateData) return;

	// �X�e�C�g��ύX����
	for (auto& state : m_pState)
	{
		// �ύX����X�e�C�g���������珈�����I������
		if (state->GetStateData() == stateData)
		{
			m_changeState();
			m_pNowState = state;
			return;
		}
	}
}

Context::StateData Context::GetState() const
{
	// ���݂̃X�e�C�g��Ԃ�
	return m_pNowState->GetStateData();
}
