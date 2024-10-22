#include "SceneStage.h"
#include "../Object/ObjectManager.h"


#include <cassert>

namespace
{
	constexpr float kCameraNear = 5.0f;		// カメラ手前クリップ距離
	constexpr float kCameraFar = 5000.0f;	// カメラ奥クリップ距離
}

SceneStage::SceneStage(Game::StageKind stage):
	m_stageKind(stage),
	m_pObject(std::make_shared<ObjectManager>(stage)),
	m_pNextScene(nullptr)
{
	/*処理無し*/
}

SceneStage::~SceneStage()
{
	/*処理無し*/
}

void SceneStage::Init()
{
	/*処理無し*/
}

std::shared_ptr<SceneBase> SceneStage::Update()
{
	// オブジェクトの更新
	m_pObject->Update();

	return shared_from_this();
}

void SceneStage::Draw()
{
	// オブジェクトの描画
	m_pObject->Draw();

#ifdef _DEBUG
	// デバッグ用シーン名描画
	if (static_cast<int>(m_stageKind) == 0)
	{
		DrawFormatString(0, 0, 0xffffff, "StageTest");
	}
	else
	{
		DrawFormatString(0, 0, 0xffffff, "Stage%d", static_cast<int>(m_stageKind));
	}
#endif // _DEBUG
}
