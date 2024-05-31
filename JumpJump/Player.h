#pragma once

class Input;
class Camera;
class Stage;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	enum class State : int
	{
		Idle = 0,
		Run = 1,
		Jump = 2,
	};

public:
	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera);
	void Draw();
	void End();

	const VECTOR& GetPos()const { return m_pos; }
	bool GetIsMove() const { return m_isMove; }
	State GetState()const { return m_state; }
	float GetJumpPower()const { return m_nowJunpPower; }

	void OnHitRoof();
	void OnHitFloor();
	void OnFall();


private:	// �ϐ�
	VECTOR m_pos;			// ���W
	VECTOR m_targetDir;		// �������������̃x�N�g��
	float m_angle;			// �����Ă���p�x
	float m_nowJunpPower;		// �W�����v���̌��݂̑��x
	int m_modelHandle;		// ���f���̃n���h��

	State m_state;		// ���݂̏��


	bool m_isMove;		// ���̃t���[���œ��������ǂ���
	


private:	// �萔
	static constexpr float kMoveSpeed = 1.0f;		// �ړ����x
	static constexpr float kAngleSpeed = 0.2f;		// ��]���x
	static constexpr float kJunpPower = 3.0f;		// �W�����v��
	static constexpr float kFallUpPower = 0.6f;		// ���𓥂݊O�����Ƃ��̃W�����v��
	static constexpr float kGravity = 3.0f;			// �d��

private:	// �֐�

	void DisableRootFrameZMove();

	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	void Move(const VECTOR& moveVec);
	
	/// <summary>
	/// ��]����
	/// </summary>
	void UpdateAngle();

};

