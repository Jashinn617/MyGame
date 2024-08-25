#include "DxLib.h"

#include "SceneGameClear.h"
#include "StageSceneManager.h"

#include "../Util/Result.h"
#include "../Util/Time.h"



#include <cassert>

namespace
{
	constexpr int kImageDrawTime = 120;	// 画像が表示されるまでの時間
}

SceneGameClear::SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager):
	m_graphH(-1),
	m_isSceneEnd(false),
	m_isNextScene(false),
	m_pStageSceneManager(pStageSceneManager)
{
	m_pImageDrawTime = std::make_shared<Time>(kImageDrawTime);

	// クリアタイム
	int stageClearTime = m_pStageSceneManager->GetGameClearTime();
	
	m_pResult = std::make_shared<Result>(stageClearTime, m_pStageSceneManager->GetStageKind());
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
}

std::shared_ptr<SceneBase> SceneGameClear::Update(Input& input)
{
	m_pResult->Update();

	m_pStageSceneManager->Update(input);

	return shared_from_this();
}

void SceneGameClear::Draw()
{

	m_pResult->Draw();

#ifdef _DEBUG
	DrawString(0, 0, "GameClear", 0xffffff);
#endif // _DEBUG
}

void SceneGameClear::End()
{
}

void SceneGameClear::ChangeMainScene()
{
}

void SceneGameClear::ChangeTitleScene()
{
}
