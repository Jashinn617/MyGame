#include "DxLib.h"

#include "SceneGameClear.h"
#include "StageSceneManager.h"

#include "../Util/Result.h"
#include "../Util/Time.h"
#include "../Util/Ranking.h"



#include <cassert>

namespace
{
	const char* const kBackgroundFikeName = "Data/Img/Result/Background.png";	// 背景画像ファイル

	// 自身のクリアタイムの画像ファイル
	const char* const kMyTimeNumFileName[10] =
	{
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum0.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum1.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum2.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum3.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum4.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum5.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum6.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum7.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum8.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum9.png"
	};

	// ランキングタイムの画像ファイル
	const char* const kRankingTimeNumFileName[10] =
	{
		"Data/Img/Ranking/RankingNum/RankingNum0.png",
		"Data/Img/Ranking/RankingNum/RankingNum1.png",
		"Data/Img/Ranking/RankingNum/RankingNum2.png",
		"Data/Img/Ranking/RankingNum/RankingNum3.png",
		"Data/Img/Ranking/RankingNum/RankingNum4.png",
		"Data/Img/Ranking/RankingNum/RankingNum5.png",
		"Data/Img/Ranking/RankingNum/RankingNum6.png",
		"Data/Img/Ranking/RankingNum/RankingNum7.png",
		"Data/Img/Ranking/RankingNum/RankingNum8.png",
		"Data/Img/Ranking/RankingNum/RankingNum9.png"
	};

	// テキスト画像ファイル
	const char* const kTextFileName[3] =
	{
		"Data/Img/Result/ClearTimeText.png",
		"Data/Img/Result/RankText.png",
		"Data/Img/Result/RankingText.png"
	};

	// ランキング画像ファイル
	const char* const kRankingFileName[3] =
	{
		"Data/Img/Ranking/Ranking1.png",
		"Data/Img/Ranking/Ranking2.png",
		"Data/Img/Ranking/Ranking3.png"
	};

	// テキストボックス画像ファイル
	const char* const kTextBoxFileName[2] =
	{
		"Data/Img/Result/ResultTextBox1.png",
		"Data/Img/Result/ResultTextBox2.png"
	};

	// ボタン画像ファイル
	const char* const kButtonFileName[2] =
	{
		"Data/Img/Result/StageBackButton.png",
		"Data/Img/Result/TitleBackButton.png"
	};

	/*テキスト座標*/
	constexpr int kTextPosX1 = static_cast<int>(Game::kScreenWidth * 0.28f);
	constexpr int kTextPosX2 = static_cast<int>(Game::kScreenWidth * 0.75f);
	constexpr int kTextPosY1 = static_cast<int>(Game::kScreenHeight * 0.13f);
	constexpr int kTextPosY2 = static_cast<int>(Game::kScreenHeight * 0.42f);
	/*ランキング座標*/
	constexpr int kRankingPosX = static_cast<int>(Game::kScreenWidth * 0.63f);
	constexpr int kRnakingPosY1 = static_cast<int>(Game::kScreenHeight * 0.35f);
	constexpr int kRnakingPosY2 = static_cast<int>(Game::kScreenHeight * 0.55f);
	constexpr int kRnakingPosY3 = static_cast<int>(Game::kScreenHeight * 0.75f);
	constexpr float kRankingSize = 0.3f;	// ランキングサイズ
	/*テキストボックス座標*/
	constexpr int kTextBoxPosX1 = static_cast<int>(Game::kScreenWidth * 0.28f);
	constexpr int kTextBoxPosX2 = static_cast<int>(Game::kScreenWidth * 0.75f);
	constexpr int kTextBoxPosY = static_cast<int>(Game::kScreenHeight * 0.48f);
	constexpr int kTextBoxAlpha = static_cast<int>(255 * 0.8f);	// テキストボックスの不透明度

	constexpr int kImageDrawTime = 120;	// 画像が表示されるまでの時間
}

