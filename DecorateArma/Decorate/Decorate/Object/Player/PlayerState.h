#pragma once
#include "DxLib.h"

class PlayerState
{
public:	// �񋓌^

	/// <summary>
	/// �X�e�C�g�̎��
	/// </summary>
	enum class StateKind
	{
		Idle,	// �ҋ@
		Walk,	// ����
		Dash,	// �_�b�V��
		Jump,	// �W�����v
		Damage,	// �_���[�W
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerState();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerState();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �_���[�W����
	/// </summary>
	void OnDamage();

	/// <summary>
	/// �X�e�C�g�̐ݒ�
	/// </summary>
	/// <param name="stateKind"></param>
	void SetState(StateKind stateKind);

	/// <summary>
	/// �X�e�C�g�̏I������
	/// </summary>
	void EndState();

	StateKind GetState()const { return m_nowState; }

private:	// �֐�
	/// <summary>
	/// �ҋ@��Ԃւ̕ύX
	/// </summary>
	void StateTransitionIdle();

	/// <summary>
	/// ������Ԃւ̕ύX
	/// </summary>
	void StateTransitionWalk();

	/// <summary>
	/// �_�b�V����Ԃւ̕ύX
	/// </summary>
	void StateTransitionDash();

	/// <summary>
	/// �W�����v��Ԃւ̕ύX
	/// </summary>
	void StateTransitionJump();

	/// <summary>
	/// �e�X�e�C�g�̑J��
	/// </summary>
	void StateTransition();

	/// <summary>
	/// �X�e�C�g�ύX
	/// </summary>
	/// <param name="state">�X�e�C�g</param>
	void StateChange(StateKind stateKind);

private:	// �ϐ�
	bool m_isAction;		// �A�N�V�����s������
	StateKind m_nowState;	// ���݂̃X�e�C�g
};