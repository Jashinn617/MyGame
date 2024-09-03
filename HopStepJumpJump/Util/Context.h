#pragma once
#include <vector>
#include <memory>
#include <functional>

class State;

class Context
{
public:
	// �X�e�C�g�̎�ޏ��
	enum class StateData
	{
		Idle,		// �ҋ@
		Walk,		// ����
		Jump,		// �W�����v
		Dash,		// �_�b�V��
		KnockBack,	// �m�b�N�o�b�N
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="changeState">�X�e�C�g�֐�</param>
	Context(std::function<void(void)> changeState);

	void Update();

	/// <summary>
	/// �X�e�C�g�̒ǉ�
	/// </summary>
	/// <param name="listener">�X�e�C�g�̊֐�</param>
	/// <param name="state">�X�e�C�g�̎��</param>
	void AddState(std::function<void(void)> listener, Context::StateData stateData);

	/// <summary>
	/// �X�e�C�g�ύX
	/// </summary>
	/// <param name="state">�ύX��̃X�e�C�g</param>
	void ChangeState(StateData state);

	/// <summary>
	/// ���݂̃X�e�C�g��Ԃ�
	/// </summary>
	/// <returns></returns>
	StateData GetState() const;

private:
	std::vector<std::shared_ptr<State>> m_pState;	// �S�ẴX�e�C�g
	std::shared_ptr<State> m_pNowState;				// ���݂̃X�e�C�g
	std::function<void(void)> m_changeState;		// �X�e�C�g�ύX���̏����֐�
};

