#include "CsvLoad.h"
#include "EffekseerForDXLib.h"

#include <vector>
#include<array>
#include <string>
#include<cassert>

//����̕��������o�����܂ŕ������v�b�V���o�b�N����
std::vector<std::string> Split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

CsvLoad::CsvLoad()
{
	/*��������*/
}

CsvLoad::~CsvLoad()
{
	/*��������*/
}

CsvLoad& CsvLoad::GetInstance()
{
	static CsvLoad instance;

	return instance;
}

void CsvLoad::AnimLoad(CharacterBase::AnimData& Data, const char* charcterName)
{
	// �t�@�C�����̓ǂݍ���
	std::ifstream ifs("Data/File/AnimNum.csv");
	std::string line;

	std::array<int8_t, 7> animData{};

	std::vector<std::string> strvec;

	while (getline(ifs, line))
	{
		// csv�f�[�^�P�s���A','�ŕ����̕�����ɕ���
		strvec = Split(line, ',');

		// strvec[0]	: �L������	string
		// strvec[1]	: �ҋ@���[�V����
		// strvec[2]	: �������[�V����
		// strvec[3]	: �W�����v�����[�V����
		// strvec[4]	: �W�����v�����[�V����
		// strvec[5]	: ���胂�[�V����
		// strvec[6]	: �m�b�N�o�b�N���[�V����

		//�Q�Ƃ������L�������������Ă����珈������߂�
		const char* str = strvec[0].c_str();
		if (strcmp(str, charcterName) == 0)
		{
			for (int i = 0; i < animData.size(); i++)
			{
				//�L�����N�^�[�����͂���Ȃ��̂ŏȂ�
				if (i == 0)continue;
				int animNum = stoi(strvec[i]);
				animData[i] = static_cast<int8_t>(animNum);
			}
			break;
		}

		else
		{
			strvec.erase(strvec.begin(), strvec.end());
		}
	}

	//�O���t�@�C�����玝���Ă����X�e�[�^�X�����X�e�[�^�X�f�[�^�ɓ����
	Data.idle = animData[1];
	Data.walk = animData[2];
	Data.jumpStart = animData[3];
	Data.jumpIdle = animData[4];
	Data.run = animData[5];
	Data.knockBack = animData[6];
}

void CsvLoad::SoundLoad(std::unordered_map<std::string, LoadData::SoundData>& Data)
{
	// �t�@�C�����̓ǂݍ���
	std::ifstream ifs("Data/File/SoundData.csv");
	std::string line;
	while (getline(ifs, line))
	{
		// csv�f�[�^�P�s���A','�ŕ����̕�����ɕ���
		std::vector<std::string> strvec = Split(line, ',');

		// strvec[0]	: �t�@�C����	string
		// strvec[1]	: BGM�t���O		int(bool �ɕϊ�������)
		// strvec[2]	: ����			float

		// �������K�؂ȃf�[�^�^�ɕϊ����Ċi�[
		LoadData::SoundData data{};

		std::string str;
		
		//BGM��SE���𔻒f����
		if (stoi(strvec[1]) == 0)	// SE
		{
			str = "Data/Sound/SE/" + strvec[0] + ".mp3";
			//�T�E���h�����[�h
			data.handle = LoadSoundMem(str.c_str());
			data.isBgm = false;
		}
		else	// BGM
		{
			str = "Data/Sound/BGM/" + strvec[0] + ".mp3";
			//�T�E���h�����[�h
			data.handle = LoadSoundMem(str.c_str());

			data.isBgm = true;
		}
		//�{�����[���̑傫����ݒ�
		data.volRate = stof(strvec[2]);

		//strvec[0]�Ƃ����z�񖼂Ƀf�[�^��ۑ�
		Data[strvec[0]] = data;
	}
}

void CsvLoad::EffectLoad(std::unordered_map<std::string, LoadData::EffectData>& Data)
{
	// �t�@�C�����̓ǂݍ���
	std::ifstream ifs("Data/File/EffectData.csv");
	std::string line;

	while (getline(ifs, line))
	{
		// csv�f�[�^�P�s���A','�ŕ����̕�����ɕ���
		std::vector<std::string> strvec = Split(line, ',');

		// strvec[0]	: �G�t�F�N�g��	string
		// strvec[1]	: �G�t�F�N�g�T�C�Y
		// strvec[2]	: �G�t�F�N�g�̍Đ����x

		// �������K�؂ȃf�[�^�^�ɕϊ����Ċi�[
		LoadData::EffectData data{};

		///�t�@�C����
		std::string fileName = "Data/Effect/";
		fileName += strvec[0];
		fileName += +".efk";

		const char* file = fileName.c_str();

		//�O���t�@�C�����玝���Ă����G�t�F�N�g�����G�t�F�N�g�f�[�^�ɓ����
		Data[strvec[0]].resouceH = LoadEffekseerEffect(file);
		Data[strvec[0]].size = stof(strvec[1]);
		Data[strvec[0]].speed = stof(strvec[2]);

		assert(Data[strvec[0]].resouceH != -1);
	}

	int unti = 0;
}