SceneGameClear::SceneGameClear() :
	m_backgroundH(-1),
	m_stageClearTime(0),
	m_isSceneEnd(false),
	m_isNextScene(false),
	m_stageKind(Game::Stage::StageNum)
{
	m_pImageDrawTime = std::make_shared<Time>(kImageDrawTime);

	// クリアタイム
	m_stageClearTime = m_pStageSceneManager->GetGameClearTime();

	m_pResult = std::make_shared<Result>(m_stageClearTime, m_pStageSceneManager->GetStageKind());

	/*画像ハンドルのロード*/
	m_backgroundH = LoadGraph(kBackgroundFikeName);
	for (int i = 0; i < m_myTimeNumH.size(); i++)
	{
		m_myTimeNumH[i] = LoadGraph(kMyTimeNumFileName[i]);
	}
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		m_rankingTimeNumH[i] = LoadGraph(kRankingTimeNumFileName[i]);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		m_textH[i] = LoadGraph(kTextFileName[i]);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		m_rankingH[i] = LoadGraph(kRankingFileName[i]);
	}
	for (int i = 0; i < m_textBoxH.size(); i++)
	{
		m_textBoxH[i] = LoadGraph(kTextBoxFileName[i]);
	}
	for (int i = 0; i < m_buttonH.size(); i++)
	{
		m_buttonH[i] = LoadGraph(kButtonFileName[i]);
	}
}

SceneGameClear::SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager, Game::Stage stageKind):
	m_backgroundH(-1),
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

	/*画像ハンドルのロード*/
	m_backgroundH = LoadGraph(kBackgroundFikeName);
	for (int i = 0; i < m_myTimeNumH.size(); i++)
	{
		m_myTimeNumH[i] = LoadGraph(kMyTimeNumFileName[i]);
	}
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		m_rankingTimeNumH[i] = LoadGraph(kRankingTimeNumFileName[i]);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		m_textH[i] = LoadGraph(kTextFileName[i]);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		m_rankingH[i] = LoadGraph(kRankingFileName[i]);
	}
	for (int i = 0; i < m_textBoxH.size(); i++)
	{
		m_textBoxH[i] = LoadGraph(kTextBoxFileName[i]);
	}
	for (int i = 0; i < m_buttonH.size(); i++)
	{
		m_buttonH[i] = LoadGraph(kButtonFileName[i]);
	}
}

SceneGameClear::~SceneGameClear()
{
	/*画像のデリート*/
	DeleteGraph(m_backgroundH);
	for (int i = 0; i < m_myTimeNumH.size(); i++)
	{
		DeleteGraph(m_myTimeNumH[i]);
	}
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		DeleteGraph(m_rankingTimeNumH[i]);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		DeleteGraph(m_textH[i]);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		DeleteGraph(m_rankingH[i]);
	}
	for (int i = 0; i < m_textBoxH.size(); i++)
	{
		DeleteGraph(m_textBoxH[i]);
	}
	for (int i = 0; i < m_buttonH.size(); i++)
	{
		DeleteGraph(m_buttonH[i]);
	}
}

void SceneGameClear::Init()
{
	// ランキングの更新、取得
	m_pRanking->UpdateRanking(m_stageKind, m_stageClearTime);
	m_ranking = m_pRanking->GetRanking(m_stageKind);
}

std::shared_ptr<SceneBase> SceneGameClear::Update(Input& input)
{
	m_pResult->Update();

	m_pStageSceneManager->Update(input);

	return shared_from_this();
}

void SceneGameClear::Draw()
{
	// 背景の描画
	DrawGraph(0, 0, m_backgroundH, false);

	/*テキストボックスの描画*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kTextBoxAlpha);
	DrawRotaGraph(kTextBoxPosX1, kTextBoxPosY,
		1.0f, 0.0f,
		m_textBoxH[0], true);
	DrawRotaGraph(kTextBoxPosX2, kTextBoxPosY,
		1.0f, 0.0f,
		m_textBoxH[1], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*テキストの描画*/
	DrawRotaGraph(kTextPosX1, kTextPosY1,
		1.0f, 0.0f,
		m_textH[0], true);
	DrawRotaGraph(kTextPosX1, kTextPosY2,
		1.0f, 0.0f,
		m_textH[1], true);
	DrawRotaGraph(kTextPosX2, kTextPosY1,
		1.0f, 0.0f,
		m_textH[2], true);
	/*ランキングの描画*/
	DrawRotaGraph(kRankingPosX, kRnakingPosY1,
		kRankingSize, 0.0f,
		m_rankingH[0], true);
	DrawRotaGraph(kRankingPosX, kRnakingPosY2,
		kRankingSize, 0.0f,
		m_rankingH[1], true);
	DrawRotaGraph(kRankingPosX, kRnakingPosY3,
		kRankingSize, 0.0f,
		m_rankingH[2], true);

	m_pResult->Draw();

#ifdef _DEBUG
	DrawString(0, 0, "GameClear", 0xffffff);
	DrawFormatString(0, 80, 0xffffff, "1位：%d 2位：%d 3位:%d",m_ranking[0]/60,m_ranking[1]/60,m_ranking[2]/60);

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
