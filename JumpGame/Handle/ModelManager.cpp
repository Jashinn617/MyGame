#include "ModelManager.h"
#include "DxLib.h"
#include <cassert>

ModelManager::ModelManager():
	playerHandle(-1)
{
	playerHandle = MV1LoadModel("Data/Model/chicken.mv1");
	assert(playerHandle != -1);
}

ModelManager::~ModelManager()
{
	MV1DeleteModel(playerHandle);
}

void ModelManager::CreateModel()
{
	
}

void ModelManager::DestroyModel()
{
	
}
