#include "DxLib.h"
#include "SceneGame2.h"

SceneGame2::SceneGame2()
{
}

SceneGame2::~SceneGame2()
{
}

void SceneGame2::Init()
{
}

std::shared_ptr<SceneBase> SceneGame2::Update(Input& input)
{
	return shared_from_this();
}

void SceneGame2::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Game2");
#endif // _DEBUG   
}

void SceneGame2::End()
{
}