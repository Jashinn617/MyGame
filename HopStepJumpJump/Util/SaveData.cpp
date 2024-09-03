#include "DxLib.h"
#include "SaveData.h"

#include <fstream>
#include <cassert>

namespace
{
	constexpr int kCurrentSaveVersion = 0;	// �Z�[�u�f�[�^�̃o�[�W����
	const char* const kSaveDataFileName = "SaveData.dat";	// �Z�[�u�f�[�^�t�@�C����
}

SaveData::SaveData()
{
	/*��������*/
}

SaveData::~SaveData()
{
	/*��������*/
}

void SaveData::Load()
{
	// �f�[�^�̃N���A
	ClearSaveData();

	std::ifstream ifs;
	ifs.open(kSaveDataFileName, std::ios_base::binary);
	if (ifs.fail())
	{
		//�t�@�C���ǂݍ��ݎ��s �Z�[�u�f�[�^�����
		CreateNewSaveData();
		return;
	}
	else
	{
		Data data;
		ifs.read((char*)&data, sizeof(Data));
		ifs.close();

		if (data.version == kCurrentSaveVersion)
		{
			// �ǂݍ��񂾃f�[�^�����ۂɎg�p����f�[�^�ɃR�s�[
			m_data = data;
		}
		else
		{
			// �����[�X��ɃZ�[�u�f�[�^�̃o�[�W�������ς������������悤
			assert(false);
		}
	}

}

void SaveData::Write()
{
	// �f�[�^���t�@�C���ɏ�������
	std::ofstream ofs(kSaveDataFileName, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(Data));
}

void SaveData::ChangeBGMVol(int BGMVol)
{
	m_data.volBGM = BGMVol;
}

void SaveData::ChangeSEVol(int SEVol)
{
	m_data.volSE = SEVol;
}

int SaveData::GetBGMVol() const
{
	return m_data.volBGM;
}

int SaveData::GetSEVol() const
{
	return m_data.volSE;
}

void SaveData::CreateNewSaveData()
{
	m_data.volBGM = 2;		// BGM����	0~5
	m_data.volSE = 2;		// SE����	0~5
}

void SaveData::ClearSaveData()
{
	ClearSaveData();

	std::ofstream ofs(kSaveDataFileName, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(SaveData));
}
