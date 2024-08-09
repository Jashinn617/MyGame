#include "SceneGameClear.h"
#include "StageSceneManager.h"

SceneGameClear::SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager)
{
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
}

std::shared_ptr<SceneBase> SceneGameClear::Update(Input& input)
{
	return shared_from_this();
}

void SceneGameClear::Draw()
{
}

void SceneGameClear::End()
{
}

void SceneGameClear::ChangeMainScene()
{
}

void SceneGameClear::ChangeTitleScene()
{
}
