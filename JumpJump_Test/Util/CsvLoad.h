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
	};
}

class CsvLoad
{
};

