#pragma once
#include "DxLib.h"
#include "../CharacterBase.h"

#include <memory>

class Time;

class EnemyBase :public CharacterBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyBase();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="speed">�X�s�[�h</param>
	EnemyBase(VECTOR pos, float speed);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="direction">��������</param>
	/// <param name="turnTime">���]����܂ł̎���</param>
	/// <param name="speed">�ړ��X�s�[�h</param>
	EnemyBase(VECTOR pos, VECTOR direction, int turnTime, float speed);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyBase();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pToonShader"></param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	/// <summary>
	/// �X�e�[�W�N���A����
	/// </summary>
	void StageClear() override final;

	/// <summary>
	/// �Q�[���I��������
	/// </summary>
	void GameEnd() override final;

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="targetPos">�U������̍��W</param>
	void OnDamage(VECTOR targetPos) override;

	/// <summary>
	/// ���S����
	/// </summary>
	void  OnDead();

	/// <summary>
	/// ���݂��邩�ǂ���
	/// </summary>
	/// <returns>���݃t���O</returns>
	bool IsExist()const { return m_info.isExist; }

	/// <summary>
	/// �G����v���C���[�܂ł̃x�N�g���̎擾
	/// </summary>
	/// <returns>�v���C���[�܂ł̃x�N�g��</returns>
	VECTOR GetEnemyToPlayerVec()const { return m_enemyToPlayerVec; }

	/// <summary>
	/// ���g�̓����蔻��̏��̎擾
	/// </summary>
	/// <returns>�����蔻����</returns>
	virtual ColType GetColType()const { return ColType::Enemy; }

protected:	// �֐�
	/// <summary>
	/// �ړ����x�̏�����
	/// </summary>
	/// <param name="moveSpeed"></param>
	void InitMoveSpeed(float moveSpeed);

	/// <summary>
	/// �p�x�̍X�V
	/// </summary>
	void AngleUpdate();

	/// <summary>
	/// �ړ������̍X�V
	/// </summary>
	virtual void MoveDirectionUpdate();

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <returns></returns>
	virtual VECTOR MoveUpdate();

protected:	// �ϐ�
	VECTOR m_moveDirectionVec;				// �ړ������x�N�g��
	VECTOR m_enemyToPlayerVec;				// �G����v���C���[�܂ł̃x�N�g��
	std::shared_ptr<Time> m_turnTime;		// �^�[������܂ł̎���
	std::shared_ptr<Time> m_deadTime;		// ����ł���̎���
	std::shared_ptr<Time> m_endTime;		// �Q�[���I�����Ă���̎���
	std::shared_ptr<Time> m_endDeadTime;	// �Q�[���I����ɏ����Ă���̎���

private:	// �ϐ�
	float m_colHeight;						// �����蔻��̍��������f���̒��S�ɂ���
	bool m_isEndDead;						// �Q�[���I����ɏ��������ǂ���
	bool m_isEnd;							// �Q�[���I���������ǂ���
};
