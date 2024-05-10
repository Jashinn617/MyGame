#include "DxLib.h"
#include "HandleManager.h"

#include <cassert>

HandleManager::HandleManager()
{
	LoadModel();
}

HandleManager::~HandleManager()
{
}

int HandleManager::GetModel(const char* command) const
{
	auto it = m_modelHandleTable.find(command);
	assert(it != m_modelHandleTable.end());

	return m_modelHandleTable.at(command);
}

int HandleManager::GetImg(const char* command) const
{
	return 0;
}

int HandleManager::GetSound(const char* command) const
{
	return 0;
}

void HandleManager::LoadModel()
{
	m_modelHandleTable["player"] = MV1LoadModel("Data/Model/Player/chicken.mv1");
}

void HandleManager::LoadImg()
{
}

void HandleManager::LoadSound()
{
}

void HandleManager::DeleteModel()
{
}

void HandleManager::DeleteImg()
{
}

void HandleManager::DeleteSound()
{
}
