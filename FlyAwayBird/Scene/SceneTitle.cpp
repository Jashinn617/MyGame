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

shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	return shared_from_this();
}

void SceneTitle::Draw()
{
#ifdef _DEBUG
	DrawString(8, 8, "Title", 0xffffff);
#endif // DEBUG
}

void SceneTitle::End()
{
}
