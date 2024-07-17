#include "DxLib.h"
#include "SceneTutorial.h"

SceneTutorial::SceneTutorial()
{
}

SceneTutorial::~SceneTutorial()
{
}

void SceneTutorial::Init()
{
}

std::shared_ptr<SceneBase> SceneTutorial::Update(Input& input)
{
	return shared_from_this();
}

void SceneTutorial::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Tutorial");
#endif // _DEBUG   
}

void SceneTutorial::End()
{
}
