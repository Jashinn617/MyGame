#include "SceneClear.h"

SceneClear::SceneClear()
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
}

std::shared_ptr<SceneBase> SceneClear::Update()
{
	return shared_from_this();
}

void SceneClear::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Clear");
#endif // _DEBUG
}

void SceneClear::End()
{
}