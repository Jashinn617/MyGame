#include "DxLib.h"

#include "SceneGameClear.h"
#include "StageSceneManager.h"

#include "../Util/Result.h"
#include "../Util/Time.h"
#include "../Util/Ranking.h"



#include <cassert>

namespace
{
	constexpr int kImageDrawTime = 120;	// 画像が表示されるまでの時間
}

SceneGameClear::SceneGameClear() :
	m_graphH(-1),
	m_stageClearTime(0),
	m_isSceneEnd(false),
	m_isNextScene(false),
	m_stageKind(Game::Stage::StageNum)
{
	m_pImageDrawTime = std::make_shared<Time>(kImageDrawTime);

	// クリアタイム
	m_stageClearTime = m_pStageSceneManager->GetGameClearTime();

	m_pResult = std::make_shared<Result>(m_stageClearTime, m_pStageSceneManager->GetStageKind());
}

SceneGameClear::SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager, Game::Stage stageKind):
	m_graphH(-1),
	m_stageClearTime(0),
	m_isSceneEnd(false),
	m_isNextScene(false),
	m_stageKind(stageKind),
	m_pStageSceneManager(pStageSceneManager)
{
	m_pImageDrawTime = std::make_shared<Time>(kImageDrawTime);

	// クリアタイム
	m_stageClearTime = m_pStageSceneManager->GetGameClearTime();
	
	m_pResult = std::make_shared<Result>(m_stageClearTime, m_pStageSceneManager->GetStageKind());
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
	// ランキングの更新、取得
	m_pRanking->UpdateRanking(m_stageKind, m_stageClearTime);
	m_rank = m_pRanking->GetRanking(m_stageKind);
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
	DrawFormatString(0, 80, 0xffffff, "1位：%d 2位：%d 3位:%d",m_rank[0]/60,m_rank[1]/60,m_rank[2]/60);

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
