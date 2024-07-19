#include "DxLib.h"
#include "SceneGame1.h"

SceneGame1::SceneGame1()
{
}

SceneGame1::~SceneGame1()
{
}

void SceneGame1::Init()
{
}

std::shared_ptr<SceneBase> SceneGame1::Update(Input& input)
{
	return shared_from_this();
}

void SceneGame1::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Game1");
#endif // _DEBUG   
}

void SceneGame1::End()
{
}
