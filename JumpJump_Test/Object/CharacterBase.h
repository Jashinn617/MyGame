#pragma once
#include "ObjectBase.h"
class CharacterBase : public ObjectBase
{
public:

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
		int8_t run = 0;			// ����
		int8_t jumpStart = 0;	// �W�����v��
		int8_t jumpIdle = 0;	// �W�����v��
		int8_t knockBack = 0;	// �m�b�N�o�b�N
	};

public:


protected:	// �֐�

protected:	// �ϐ�
	MoveData m_moveData;	// �ړ����
	AnimData m_animData;	// �A�j���[�V�������

	

};

