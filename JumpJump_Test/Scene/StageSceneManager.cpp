#include "StageSceneManager.h"
#include "../Util/Input.h"
#include "../Object/ObjectManager.h"

StageSceneManager::StageSceneManager(Game::Stage stageKind):
	m_gameClearTime(0),
	m_isGameClear(false),
	m_stageKind(stageKind)
{
	m_pObjectManager = std::make_shared<ObjectManager>(stageKind);
}

StageSceneManager::~StageSceneManager()
{
	/*処理無し*/
}

void StageSceneManager::Init()
{
	/*処理無し*/
}

void StageSceneManager::Update(Input& input)
{
	m_pObjectManager->Update(input);

	// ゲームクリア時間の更新
	m_gameClearTime++;

	// クリア条件を達成した時
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
