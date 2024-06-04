#pragma once

class Input;
class Camera;
class StageTest;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	// ���
	enum class State : int
	{
		Idle = 0,		// �����~�܂�
		Run = 1,		// ����
		Jump = 2,		// �W�����v
	};

	// �A�j���[�V�������
	enum class AnimKind :int
	{
		None = -1,		// ����
		Unknown = 0,	// �s��
		Run = 7,		// ����
		Jump = 12,		// �W�����v
		Fall = 13,		// ������
		Stop = 1,		// �����~�܂�
	};

public:
	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, StageTest& stage);
	void Draw();
	void End();

	const VECTOR& GetPos()const { return m_pos; }
	bool GetIsMove() const { return m_isMove; }
	State GetState()const { return m_state; }
	float GetJumpPower()const { return m_nowJunpPower; }

	void OnHitRoof();
	void OnHitFloor();
	void OnFall();

private:	// �֐�

	void DisableRootFrameZMove();

	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	void Move(const VECTOR& moveVec, StageTest& stage);
	
	/// <summary>
	/// ��]����
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// �A�j���[�V�����X�e�[�g�̍X�V
	/// </summary>
	/// <param name="prevState"></param>
	void UpdateAnimationState(State prevState);

	/// <summary>
	/// �V�����A�j���[�V�����̍Đ�
	/// </summary>
	/// <param name="playAnim"></param>
	void PlayAnimation(AnimKind nextPlayAnim);

	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="playAnim"></param>
	void UpdateAnimation();



private:	// �ϐ�
	VECTOR m_pos;				// ���W
	VECTOR m_targetDir;			// �������������̃x�N�g��
	float m_angle;				// �����Ă���p�x
	float m_nowJunpPower;		// �W�����v���̌��݂̑��x
	int m_modelHandle;			// ���f���̃n���h��
	State m_state;				// ���݂̏��

	int m_nowPlayAnim;				// ���Đ����Ă���A�j���[�V�����̔ԍ�
	int m_prevPlayAnim;				// �O�̍Đ��A�j���[�V�����̔ԍ�
	float m_nowAnimCount;			// �Đ����Ă���A�j���[�V�����̍Đ�����
	float m_prevAnimCount;			// �O�̍Đ��A�j���[�V�����̍Đ�����
	float m_animBlendRate;			// �O�ƍ��̃A�j���[�V�����̃u�����h��

	bool m_isMove;		// ���̃t���[���œ��������ǂ���
	
};

