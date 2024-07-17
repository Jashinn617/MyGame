#include "DxLib.h"
#include "SceneDebug.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneRanking.h"
#include "SceneTutorial.h"
#include "SceneGame1.h"
#include "SceneGame2.h"
#include "SceneResult.h"

namespace
{
	int kSceneNum = 8;

	int kSceneTextPosX = 40;
	int kSceneTextPosY = 20;
}

SceneDebug::SceneDebug():
	m_count(0)
{
}

SceneDebug::~SceneDebug()
{
}

void SceneDebug::Init()
{
}

std::shared_ptr<SceneBase> SceneDebug::Update(Input& input)
{
	if (input.IsTriggered("up"))
	{
		m_count--;
	}
	else if (input.IsTriggered("down"))
	{
		m_count++;
	}

	if (m_count >= kSceneNum)
	{
		m_count = 0;
	}
	if (m_count < 0)
	{
		m_count = kSceneNum-1;
	}

	if (input.IsTriggered("A"))
	{
		if (m_count == 0)
		{
			return make_shared<SceneTest>();
		}
		else if (m_count == 1)
		{
			return make_shared<SceneTitle>();
		}
		else if (m_count == 2)
		{
			return make_shared<SceneSelect>();
		}
		else if (m_count == 3)
		{
			return make_shared<SceneRanking>();
		}
		else if (m_count == 4)
		{
			return make_shared<SceneTutorial>();
		}
		else if (m_count == 5)
		{
			return make_shared<SceneGame1>();
		}
		else if (m_count == 6)
		{
			return make_shared<SceneGame2>();
		}
		else if (m_count == 7)
		{
			return make_shared<SceneResult>();
		}
	}


	return shared_from_this();
}

void SceneDebug::Draw()
{
	vector<int> color;
	color.resize(kSceneNum);
	for (int i = 0; i < color.size(); i++)
	{
		if (i == m_count)
		{
			color[i] = 0xff0000;
		}
		else
		{
			color[i] = 0xffffff;
		}
	}

	DrawFormatString(kSceneTextPosX, kSceneTextPosY, color[0], "Test");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*2, color[1], "Title");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*3, color[2], "Select");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*4, color[3], "Ranking");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*5, color[4], "Tutorial");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*6, color[5], "Game1");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*7, color[6], "Game2");
	DrawFormatString(kSceneTextPosX, kSceneTextPosY*8, color[7], "Result");


	DrawFormatString(0, 0, 0x00ffff, "Debug");
	DrawFormatString(60, 0, 0x00ffff, "ƒV[ƒ“‚ð‘I‘ð‚µ‚Ä‚­‚¾‚³‚¢(A‚ÅŒˆ’è)");
}

void SceneDebug::End()
{
}
