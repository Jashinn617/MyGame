#include "DxLib.h"
#include "SceneRanking.h"
#include "../Util/Input.h"

#include "../Util/Ranking.h"

namespace
{
	const char* const kBackgroundFileName = "Data/Img/Ranking/Background.png";	// 背景画像ファイル
	const char* const kBackButtonFileName = "Data/Img/Rnking/BackButton.png";	// 戻るボタン画像ファイル

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

	// テキストボックス画像ファイル
	const char* const kTextBoxFileName[2] =
	{
		"Data/Img/Result/ResultTextBox1.png",
		"Data/Img/Result/ResultTextBox2.png"
	};

	// ランキング画像ファイル
	const char* const kRankingFileName[3] =
	{
		"Data/Img/Ranking/Ranking1.png",
		"Data/Img/Ranking/Ranking2.png",
		"Data/Img/Ranking/Ranking3.png"
	};
}

SceneRanking::SceneRanking():
	m_backgroundH(-1)
{
	/*画像のロード*/
	m_backgroundH = LoadGraph(kBackgroundFileName);
}

SceneRanking::~SceneRanking()
{
	/*画像のデリート*/
	DeleteGraph(m_backgroundH);
}

void SceneRanking::Init()
{
}

std::shared_ptr<SceneBase> SceneRanking::Update(Input& input)
{
	return shared_from_this();
}

void SceneRanking::Draw()
{
	// 背景描画
	DrawGraph(0, 0, m_backgroundH, false);

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Ranking");
#endif // _DEBUG   
}

void SceneRanking::End()
{
}
