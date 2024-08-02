#include "DxLib.h"
#include "SceneTest.h"

SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
}

std::shared_ptr<SceneBase> SceneTest::Update(Input& input)
{
	return shared_from_this();
}

void SceneTest::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Test");
#endif // _DEBUG   
}

void SceneTest::End()
{
}

void SceneTest::DrawGrid()
{
}
