#pragma once
#include "DxLib.h"

/// <summary>
/// �L�����N�^�[�̎����Ă�����
/// </summary>
namespace CharacterData
{
	/// <summary>
	/// �L�����N�^�[���
	/// </summary>
	struct CharacterInfo
	{
		VECTOR pos;		// ���W
		VECTOR vec;		// �ړ��x�N�g��
		VECTOR rot;		// ��]
		int modelH;		// ���f���n���h��
		int isExist;	// ���݂��Ă��邩�ǂ���
	};
}