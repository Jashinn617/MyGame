#pragma once
#include "CharacterData.h"
#include "../Object/ObjectBase.h"
#include "../Object/CharacterBase.h"

#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace CharacterData;

namespace LoadData
{
	// �T�E���h�f�[�^
	struct SoundData
	{
		// �Œ�f�[�^
		bool isBgm = false;		// BGM��SE��
		float volRate = 255;	// �{�����[������

		int handle = -1;	// �T�E���h�n���h��
	};
}

class CsvLoad
{
public:
	~CsvLoad();

	static CsvLoad& GetInstance();

	void AnimLoad(CharacterBase::AnimData& Data, const char* charcterName);

	void SoundLoad(std::unordered_map<std::string, LoadData::SoundData>& Data);

private:
	/// <summary>
	/// �V���O���g���p�^�[��
	/// </summary>
	CsvLoad();

	// �R�s�[���֎~����
	// �R�s�[�R���X�g���N�^
	CsvLoad(const CsvLoad&) = delete;
	// ������֎~����
	void operator=(const CsvLoad&) = delete;
};

