#pragma once
#include "ItemBase.h"

/// <summary>
/// �㉺�ړ������Ȃ����]����A�C�e��
/// </summary>
class ItemNotMove : public ItemBase
{
public:		// �֐�
	ItemNotMove(int modelHandle);
	virtual ~ItemNotMove();

	virtual void Init();
	virtual void Update();

private:	// �ϐ�
	float m_angleX;			// X���̊p�x
	float m_moveSinCount;	// �ړ��̃J�E���g
	float m_posY;			// Y�ʒu
};

