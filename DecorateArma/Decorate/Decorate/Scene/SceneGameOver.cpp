#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

std::shared_ptr<SceneBase> SceneGameOver::Update()
{
	return shared_from_this();
}

void SceneGameOver::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "GameOver");
#endif // _DEBUG
}

void SceneGameOver::End()
{
}
