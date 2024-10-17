#pragma once

#include "../Object/CharacterBase.h"

#include "../Utility/CharacterData.h"

using namespace CharacterData;

/// <summary>
/// CSV�t�@�C���f�[�^��ǂݍ��ރN���X
/// </summary>
class CsvLoad
{
public:	// �֐�
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CsvLoad();

	/// <summary>
	/// ���Ԃ̎擾
	/// </summary>
	/// <returns>����</returns>
	static CsvLoad& GetInstance();

	void AnimLoad(CharacterBase::AnimData& data, const char* charcterName);

private:	// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���p�^�[��
	/// </summary>
	CsvLoad();

	/// <summary>
	/// �R�s�[�R���X�g���N�^
	/// �R�s�[���֎~����
	/// </summary>
	/// <param name="">����</param>
	CsvLoad(const CsvLoad&) = delete;

	/// <summary>
	/// ������֎~����
	/// </summary>
	/// <param name="">����</param>
	void operator=(const CsvLoad&) = delete;
};