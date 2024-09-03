#pragma once
#include "Context.h"

#include <functional>

class State
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stateUpdate"></param>
	/// <param name="stateData"></param>
	State(std::function<void(void)> stateUpdate, Context::StateData state);

	void Update();

	Context::StateData GetStateData() const { return m_stateKind; }

private:
	std::function<void(void)> m_stateUpdate;	// �X�V����
	Context::StateData m_stateKind;				// ��Ԃ̎��
};

