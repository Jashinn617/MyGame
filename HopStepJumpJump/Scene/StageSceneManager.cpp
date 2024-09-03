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
	/*��������*/
}

void StageSceneManager::Init()
{
	// �J�E���g�_�E����SE��炷
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
	// �J�E���g�_�E����SE���Ȃ�I������烁�C���V�[���ɔ��
	if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Countdown"))
	{
		m_sceneType = SceneType::Main;
	}
}

void StageSceneManager::MainUpdate(Input& input)
{
	// BGM�𗬂�
	SoundManager::GetInstance().Play("MainScene");

	m_pObjectManager->Update(input);



	// �Q�[���N���A���Ԃ̍X�V
	m_gameClearTime++;

	m_pCountTime->Update(m_gameClearTime);

	// �N���A������B��������
	if (m_pObjectManager->IsGameClear() && !m_isGameClear)
	{
		m_sceneType = SceneType::Clear;
	}
}

void StageSceneManager::ClearUpdate(Input& input)
{
	// BGM���~�߂�
	SoundManager::GetInstance().DesignationStopSound("MainScene");

	if (!m_isPlayClearSE)
	{
		// SE�𗬂�
		SoundManager::GetInstance().Play("GameClear");
		m_isPlayClearSE = true;
	}
	
	// SE������I�������
	if (m_isPlayClearSE && !SoundManager::GetInstance().IsDesignationCheckPlaySound("GameClear"))
	{
		// �Q�[���N���A�֐��̌Ăяo��
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
