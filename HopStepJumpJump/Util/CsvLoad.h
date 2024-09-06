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

	// �G�t�F�N�g�f�[�^
	struct EffectData
	{
		int resouceH = -1;			// �G�t�F�N�g�n���h�� 
		int playingEffectH = -1;	// ���ۂɃG�t�F�N�g���ăZ����Ƃ��Ɏg���n���h��
		float size = 0;				// �G�t�F�N�g�̃T�C�Y
		float speed = 1;			// �Đ��X�s�[�h
	};
}

class CsvLoad
{
public:
	~CsvLoad();

	static CsvLoad& GetInstance();

	/// <summary>
	/// �A�j���[�V�����̃��[�h
	/// </summary>
	/// <param name="Data">�A�j���[�V�������</param>
	/// <param name="charcterName">�L�����N�^�[��</param>
	void AnimLoad(CharacterBase::AnimData& Data, const char* charcterName);

	/// <summary>
	/// �T�E���h�̃��[�h
	/// </summary>
	/// <param name="Data">�T�E���h���</param>
	void SoundLoad(std::unordered_map<std::string, LoadData::SoundData>& Data);

	/// <summary>
	/// �G�t�F�N�g�̃��[�h
	/// </summary>
	/// <param name="Data">�t�@�C���f�[�^</param>
	void EffectLoad(std::unordered_map<std::string, LoadData::EffectData>& Data);

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

