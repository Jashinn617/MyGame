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

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�n���h��</param>
	void Init(HandleManager& handle);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	/// <param name="isOperate">���삪�ł��邩�ǂ���</param>
	void Update(Input& input, HandleManager& handle, bool isOperate);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="handleManager">�n���h��</param>
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

	/// <summary>
	/// �J�����̊p�x��ݒ肷��
	/// </summary>
	/// <param name="angle">�J�����̃A���O��</param>
	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

private:	// �֐�
	/// <summary>
	/// �R���g���[���[�ł̈ړ�����
	/// </summary>
	/// <param name="input">����</param>
	void Move(Input& input);

	/// <summary>
	/// �W�����v����
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="handle">�n���h��</param>
	void Jump(Input& input, HandleManager& handle);

	/// <summary>
	/// �d�͂ƒn�ʂɊւ��鏈��
	/// </summary>
	void GravityAndGround();

	/// <summary>
	/// �ǂ̓����蔻��Ɋւ��鏈��
	/// </summary>
	void Wall();

private:	// �ϐ�
	VECTOR m_pos;			// �ʒu
	float m_dir;			// Y�����̌���
	float m_jumpPower;		// �W�����v��
	bool m_isJump;			// �W�����v�����ǂ���
	float m_cameraAngle;	// �J�������

private:	// �萔
	static constexpr float kMaxSpeed = 400.0f;							// ���x
	static constexpr float kScale = 0.002f;								// �g�嗦
	static constexpr float kRadius = 0.5f;								// ���a
	static constexpr float kStartModelDir = (DX_PI_F / 180.0f) * 90;	// ���f���̏�����Y������
	static constexpr float kGravity = 0.025f;							// �d��
	static constexpr float kJumpPower = 0.35f;							// �W�����v��
	static constexpr float kGroundPosY = 0.4f;							// �n�ʂ�Y�ʒu
	static constexpr float kWallZ = 30;									// z���̕�
	static constexpr float kWallX = 50;									// x���̕�
	static constexpr float kAnalogRangeMax = 0.8f;						// �A�i���O�X�e�B�b�N�̗L���͈͂̍ő�l
	static constexpr float kAnalogRangeMim = 0.1f;						// �A�i���O�X�e�B�b�N�̗L���͈͂̍ŏ��l
	static constexpr float kAnalogInputMax = 1000.0f;					// �A�i���O�X�e�B�b�N�̍ő���͔͈�
};