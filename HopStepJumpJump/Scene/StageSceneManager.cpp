#include "StageSceneManager.h"

#include "../Object/ObjectManager.h"

#include "../Util/CountTime.h"
#include "../Util/Input.h"
#include "../Util/SoundManager.h"


StageSceneManager::StageSceneManager(Game::Stage stageKind):
	m_gameClearTime(0),
	m_isGameClear(false),
	m_isPlayClearSE(false),
	m_stageKind(stageKind),
	m_sceneType(SceneType::Counddown)
{
	m_pObjectManager = std::make_shared<ObjectManager>(stageKind);
	m_pCountTime = std::make_shared<CountTime>();
}

StageSceneManager::~StageSceneManager()
{
	/*処理無し*/
}

void StageSceneManager::Init()
{
	// カウントダウンのSEを鳴らす
	SoundManager::GetInstance().Play("Countdown");
}

void StageSceneManager::Update(Input& input)
{
	switch (m_sceneType)
	{
	case StageSceneManager::SceneType::Counddown:
		CountdownUpdate(input);
		break;
	case StageSceneManager::SceneType::Main:
		MainUpdate(input);
		break;
	case StageSceneManager::SceneType::Clear:
		ClearUpdate(input);
		break;
	default:
		break;
	}
}

void StageSceneManager::Draw()
{
	switch (m_sceneType)
	{
	case StageSceneManager::SceneType::Counddown:
		CountdownDraw();
		break;
	case StageSceneManager::SceneType::Main:
		MainDraw();
		break;
	case StageSceneManager::SceneType::Clear:
		ClearDraw();
		break;
	default:
		break;
	}
}

void StageSceneManager::AttachGameClear(std::function<void(void)> gameClear)
{
	m_gameClear = gameClear;
}

void StageSceneManager::SetGameClear()
{
	m_pObjectManager->SetGameClear();
	m_isGameClear = true;
}

void StageSceneManager::CountdownUpdate(Input& input)
{
	// カウントダウンのSEがなり終わったらメインシーンに飛ぶ
	if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Countdown"))
	{
		m_sceneType = SceneType::Main;
	}
}

void StageSceneManager::MainUpdate(Input& input)
{
	// BGMを流す
	SoundManager::GetInstance().Play("MainScene");

	m_pObjectManager->Update(input);



	// ゲームクリア時間の更新
	m_gameClearTime++;

	m_pCountTime->Update(m_gameClearTime);

	// クリア条件を達成した時
	if (m_pObjectManager->IsGameClear() && !m_isGameClear)
	{
		m_sceneType = SceneType::Clear;
	}
}

void StageSceneManager::ClearUpdate(Input& input)
{
	// BGMを止める
	SoundManager::GetInstance().DesignationStopSound("MainScene");

	if (!m_isPlayClearSE)
	{
		// SEを流す
		SoundManager::GetInstance().Play("GameClear");
		m_isPlayClearSE = true;
	}
	
	// SEが流れ終わったら
	if (m_isPlayClearSE && !SoundManager::GetInstance().IsDesignationCheckPlaySound("GameClear"))
	{
		// ゲームクリア関数の呼び出し
		m_gameClear();
		m_isGameClear = true;
	}	
}

void StageSceneManager::CountdownDraw()
{
}

void StageSceneManager::MainDraw()
{
	m_pObjectManager->Draw();
	m_pCountTime->Draw();
}

void StageSceneManager::ClearDraw()
{
}
