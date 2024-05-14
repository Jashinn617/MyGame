#include "DxLib.h"
#include "HandleManager.h"

#include <cassert>

HandleManager::HandleManager()
{
	LoadModel();
	LoadImg();
	LoadSound();
	ChangeSoundVolume();
	LoadFont();
}

HandleManager::~HandleManager()
{
	DeleteModel();
	DeleteImg();
	DeleteSound();
	DeleteFont();
}

int HandleManager::GetModel(const char* command) const
{
	auto it = m_modelHandleTable.find(command);

	return m_modelHandleTable.at(command);
}

int HandleManager::GetImg(const char* command) const
{
	auto it = m_modelHandleTable.find(command);

	return m_modelHandleTable.at(command);
}

int HandleManager::GetSound(const char* command) const
{
	auto it = m_modelHandleTable.find(command);

	return m_modelHandleTable.at(command);
}

int HandleManager::GetFont(const char* command) const
{
	auto it = m_modelHandleTable.find(command);

	return m_modelHandleTable.at(command);
}

void HandleManager::LoadModel()
{
	m_modelHandleTable["player"] = MV1LoadModel("Data/Model/Player/chicken.mv1");
	m_modelHandleTable["ground"] = MV1LoadModel("Data/Model/Ground.mv1");
	m_modelHandleTable["item"] = MV1LoadModel("Data/Model/Heart.mv1");
}

void HandleManager::LoadImg()
{
	m_modelHandleTable["startScreen"] = LoadGraph("Data/Img/StartImg.png");
	m_modelHandleTable["clearScreen"] = LoadGraph("Data/Img/ClearImg.png");
	m_modelHandleTable["backSky"] = LoadGraph("Data/Img/Back/Sky.png");
}

void HandleManager::LoadSound()
{
	m_modelHandleTable["jumpSE"] = LoadSoundMem("Data/Sound/SE/JumpSE.mp3");
	m_modelHandleTable["fastClearSE"] = LoadSoundMem("Data/Sound/SE/FastClearSE.mp3");
	m_modelHandleTable["normalClearSE"] = LoadSoundMem("Data/Sound/SE/NormalClearSE.mp3");
	m_modelHandleTable["slowClearSE"] = LoadSoundMem("Data/Sound/SE/SlowClearSE.mp3");
	m_modelHandleTable["itemChatchSE"] = LoadSoundMem("Data/Sound/SE/ItemChatchSE.mp3");
	m_modelHandleTable["selectSE"] = LoadSoundMem("Data/Sound/SE/SelectSE.mp3");
	m_modelHandleTable["countdownSE"] = LoadSoundMem("Data/Sound/SE/CountdownSE.mp3");
	m_modelHandleTable["startBGM"] = LoadSoundMem("Data/Sound/BGM/StartBGM.mp3");
	m_modelHandleTable["mainBGM"] = LoadSoundMem("Data/Sound/BGM/MainBGM.mp3");
	m_modelHandleTable["clearBGM"] = LoadSoundMem("Data/Sound/BGM/ClearBGM.mp3");
}

void HandleManager::ChangeSoundVolume()
{
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["jumpSE"]);
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["fastClearSE"]);
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["normalClearSE"]);
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["slowClearSE"]);
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["itemChatchSE"]);
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["selectSE"]);
	ChangeVolumeSoundMem(kSeVolume, m_modelHandleTable["countdownSE"]);
	ChangeVolumeSoundMem(kBgmVolume, m_modelHandleTable["startBGM"]);
	ChangeVolumeSoundMem(kBgmVolume, m_modelHandleTable["mainBGM"]);
	ChangeVolumeSoundMem(kBgmVolume, m_modelHandleTable["clearBGM"]);
}

void HandleManager::LoadFont()
{
	m_modelHandleTable["timeFont"] = CreateFontToHandle("GN-ƒLƒ‹ƒSU‚©‚ÈNA", 100, -1);
	m_modelHandleTable["itemNumFont"] = CreateFontToHandle("GN-ƒLƒ‹ƒSU‚©‚ÈNA", 80, -1);
	m_modelHandleTable["clearTimeFont"] = CreateFontToHandle("GN-ƒLƒ‹ƒSU‚©‚ÈNA", 70, -1);
}

void HandleManager::DeleteModel()
{
	MV1DeleteModel(m_modelHandleTable["player"]);
	MV1DeleteModel(m_modelHandleTable["ground"]);
	MV1DeleteModel(m_modelHandleTable["item"]);
}

void HandleManager::DeleteImg()
{
	DeleteGraph(m_modelHandleTable["startScreen"]);
	DeleteGraph(m_modelHandleTable["clearScreen"]);
	DeleteGraph(m_modelHandleTable["backSky"]);
}

void HandleManager::DeleteSound()
{
	DeleteSoundMem(m_modelHandleTable["jumpSE"]);
	DeleteSoundMem(m_modelHandleTable["fastClearSE"]);
	DeleteSoundMem(m_modelHandleTable["normalClearSE"]);
	DeleteSoundMem(m_modelHandleTable["slowClearSE"]);
	DeleteSoundMem(m_modelHandleTable["selectSE"]);
	DeleteSoundMem(m_modelHandleTable["countdownSE"]);
	DeleteSoundMem(m_modelHandleTable["startBGM"]);
	DeleteSoundMem(m_modelHandleTable["mainBGM"]);
	DeleteSoundMem(m_modelHandleTable["clearBGM"]);
}

void HandleManager::DeleteFont()
{
	DeleteFontToHandle(m_modelHandleTable["timeFont"]);
	DeleteFontToHandle(m_modelHandleTable["itemNumFont"]);
	DeleteFontToHandle(m_modelHandleTable["clearTimeFont"]);
}
