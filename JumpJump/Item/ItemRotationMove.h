#pragma once
#include "ItemBase.h"

/// <summary>
/// �~�������悤�Ɉړ�����A�C�e��
/// </summary>
class ItemRotationMove : public ItemBase
{
public:		// �֐�
	ItemRotationMove(int modelHandle);
	virtual ~ItemRotationMove();

	virtual void Init();
	virtual void Update();

private:	// �ϐ�
	float m_centerX;	// �~�̒��S��X�ʒu
	float m_centerZ;	// �~�̒��S��Z�ʒu
};

