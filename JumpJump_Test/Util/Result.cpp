#include "DxLib.h"
#include "Result.h"

#include "../Image/ExpansionImage.h"
#include "../Image/FadeImage.h"

#include "../Util/Easing.h"
#include "../Util/Time.h"
#include "../Util/Pad.h"
#include "../Util/SoundManager.h"

#include <cassert>

namespace
{
	// ステージごとのクリア時間の基準
	constexpr double kResultDataTable[static_cast<int>(Game::Stage::StageNum)] =
	{
		0,
		0,
		0,
		0
	};

	const char* const kTimeFileName = "Data/Img/Result/ClearTimeNum/ClearTime.png";

	// 数字の画像ハンドル
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
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum9.png",
	};

	// ランクの画像ハンドル
	const char* const kRankImage[static_cast<int>(Result::Rank::RankNum)] =
	{
		"Data/Img/Result/Rank/S.png",
		"Data/Img/Result/Rank/A.png",
		"Data/Img/Result/Rank/B.png",
		"Data/Img/Result/Rank/C.png"
	};

	// 画像のデータ
	const char* const kResultImageName = "";
	const char* const kEndImageName = "";

	// 描画位置
	constexpr float kStageClearTimePosY = 150.0f;
	constexpr float kMaxComboCountPosY = 300.0f;
	constexpr float kTotalDamagePosY = 450.0f;
	constexpr float kRankPosY = 650.0f;

	// 初期の描画位置
	constexpr float kStartPosX = 1200.0f;

	// 目標の描画位置
	constexpr float kEndPosX = 160.0f;

	// イージング時間
	constexpr float kEasingTime = 60.0f;
	constexpr float kOneFrame = 1.0f;

	// リザルト画面を出現させるまでの時間
	constexpr int kResultTime = 250;

	// リザルト画面の大きさ
	constexpr int kResultImageSizeX = 1080;
	constexpr int kResultImageSizeY = 702;
	
	// リザルト画面の描画位置
	constexpr int kResultImagePosX = 50;
	constexpr int kResultImagePosY = 300;
	
	// ランクの描画位置
	constexpr int kRankImagePosX = 740;
	constexpr int kRankImagePosY = 300;

	// ランク画像のアルファ値の増加量
	constexpr int kRankAlphaAdd = 8;

	// ランク用のSEを鳴らすまでの時間
	constexpr int kRankSound = 30;
}

Result::Result(int stageClearTime, Game::Stage stage):
	m_timeImageH(-1),
	m_clearTime(stageClearTime / 60),
	m_isEnd(false),
	m_clearTimePos{kStartPosX,kStageClearTimePosY},
	m_rankPos{kStartPosX,kRankPosY},
	m_rank(Result::Rank::RankNum)
{
	/*ポインタ作成*/
	m_pResultTime = std::make_shared<Time>(kResultTime);
	

	// ランク計算
	CalcRank();

	// リザルト画像の生成
	m_timeImageH = LoadGraph(kTimeFileName);

	// 数字の画像ハンドルロード
	for (int i = 0; i < m_timeNumH.size(); i++)
	{
		m_timeNumH[i] = LoadGraph(kMyTimeNumFileName[i]);
	}
	// ランクの画像ハンドルロード
	for (int i = 0; i < m_rankH.size(); i++)
	{
		m_rankH[i] = LoadGraph(kRankImage[i]);
	}

}

Result::~Result()
{
	// リザルト画面のデリート
	DeleteGraph(m_timeImageH);
	for (int i = 0; i < m_timeNumH.size(); i++)
	{
		DeleteGraph(m_timeNumH[i]);
	}
	for (int i = 0; i < m_rankH.size(); i++)
	{
		DeleteGraph(m_rankH[i]);
	}
}

void Result::Update()
{
	// リザルト画面を出現させるまで
	if (!m_pResultTime->Update())return;

}

void Result::Draw()
{
	/*タイム計算*/
	// 分数
	int clearMinutesTime = m_clearTime / 60;
	int minutesTimeFirst = clearMinutesTime / 10;	// 一の位
	int minutesTimeSecond = clearMinutesTime % 10;	// 十の位
	// 秒数
	int clearSecondTime = m_clearTime % 60;
	int secondTimeFirst = clearSecondTime / 10;		// 一の位
	int secondTimeSecond = clearSecondTime % 10;	// 十の位

	// クリアタイムの描画
	DrawRotaGraph(200, 300,
		0.5f, 0.0f,
		m_timeNumH[minutesTimeFirst], true);
	DrawRotaGraph(350, 300,
		0.5f, 0.0f,
		m_timeNumH[minutesTimeSecond], true);
	DrawRotaGraph(650, 300,
		0.5f, 0.0f,
		m_timeNumH[secondTimeFirst], true);
	DrawRotaGraph(800, 300,
		0.5f, 0.0f,
		m_timeNumH[secondTimeSecond], true);

	DrawRotaGraph(500, 300,
		0.5f, 0.0f,
		m_timeImageH, true);

	// ランクの描画
	DrawRotaGraph(500, 750,
		0.8f, 0.0f,
		m_rankH[0], true);

	// ランキングの描画

#ifdef _DEBUG

	DrawFormatString(0, 20, 0xffffff, "クリアタイム：%d分%d秒", clearMinutesTime, clearSecondTime);

#endif // _DEBUG
}

void Result::CalcRank()
{
}