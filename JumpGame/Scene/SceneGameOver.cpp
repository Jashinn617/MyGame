#include "SceneGameOver.h"
#include "SceneTitle.h"
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

#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_O))
	{
		return make_shared<SceneTitle>();
	}
#endif


	return shared_from_this();
}

void SceneGameOver::Draw()
{
	DrawString(0, 0, "GameOver", 0xffffff);
}

void SceneGameOver::End()
{
}
