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
		Walk = 1,		// ����
		Run = 2,		// ����
		Jump = 3,		// �W�����v
	};

	// �A�j���[�V�������
	enum class AnimKind :int
	{
		None = -1,		// ����
		Unknown = 0,	// �s��
		Walk = 10,		// ����
		Run = 6,		// ����
		Jump = 3,		// �W�����v
		Idle = 2,		// �����~�܂�
	};

public:
	Player();
	~Player();

	/// <summary>
	/// ����������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="camera">�J����</param>
	/// <param name="stage">���݂̏��</param>
	void Update(const Input& input, const Camera& camera, StageTest& stage);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns>���݈ʒu</returns>
	const VECTOR& GetPos()const { return m_pos; }

	/// <summary>
	/// ���݈ړ������̎擾
	/// </summary>
	/// <returns>���݈ړ�����</returns>
	bool GetIsMove() const { return m_isMove; }

	/// <summary>
	/// ��Ԃ̎擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	State GetState()const { return m_currentState; }

	/// <summary>
	/// �W�����v�̍����̎擾
	/// </summary>
	/// <returns>�W�����v�̍���</returns>
	float GetJumpPower()const { return m_nowJunpPower; }

	/// <summary>
	/// �V��ɓ����������̏���
	/// </summary>
	void OnHitRoof();

	/// <summary>
	/// ���ɓ����������̏���
	/// </summary>
	void OnHitFloor();

	/// <summary>
	/// ��������
	/// </summary>
	void OnFall();

private:	// �֐�

	/// <summary>
	/// ���[�g�t���[����Z�������̈ړ��p�����[�^�𖳌��ɂ���
	/// �A�j���[�V������A�����蔻��ɕs����N���Ȃ��悤�ɂ��邽�߂Ɏg�p����
	/// </summary>
	void DisableRootFrameZMove();

	/// <summary>
	/// ���͂ɂ��p�����[�^��ݒ肷��
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="camera">�J����</param>
	/// <param name="upMoveVec">������̈ړ��x�N�g��</param>
	/// <param name="leftMoveVec">�������̈ړ��x�N�g��</param>
	/// <param name="moveVec">�ړ��x�N�g��</param>
	/// <returns>���݂̏��</returns>
	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	/// <summary>
	/// �ړ�
	/// </summary>
	/// <param name="moveVec">�ړ��x�N�g��</param>
	/// <param name="stage">���݂̏��</param>
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
	/// �A�j���[�V�����̍X�V
	/// </summary>
	/// <param name="attachNo">���݂̃A�j���[�V�����ԍ�</param>
	/// <returns>���[�v���Ă��邩�ǂ���</returns>
	bool LoopAnim(int attachNo);

	/// <summary>
	/// �A�j���[�V�����̓���ւ�
	/// </summary>
	/// <param name="animIndex">����ւ���A�j���[�V�����̔ԍ�</param>
	void ChangeAnim(int animIndex);



private:	// �ϐ�
	VECTOR m_pos;					// ���W
	VECTOR m_targetDir;				// �������������̃x�N�g��
	float m_angle;					// �����Ă���p�x
	float m_nowJunpPower;			// �W�����v���̌��݂̑��x
	int m_modelHandle;				// ���f���̃n���h��
	int m_ps;
	int m_vs;

	State m_currentState;				// ���݂̏��

	int m_currentAnimNo;			// ���Đ����Ă���A�j���[�V�����̔ԍ�
	int m_prevAnimNo;				// �O�̍Đ��A�j���[�V�����̔ԍ�
	float m_nowAnimCount;			// �Đ����Ă���A�j���[�V�����̍Đ�����
	float m_prevAnimCount;			// �O�̍Đ��A�j���[�V�����̍Đ�����
	float m_animBlendRate;			// �O�ƍ��̃A�j���[�V�����̃u�����h��

	bool m_isMove;					// ���̃t���[���œ��������ǂ���
};

