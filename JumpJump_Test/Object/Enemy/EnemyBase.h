#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

#include <memory>

class Input;

class Player;
class ObjectBase;
class Model;
class Circle;
class Time;

class EnemyBase :public CharacterBase
{
public:
	// �G�̃^�C�v
	enum class EnemyType
	{
		Bee,
		Crab,
		Ogre,
		Skull
	};

public:
	EnemyBase();
	EnemyBase(VECTOR pos);
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update(Input& input) override;

	virtual void Draw();
	virtual void Draw2D()override;

	/// <summary>
	/// �X�e�[�W�N���A����
	/// </summary>
	void StageClear() override final;

	void OnDamage(VECTOR targetPos) override;

	/// <summary>
	/// �W�����v�̏I������
	/// </summary>
	virtual void EndJump();

	/// <summary>
	/// ���݂��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsExist()const { return m_info.isExist; }

	/// <summary>
	/// �G����v���C���[�܂ł̃x�N�g���̎擾
	/// </summary>
	/// <returns></returns>
	VECTOR GetEnemyToPlayerVec()const { return m_enemyToPlayerVec; }

	/// <summary>
	/// ���g�̓����蔻��̏��
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType()const { return ColType::Enemy; }

	/// <summary>
	/// /�G�l�~�[�̎��
	/// </summary>
	/// <returns></returns>
	virtual EnemyType GetEnemyType()const { return EnemyType::Bee; }	

protected:	// �֐�
	/// <summary>
	/// �ړ����x�̏�����
	/// </summary>
	/// <param name="moveSpeed"></param>
	void InitMoveSpeed(float moveSpeed);

	/// <summary>
	/// �p�x�̍X�V
	/// </summary>
	virtual void AngleUpdate();

	/// <summary>
	/// �ړ������̍X�V
	/// </summary>
	virtual void MoveDirectionUpdate();

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate();

	virtual void StateTransitionUpdate();		// ��ԍX�V

	virtual bool TransitionMove();		// �ړ���ԂɑJ�ڂ��邩�ǂ���
	virtual bool TransitionKnockBack();	// �m�b�N�o�b�N��ԂɑJ�ڂ��邩�ǂ���
	virtual bool TransitionDead();		// ���S��ԂɑJ�ڂ��邩�ǂ���

	virtual void IdleStateUpdate();		// �ҋ@��Ԃ̍X�V
	virtual void MoveStateUpdate();		// �ړ���Ԃ̍X�V
	virtual void KnockBackStateUpdate();	// �m�b�N�o�b�N��Ԃ̍X�V
	virtual void DeadStateUpdate();		// ���S��Ԃ̍X�V


protected:	// �ϐ�
	int m_createTime;		// ��������Ă��痧��������
	float m_colHeight;	// �����蔻��̍��������f���̒��S�ɂ���
	VECTOR m_enemyToPlayerVec;	// �G����v���C���[�܂ł̃x�N�g��
	VECTOR m_moveDirectionVec;	// �ړ������x�N�g��
	void (EnemyBase::* m_updateFunc)();	// �����o�֐��|�C���^
	std::shared_ptr<Time> m_deadTime;	// ����ł���̎���
};
