#include "DxLib.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	return shared_from_this();
}

void SceneTitle::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG   
}

void SceneTitle::End()
{
}
