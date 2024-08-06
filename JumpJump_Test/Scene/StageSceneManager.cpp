#include "StageSceneManager.h"
#include "../Util/Input.h"
#include "../Object/ObjectManager.h"

StageSceneManager::StageSceneManager(Game::Stage stageKind):
	m_gameClearTime(0),
	m_isGameClear(false),
	m_stageKind(stageKind)
{
	m_pObjectManager = std::make_shared<ObjectManager>();
}

StageSceneManager::~StageSceneManager()
{
	/*処理無し*/
}

void StageSceneManager::Init()
{
	/*処理無し*/
}

void StageSceneManager::Update()
{
	m_pObjectManager->Update();

	// ゲームクリア時間の更新
	m_gameClearTime++;

	// クリア条件を達成したら
	if (m_pObjectManager->IsGameClear() && !m_isGameClear)
	{
		// ゲームクリア関数の呼び出し
		m_gameClear();
		m_isGameClear = true;
	}
}

void StageSceneManager::Draw()
{
	m_pObjectManager->Draw();
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
