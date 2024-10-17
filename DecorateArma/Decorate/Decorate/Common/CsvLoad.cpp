#include "CsvLoad.h"

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// <summary>
/// ��؂蕶�������o�����܂ŕ������v�b�V���o�b�N����
/// </summary>
/// <param name="input">�����o������</param>
/// <param name="delimiter">��؂蕶��</param>
/// <returns>���o�����܂ł̕�����</returns>
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
	// �B��̎���
	static CsvLoad instance;

	return instance;
}

void CsvLoad::AnimLoad(CharacterBase::AnimData& data, const char* charcterName)
{
	// �t�@�C�����̓ǂݍ���
	std::ifstream ifs("Data/CsvFile/AnimNum.csv");
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
		// strvec[3]	: ���胂�[�V����
		// strvec[4]	: �W�����v�����[�V����
		// strvec[5]	: �W�����v�����[�V����
		// strvec[6]	: �_���[�W���[�V����

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
	data.idle = animData[1];
	data.walk = animData[2];
	data.run = animData[3];
	data.jumpStart = animData[4];
	data.jumpIdle = animData[5];
	data.damage = animData[6];
}

