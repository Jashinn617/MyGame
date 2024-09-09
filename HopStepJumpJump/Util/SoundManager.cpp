#include "DxLib.h"
#include "SoundManager.h"
#include "SaveData.h"

#include <cassert>

namespace
{
	constexpr int kVoluRateOne = 80;	// ���ʂ̊�{�l
}

SoundManager::SoundManager()
{
	// �T�E���h�f�[�^�̃��[�h
	CsvLoad::GetInstance().SoundLoad(m_data);
}

SoundManager::~SoundManager()
{
	/*��������*/
}

void SoundManager::Play(const char* name)
{
	// BGM�̏ꍇ
	if (m_data[name].isBgm)
	{
		// �w�肵���T�E���h������Ă������͏������I������
		if (CheckSoundMem(m_data[name].handle)) return;
		// �T�E���h�𗬂�(���[�v)
		PlaySoundMem(m_data[name].handle, DX_PLAYTYPE_LOOP);

		// ���ʒ���
		float vol = (static_cast<float>(m_data[name].volRate) / 255.0f);

		ChangeVolumeSoundMem(static_cast<int>(SaveData::GetInstance().GetBGMVol()
			* kVoluRateOne * vol),
			m_data[name].handle);
	}
	// SE�̏ꍇ
	else if(!m_data[name].isBgm)
	{
		// �T�E���h�𗬂�(�o�b�N)
		PlaySoundMem(m_data[name].handle, DX_PLAYTYPE_BACK);

		// ���ʒ���
		float vol = (static_cast<float>(m_data[name].volRate) / 255.0f);
		ChangeVolumeSoundMem(static_cast<int>(SaveData::GetInstance().GetSEVol()
			* kVoluRateOne * vol),
			m_data[name].handle);
	}
}

void SoundManager::StopSound()
{
	StopMusic();

	for (auto& handle : m_data)
	{
		// �T�E���h�̒�~
		StopSoundMem(handle.second.handle);
	}
}

void SoundManager::StopSE()
{
	for (auto& handle : m_data)
	{
		// BGM�̏ꍇ�͉������Ȃ�
		if (handle.second.isBgm) continue;

		// �T�E���h�̒�~
		StopSoundMem(handle.second.handle);
	}
}

void SoundManager::DesignationStopSound(std::string str)
{
	// �w�肵���T�E���h�̒�~
	StopSoundMem(m_data[str].handle);
}

bool SoundManager::IsDesignationCheckPlaySound(std::string str)
{
	// �w�肵���T�E���h������Ă��邪
	return CheckSoundMem(m_data[str].handle);
}

void SoundManager::ChangeBGMVolume()
{
	for (auto& handle : m_data)	// BGM�̉��ʕύX
	{
		// �T�E���h�̎�ނ�BGM�ł͂Ȃ��Ƃ��͏�������߂�
		if (!handle.second.isBgm)continue;

		ChangeVolumeSoundMem(SaveData::GetInstance().GetBGMVol() * kVoluRateOne,
			handle.second.handle);
	}
}

void SoundManager::ChangeSEVolume()
{
	for (auto& handle : m_data)	// SE�̉��ʕύX
	{
		// �T�E���h�̎�ނ�BGM�̎�(SE�ł͂Ȃ��Ƃ�)
		// �͏�������߂�
		if (handle.second.isBgm)continue;

		ChangeVolumeSoundMem(SaveData::GetInstance().GetSEVol() * kVoluRateOne,
			handle.second.handle);
	}
}
