#pragma once
#include "DxLib.h"

// �L�����N�^�[�̎����Ă�����
namespace CharacterData
{
	// �L�����N�^�[���
	struct CharacterInfo
	{
		VECTOR pos;		// ���W
		VECTOR vec;		// �ړ��x�N�g��
		VECTOR rot;		// ��]	
		int modelH;		// ���f���n���h��
		int isExist;	// ���݂��Ă��邩�ǂ���
	};
}
