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
#include "StageSceneManager.h"

#include "../Util/Input.h"
#include "../Util/Vec2.h"

namespace
{
	constexpr float kCursorPosX = 500.0f;		// 初期カーソル位置X
	constexpr float kCursorPosY = 300.0f;		// 初期カーソル位置Y

	constexpr float kCursorMove = 50.0f;		// カーソルの移動量
}

SceneDebug::SceneDebug():
	m_count(0)
{
	m_sceneString[static_cast<int>(SceneType::Debug)] = "Debug";
	m_sceneString[static_cast<int>(SceneType::Stage1)] = "Stage1";
	m_sceneString[static_cast<int>(SceneType::Stage2)] = "Stage2";
	m_sceneString[static_cast<int>(SceneType::Option)] = "Option";
	m_sceneString[static_cast<int>(SceneType::GameClear)] = "GameClear";
	m_sceneString[static_cast<int>(SceneType::Title)] = "Title";
	m_sceneString[static_cast<int>(SceneType::StageSelect)] = "StageSelect";
	m_sceneString[static_cast<int>(SceneType::Tutorial)] = "Tutorial";
}

SceneDebug::~SceneDebug()
{
}

void SceneDebug::Init()
{
}

std::shared_ptr<SceneBase> SceneDebug::Update(Input& input)
{
	// ボタンが押されたら選択されたシーンに遷移する
	if (input.IsTriggered("select"))
	{
		return UpdateNextScene();
	}

	UpdateCursor(input);

	UpdateFade();
	
	return shared_from_this();
}

void SceneDebug::Draw()
{
	for (int i = 0; i < static_cast<int>(m_sceneString.size()); i++)
	{
		DrawString(static_cast<int>(kCursorPosX), 
			static_cast<int>(kCursorPosY + (i * kCursorMove)), 
			m_sceneString[i].c_str(), 
			0xffffff);

		if (m_count == i)
		{
			// 選ばれている文字は赤くする
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),
				m_sceneString[i].c_str(),
				0xff0000);
		}
	}

	DrawFormatString(0, 0, 0x00ffff, "Debug");
	DrawFormatString(60, 0, 0x00ffff, "シーンを選択してください(Aで決定)");

	DrawFade();
}

void SceneDebug::End()
{
}

void SceneDebug::UpdateCursor(Input& input)
{
	if (input.IsTriggered("up"))
	{
		m_count--;
		if (m_count < 0)
		{
			m_count = static_cast<int>(m_sceneString.size() - 1);
		}
	}

	if (input.IsTriggered("down"))
	{
		m_count++;
		if (m_count >= static_cast<int>(m_sceneString.size()))
		{
			m_count = 0;
		}
	}
}

std::shared_ptr<SceneBase> SceneDebug::UpdateNextScene()
{
	std::shared_ptr<SceneBase> nextScene = nullptr;
	std::shared_ptr<StageSceneManager> mainSceneManager = nullptr;

	// 選択されたシーンに遷移する
	

	return nextScene;
}
