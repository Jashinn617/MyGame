#pragma once
#include "DxLib.h"

#include <vector>
#include <memory>
#include <functional>

class Stamina;
class Time;
class Input;

class PlayerState
{
public:
	// ���
	enum class StateKind
	{
		Idle,		// �ҋ@
		Walk,		// ����
		Dash,		// ����
		Jump,		// �W�����v
		KnockBack,	// �m�b�N�o�b�N
		StateClear,	// �X�e�[�W�N���A
	};

public:
	PlayerState();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerState() {};

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Input& input);

	/// <summary>
	/// �_���[�W���󂯂�
	/// </summary>
	void OnDamage();

	/// <summary>
	/// �X�e�[�W�N���A
	/// </summary>
	void StageClear();

	/// <summary>
	/// ��ԏ��̒ǉ�
	/// </summary>
	/// <param name="stateInit">������</param>
	/// <param name="stateUpdate">�X�V</param>
	/// <param name="stateKind">��Ԃ̎��</param>
	void AddState(std::function<void(void)> stateInit, 
		std::function<void(void)> stateUpdate, 
		StateKind stateKind);

	/// <summary>
	/// ��Ԃ̐ݒ�
	/// </summary>
	/// <param name="state">���</param>
	void SetState(StateKind stateKind);

	/// <summary>
	/// ��Ԃ̏I������
	/// </summary>
	void EndState();

	/// <summary>
	/// ���݂̏�Ԃ̎擾
	/// </summary>
	/// <returns></returns>
	StateKind GetState() const { return m_pNowState.stateKind; }

private:	// �\����

	// ��ԏ��
	struct StateData
	{
		std::function<void(void)> stateInit{};		// ��ԏ���������
		std::function<void(void)> stateUpdate{};	// ��ԍX�V����
		StateKind stateKind{};						// ��Ԃ̎��
	};

private:	// �֐�
	/// <summary>
	/// �ҋ@��Ԃւ̕ύX
	/// </summary>
	void StateTransitionIdle(Input& input);
	/// <summary>
	/// ������Ԃւ̕ύX
	/// </summary>
	void StateTransitionWalk(Input& input);
	/// <summary>
	/// �_�b�V����Ԃւ̕ύX
	/// </summary>
	void StateTransitionDash(Input& input);
	/// <summary>
	/// �W�����v��Ԃւ̕ύX
	/// </summary>
	void StateTransitionJump(Input& input);

	/// <summary>
	/// �e��ԑJ��
	/// </summary>
	void StateTransition(Input& input);

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="state">���</param>
	void StateChange(StateKind stateKind);

private:	// �ϐ�
	bool m_isAction;						// �A�N�V�����s������
	std::vector<StateData> m_pState;		// ��Ԃ̊i�[
	StateData m_pNowState;					// ���݂̏��
};

