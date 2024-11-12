#include "SceneSelect.h"

SceneSelect::SceneSelect()
{
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Init()
{
}

std::shared_ptr<SceneBase> SceneSelect::Update()
{
	return shared_from_this();
}

void SceneSelect::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "セレクト画面");
#endif // _DEBUG
}

void SceneSelect::End()
{
}
