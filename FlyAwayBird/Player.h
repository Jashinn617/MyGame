#pragma once

class Input;
class HandleManager;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update(Input& input, HandleManager& handle);
	void Draw(HandleManager& handleManager)const;

	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns>���݈ʒu</returns>
	const VECTOR GetPos()const { return m_pos; }

	/// <summary>
	/// ���a�̎擾
	/// </summary>
	/// <returns>���a</returns>
	const float GetRadius()const { return kRadius; }

private:	// �֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="input">����</param>
	void Move(Input& input);

	/// <summary>
	/// �W�����v����
	/// </summary>
	/// <param name="input">����</param>
	void Jump(Input& input);

	/// <summary>
	/// �d�͂ƒn�ʂɊւ��鏈��
	/// </summary>
	void GravityAndGround();

	/// <summary>
	/// �ǂɊւ��鏈��
	/// </summary>
	void Wall();

private:	// �ϐ�
	VECTOR m_pos;	// �ʒu
	VECTOR m_move;	// �ړ���
	float m_dirY;	// Y�����̌���

	float m_jumpPower;	// �W�����v��
	bool m_isJump;		// �W�����v�����ǂ���

private:	// �萔
	static constexpr float kSpeed = 0.3f;			// ���x
	static constexpr float kScale = 0.002f;			// �g�嗦
	static constexpr float kRadius = 0.5f;			// ���a
	static constexpr float kGravity = 0.025f;		// �d��
	static constexpr float kJumpPower = 0.35f;		// �W�����v��
	static constexpr float kGroundPosY = 0.4f;		// �n�ʂ�Y�ʒu
	static constexpr float kWallZ = 30;				// z���̕�
	static constexpr float kWallX = 50;				// x���̕�
	static constexpr int kSeVolume = 255;			// SE�̉���
};