#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

class Player;
class ObjectBase;
class Model;
class Circle;
class Time;
class Input;

class ItemBase : public CharacterBase
{
public:
	ItemBase();
	ItemBase(VECTOR pos);
	virtual ~ItemBase();

	virtual void Init();
	virtual void Update(Input& input) override;

	virtual void Draw();
	virtual void Draw2D() override;

	// ���݂��邩�ǂ���
	bool GetExist()const { return m_info.isExist; }

	// �Q�b�g���ꂽ�Ƃ�
	void OnGet();

	// ���g�̓����蔻��̏��
	virtual ColType GetColType()const { return ColType::Item; }

	// �X�e�[�W�N���A����
	void StageClear() override final;

protected:
	// �ړ����x�̏�����
	void InitMoveSpeed(float moveSpeed);

	// �p�x�̍X�V
	virtual void AngleUpdate();
	// �ړ������̍X�V
	virtual void MoveDirectionUpdate();
	// �ړ������Ɗp�x���l�������ړ��̍X�V
	VECTOR MoveUpdate();

	/*�����o�֐��|�C���^*/
	// ��ԍX�V
	virtual void StateTransitionUpdate();

	// �ړ���Ԃւ̕ύX
	virtual bool StateTransitionMove();
	// �u�]��ԂɕύX
	virtual bool StateTransitionDead();
	// �ҋ@���
	virtual void IdleStateUpdate();
	// �ړ����
	virtual void MoveStateUpdate();
	// ���S���
	virtual void DeadStateUpdate();


protected:	// �ϐ�
	VECTOR m_moveDirectionVec;	// �ړ������x�N�g��
	int m_createTime;		// ��������Ă��痧��������
	void(ItemBase::* m_updateFunc)();	// �����o�֐��|�C���^
	std::shared_ptr<Time> m_deadTime;	// ����ł���̎���
	float m_colHeight;	// �����蔻��̍����𒆐S�ɂ���ϐ�



};