#include "DxLib.h"
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

std::shared_ptr<SceneBase> SceneSelect::Update(Input& input)
{
	return shared_from_this();
}

void SceneSelect::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Select");
#endif // _DEBUG   
}

void SceneSelect::End()
{
}
