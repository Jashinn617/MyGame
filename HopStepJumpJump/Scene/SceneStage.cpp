#include "SceneStage.h"
#include "StageSceneManager.h"
#include "SceneDebug.h"
#include "SceneGameClear.h"
#include "SceneTitle.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"

#include "../Util/Collision.h"
#include "../Util/Input.h"
#include "../Util/SoundManager.h"

#include <cassert>
#include <functional>

namespace
{
	constexpr float kCameraNear = 5.0f;
	constexpr float kCameraFar = 5000.0f;
}

SceneStage::SceneStage(Game::Stage stage):
	m_isSceneEnd(false),
	m_nextScene(nullptr),
	m_stageKind(stage)
{
	m_pStageSceneManager = std::make_shared<StageSceneManager>(stage);

	// カメラの設定
	SetCameraNearFar(kCameraNear, kCameraFar);

}

SceneStage::~SceneStage()
{
	/*処理無し*/
}

void SceneStage::Init()
{
	m_pStageSceneManager->Init();
}

std::shared_ptr<SceneBase> SceneStage::Update(Input& input)
{
	

#ifdef _DEBUG
	// デバッグに飛ぶ
	if (input.IsTriggered(""))
	{
		return make_shared<SceneDebug>();
	}
#endif // _DEBUG

	//// オプションを開く
	//if (input.IsTriggered(""))
	//{
	//	
	//}

	if (m_nextScene != nullptr)
	{
		return m_nextScene;
	}

	m_pStageSceneManager->Update(input);

	if (m_pStageSceneManager->IsGameClear())
	{
		GameClear();
	}

	UpdateFade();

	if (m_pStageSceneManager->GetNextScene() == StageSceneManager::NextScene::GameScene)
	{
		return make_shared<SceneStage>(m_stageKind);
	}
	else if (m_pStageSceneManager->GetNextScene() == StageSceneManager::NextScene::Title)
	{
		return make_shared<SceneTitle>();
	}
	else if (m_pStageSceneManager->GetNextScene() == StageSceneManager::NextScene::My)
	{
		return shared_from_this();
	}

	return shared_from_this();
}

void SceneStage::Draw()
{
	m_pStageSceneManager->Draw();

	DrawFade();
}

void SceneStage::End()
{
	/*処理無し*/
}

void SceneStage::GameClear()
{
	/*処理無し*/
}
