#include "SceneGameOver.h"
#include "DxLib.h"

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

shared_ptr<SceneBase> SceneGameOver::Update()
{
	return shared_from_this();
}

void SceneGameOver::Draw()
{
	DrawString(0, 0, "GameOver", 0xffffff);
}

void SceneGameOver::End()
{
}
