#include "SceneOption.h"
#include "../Util/Input.h"

SceneOption::SceneOption(std::shared_ptr<SceneBase> prevScene)
{
}

SceneOption::~SceneOption()
{
}

void SceneOption::Init()
{
}

std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	return std::shared_ptr<SceneBase>();
}

void SceneOption::Draw()
{
}

void SceneOption::End()
{
}
