#pragma once
#include "CharacterData.h"
#include "CsvLoad.h"

#include <unordered_map>
#include <string>

using namespace CharacterData;

/// <summary>
/// �T�E���h�̊Ǘ����s���N���X
/// �V���O���g���N���X
/// </summary>
class SoundManager
{
public:
	~SoundManager();

	static SoundManager& GetInstance()
	{
		// �B��̎���
		static SoundManager instance;

		// ���Ԃ̎Q�Ƃ�Ԃ�
		return instance;
	}

	/// <summary>
	/// �w��̃T�E���h��炷
	/// </summary>
	/// <param name="name">�T�E���h��</param>
	void Play(const char* name);

	/// <summary>
	/// �S�ẴT�E���h���~����
	/// </summary>
	void StopSound();

	/// <summary>
	/// �S�Ă�SE���~����
	/// </summary>
	void StopSE();

	/// <summary>
	/// �w��̃T�E���h���~����
	/// </summary>
	/// <param name="str"></param>
	void DesignationStopSound(std::string str);

	/// <summary>
	/// �w��̃T�E���h������Ă��邩�ǂ���
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	bool IsDesignationCheckPlaySound(std::string str);

	/// <summary>
	/// BGM�̉��ʕύX
	/// </summary>
	void ChangeBGMVolume();

	/// <summary>
	/// SE�̉��ʕύX
	/// </summary>
	void ChangeSEVolume();

private:	// �\����
	/// <summary>
	/// �ύX�����T�E���h�����t�@�C���ɏ�������
	/// </summary>
	struct SoundConfigInfo
	{
		char signature[5];			// "SND_"
		float version;				// 1.0f
		unsigned short	volumeSE;	// 0�`255
		unsigned short	volumeBGM;	// 0�`255
	};

private:	// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���p�^�[���Ȃ̂�
	/// �R���X�g���N�^��private�ɒu��
	/// </summary>
	SoundManager();

	// �R�s�[���֎~����
	// �R�s�[�R���X�g���N�^
	SoundManager(const SoundManager&) = delete;
	// ������֎~����
	void operator=(const SoundManager&) = delete;

private:	// �ϐ�
	std::unordered_map<std::string, LoadData::SoundData> m_data;	// �T�E���h�f�[�^
};

