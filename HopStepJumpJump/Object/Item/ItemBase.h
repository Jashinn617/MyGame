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

	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	// ���݂��邩�ǂ���
	bool GetExist()const { return m_info.isExist; }

	// �Q�b�g���ꂽ�Ƃ�
	void OnGet();

	// ���g�̓����蔻��̏��
	virtual ColType GetColType()const { return ColType::Item; }

	/// <summary>
	/// �Q�[���I��������
	/// </summary>
	void GameEnd() override final;

protected:
	// �ړ����x�̏�����
	void InitMoveSpeed(float moveSpeed);

	// �ړ������̍X�V
	virtual void MoveDirectionUpdate();
	// �ړ������Ɗp�x���l�������ړ��̍X�V
	virtual VECTOR MoveUpdate();



protected:	// �ϐ�
	float m_colHeight;					// �����蔻��̍��������f���̒��S�ɂ���
	VECTOR m_moveDirectionVec;			// �ړ������x�N�g��
	int m_createTime;					// ��������Ă��痧��������
	std::shared_ptr<Time> m_deadTime;	// ����ł���̎���
};