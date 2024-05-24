#pragma once

class Input;
class Camera;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera);
	void Draw();
	void End();

	const VECTOR GetPos()const { return m_pos; }


private:	// �ϐ�
	VECTOR m_pos;			// ���W
	VECTOR m_targetDir;		// �����Ă�������̃x�N�g��
	float m_angle;			// �����Ă���p�x
	float m_currentJunpPower;		// �W�����v����ۂ̑��x
	int m_modelHandle;		// ���f���̃n���h��
	


private:	// �萔
	static constexpr float kSpeed = 30.0f;			// �ړ����x
	static constexpr float kJunpPower = 100.0f;		// �W�����v��
	static constexpr float kGravity = 3.0f;			// �d��

private:	// �֐�
	
	/// <summary>
	/// ��]����
	/// </summary>
	void UpdateAngle();

};

