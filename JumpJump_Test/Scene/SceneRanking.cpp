#include "DxLib.h"
#include "SceneRanking.h"

SceneRanking::SceneRanking()
{
}

SceneRanking::~SceneRanking()
{
}

void SceneRanking::Init()
{
}

std::shared_ptr<SceneBase> SceneRanking::Update(Input& input)
{
	return shared_from_this();
}

void SceneRanking::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Ranking");
#endif // _DEBUG   
}

void SceneRanking::End()
{
}
