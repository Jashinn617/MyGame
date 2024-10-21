#pragma once
#include "ObjectBase.h"

class Sphere;
class Capsule;

/// <summary>
/// �I�u�W�F�N�g�̒��ł��L�����N�^�[�̊��N���X
/// </summary>
class CharacterBase : public ObjectBase
{
public:	// �\����

	/// <summary>
	/// �X�e�[�^�X���
	/// </summary>
	struct StatusData
	{
		float spd = 0.0f;	// ���x
	};

	/// <summary>
	/// �ړ��X�e�[�^�X���
	/// </summary>
	struct MoveStatusData
	{
		float walkSpeed = 0.0f;		// �������x
		float dashSpeed = 0.0f;		// ���葬�x
		float acc = 0.0f;	// �����x
		float rotSpeed = 0.0f;		// ��]���x
	};

	/// <summary>
	/// �A�j���[�V�������
	/// </summary>
	struct AnimData
	{
		int8_t idle = 0;		// �ҋ@
		int8_t walk = 0;		// ����
		int8_t run = 0;			// ����
		int8_t jumpStart = 0;	// �W�����v�n��
		int8_t jumpIdle = 0;	// �W�����v��
		int8_t damage = 0;		// �_���[�W
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CharacterBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CharacterBase();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() override = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() override = 0;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pToonShader">�g�D�[���V�F�[�_�|�C���^</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader)override = 0;

	/// <summary>
	/// �W�����v�I������
	/// </summary>
	virtual void EndJump();

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="targetPos">�U���𓖂Ă�����̍��W</param>
	virtual void OnDamage(VECTOR targetPos) {/*��������*/ }

	/// <summary>
	/// �L�����N�^�[���m�̓����蔻����l�������ړ�����
	/// </summary>
	/// <param name="pTarget">����̃L�����N�^�[�|�C���^</param>
	void MoveCollCharacter(CharacterBase* pTarget);

	/// <summary>
	/// �n�ʂɓ������Ă���Ƃ��̏���
	/// </summary>
	void HitGround();

	/// <summary>
	/// �d�͂ɂ�闎������
	/// </summary>
	void UpdateGravity();

	/// <summary>
	/// ���̓����蔻��|�C���^�̎擾
	/// </summary>
	/// <returns>���̓����蔻��|�C���^</returns>
	const std::shared_ptr<Sphere> GetSphere()const { return m_pSphere; }

	/// <summary>
	/// �p�x�̍X�V
	/// </summary>
	/// <returns>�p�x</returns>
	float GetAngle() const { return m_angle; }

	/// <summary>
	/// �W�����v�����ǂ�����Ԃ�
	/// </summary>
	/// <returns>�W�����v�����ǂ���</returns>
	bool IsJump()const { return m_isJump; }

	/// <summary>
	/// �W�����v�͂�Ԃ�
	/// </summary>
	/// <returns>�W�����v��</returns>
	float GetJumpPower()const { return m_jumpPower; }

	/// <summary>
	/// �W�����v�͂𔽓]����
	/// </summary>
	void InvertJumpPower() { m_jumpPower *= -1; }

	/// <summary>
	/// �_���[�W���󂯂����ǂ�����Ԃ�
	/// </summary>
	/// <returns>�_���[�W���󂯂����ǂ���</returns>
	bool IsDamage()const { return m_isDamage; }

	/// <summary>
	/// �U�����󂯂Ă��Ȃ���Ԃɖ߂�
	/// </summary>
	void OffDamage() { m_isDamage = false; }

	/// <summary>
	/// ���S��Ԃ��ǂ�����Ԃ�
	/// </summary>
	/// <returns>���S��Ԃ��ǂ���</returns>
	bool IsDead()const { return m_isDead; }

protected:	// �֐�
	/// <summary>
	/// �p�x�����炩�ɕω�������֐�
	/// </summary>
	/// <param name="nowAngle">���݂̊p�x</param>
	/// <param name="nextAngle">�ڕW�p�x</param>
	void SmoothAngle(float& nowAngle, float nextAngle);

protected:	// �ϐ�
	float m_jumpPower;						// �W�����v��
	bool m_isJump;							// �W�����v�����ǂ���
	bool m_isDead;							// ���񂾂��ǂ���
	std::shared_ptr<Sphere> m_pSphere;		// �����蔻��p�̋��̃|�C���^
	std::shared_ptr<Capsule> m_pCapsule;	// �����蔻��p�̃J�v�Z���̃|�C���^

	StatusData m_statusData{};			// �X�e�[�^�X���
	MoveStatusData m_moveData{};		// �ړ����
	AnimData m_animData{};				// �A�j���[�V�������
};