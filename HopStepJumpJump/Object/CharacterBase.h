#pragma once
#include "ObjectBase.h"

class Input;
class Circle;

class CharacterBase : public ObjectBase
{
public:

	// �X�e�[�^�X���
	struct Status
	{
		float spd = 5.0f;	// �X�s�[�h
	};

	// �ړ����
	struct MoveData
	{
		float walkSpeed = 0;	// �����X�s�[�h
		float runSpeed = 0;		// ����X�s�[�h
		float acceleration = 0;	// �����x
		float rotSpeed = 0;		// ��]�X�s�[�h
	};

	// �A�j���[�V�������
	struct AnimData
	{
		int8_t idle = 0;		// �ҋ@
		int8_t walk = 0;		// ����
		int8_t jumpStart = 0;	// �W�����v��
		int8_t jumpIdle = 0;	// �W�����v��
		int8_t run = 0;			// ����
		int8_t knockBack = 0;	// �m�b�N�o�b�N
	};

public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init();
	virtual void Update();

	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	/// <summary>
	/// �U�����󂯂����̏���
	/// </summary>
	/// <param name="targetPos">�U���𓖂Ă�����̍��W</param>
	virtual void OnDamage(VECTOR targetPos);

	/// <summary>
	/// �p�x�̎擾
	/// </summary>
	/// <returns>�p�x</returns>
	float GetAngle() const { return m_angle; }

	/// <summary>
	/// �_���[�W�t���O�̎擾
	/// </summary>
	/// <returns></returns>
	bool IsDamage()const { return m_isDamage; }

	/// <summary>
	/// �U�����󂯂ĂȂ���Ԃɖ߂�
	/// </summary>
	void OffDamageFlag() { m_isDamage = false; }

	/// <summary>
	/// �W�����v��Ԃ��ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsJump()const { return m_isJump; }

	/// <summary>
	/// �W�����v�͂�Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetJumpPower()const { return m_jumpPower; }

	/// <summary>
	/// ���񂾂��ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsDead()const { return m_isDead; }

	/// <summary>
	/// �~�̓����蔼�a�|�C���^�̎擾
	/// </summary>
	/// <returns></returns>
	const std::shared_ptr<Circle> GetCircle()const { return m_pCircle; }

	/// <summary>
	/// �L�����N�^�[���m�̓����蔻����l�������ړ��X�V
	/// </summary>
	/// <param name="pTarget"></param>
	void MoveCollCharacterUpdate(CharacterBase* pTarget);

	/// <summary>
	/// �v���C���[�̍U�����G�ɓ�������
	/// </summary>
	/// <param name="pEnemy"></param>
	void AttackPlayerCollEnemy(CharacterBase* pEnemy);

	/// <summary>
	/// �G�̍U�����v���C���[�ɓ�������
	/// </summary>
	/// <param name="pPlayer"></param>
	void AttackEnemyCollPlayer(CharacterBase* pPlayer);

	/// <summary>
	/// �v���C���[���A�C�e���ɓ�������
	/// </summary>
	/// <param name="pItem"></param>
	void PlayerToItem(CharacterBase* pItem);

	/// <summary>
	/// �W�����v��Ԃ̏I������
	/// </summary>
	virtual void EndJump();

	/// <summary>
	/// �n�ʂɓ������Ă���Ƃ��̏���
	/// </summary>
	void HitGroundUpdate();

	/// <summary>
	/// �d�͂ɂ�闎������
	/// </summary>
	void GravityUpdate();

protected:	// �֐�
	/// <summary>
	/// �p�x�����炩�ɕω�������֐�
	/// </summary>
	/// <param name="nowAngle"></param>
	/// <param name="nextAngle"></param>
	void SmoothAngle(float& nowAngle, float nextAngle);

protected:	// �ϐ�
	Status m_statusData;	// �X�e�[�^�X���
	MoveData m_moveData;	// �ړ����
	AnimData m_animData;	// �A�j���[�V�������

	std::shared_ptr<Circle> m_pCircle;	// �����蔻��̉~�̃|�C���^
	
	float m_jumpPower;	// �W�����v��
	bool m_isJump;	// �W�����v�����ǂ���
	bool m_isDead;	// ���񂾂��ǂ���
};

