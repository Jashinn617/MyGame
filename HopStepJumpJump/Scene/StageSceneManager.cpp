#include "StageSceneManager.h"

#include "../Object/ObjectManager.h"

#include "../Util/CountTime.h"
#include "../Util/Input.h"
#include "../Util/SoundManager.h"


StageSceneManager::StageSceneManager(Game::Stage stageKind):
	m_gameClearTime(0),
	m_isGameClear(false),
	m_stageKind(stageKind)
{
	m_pObjectManager = std::make_shared<ObjectManager>(stageKind);
	m_pCountTime = std::make_shared<CountTime>();
}

StageSceneManager::~StageSceneManager()
{
	/*��������*/
}

void StageSceneManager::Init()
{
	// BGM�𗬂�
	SoundManager::GetInstance().Play("MainScene");
}

void StageSceneManager::Update(Input& input)
{
	m_pObjectManager->Update(input);

	if (!m_isGameClear)
	{
		// �Q�[���N���A���Ԃ̍X�V
		m_gameClearTime++;

		m_pCountTime->Update(m_gameClearTime);

		// �N���A������B��������
		if (m_pObjectManager->IsGameEnd() && !m_isGameClear)
		{
			m_isGameClear = true;
			SoundManager::GetInstance().DesignationStopSound("MainScene");
		}
	}
	else
	{
		if (m_pObjectManager->IsGameClear())
		{
			// BGM�𗬂�
			SoundManager::GetInstance().Play("ClearScene");
		}

	
	}

}

void StageSceneManager::Draw()
{
	m_pObjectManager->Draw();
	if (!m_isGameClear)
	{
		m_pCountTime->Draw();
	}
	
}

void StageSceneManager::SetGameClear()
{
	m_pObjectManager->SetGameClear();
	m_isGameClear = true;
}
