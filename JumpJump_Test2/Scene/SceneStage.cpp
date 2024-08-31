#include "SceneStage.h"
#include "StageSceneManager.h"
#include "SceneDebug.h"
#include "SceneGameClear.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"

#include "../Util/Collision.h"
#include "../Util/Input.h"

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
	m_pStageSceneManager->AttachGameClear([=] {GameClear(); });

	// カメラの設定
	SetCameraNearFar(kCameraNear, kCameraFar);

}

SceneStage::~SceneStage()
{
}

void SceneStage::Init()
{
}

std::shared_ptr<SceneBase> SceneStage::Update(Input& input)
{
	UpdateFade();

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

	UpdateFade();


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
	m_isSceneEnd = true;
	
	// クリアシーンに飛ぶ
	m_nextScene = make_shared<SceneGameClear>(m_pStageSceneManager, m_stageKind);
}
