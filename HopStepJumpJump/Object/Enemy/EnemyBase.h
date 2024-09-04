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
	EnemyBase();
	EnemyBase(VECTOR pos, float speed);
	EnemyBase(VECTOR pos, VECTOR direction, int turnTime, float speed);
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update(Input& input) override;

	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	/// <summary>
	/// �X�e�[�W�N���A����
	/// </summary>
	void StageClear() override final;

	/// <summary>
	/// �Q�[���I��������
	/// </summary>
	void GameEnd() override final;

	void OnDamage(VECTOR targetPos) override;

	void  OnDead();

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
	float m_colHeight;			// �����蔻��̍��������f���̒��S�ɂ���
	bool m_isEnd;				// �Q�[���I���������ǂ���
	bool m_isEndDead;			// �Q�[���I����ɏ��������ǂ���
	VECTOR m_moveDirectionVec;	// �ړ������x�N�g��
	VECTOR m_enemyToPlayerVec;	// �G����v���C���[�܂ł̃x�N�g��
	std::shared_ptr<Time> m_turnTime;	// �^�[������܂ł̎���
	std::shared_ptr<Time> m_deadTime;	// ����ł���̎���
	std::shared_ptr<Time> m_endTime;	// �Q�[���I�����Ă���̎���
	std::shared_ptr<Time> m_endDeadTime;	// �Q�[���I����ɏ����Ă���̎���
};
