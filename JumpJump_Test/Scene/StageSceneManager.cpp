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
	/*��������*/
}

void StageSceneManager::Init()
{
	/*��������*/
}

void StageSceneManager::Update(Input& input)
{
	m_pObjectManager->Update(input);

	// �Q�[���N���A���Ԃ̍X�V
	m_gameClearTime++;

	// �N���A������B��������
	if (m_pObjectManager->IsGameClear() && !m_isGameClear)
	{
		// �Q�[���N���A�֐��̌Ăяo��
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
