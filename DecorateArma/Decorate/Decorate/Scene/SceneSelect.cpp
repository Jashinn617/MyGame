#include "SceneSelect.h"

#include <string>
#include <cassert>

namespace
{
	constexpr int kBackImgNum = 9;		// 背景画像数
	constexpr int kStopBackNum = 3;		// 動かない背景の数
	constexpr int kBackBackNum = 2;		// 後ろの背景の数
	constexpr int kMiddleBackNum = 2;	// 真ん中の背景の数
	constexpr int kFrontBackNum = 2;	// 手前の背景の数

	constexpr int kIndexBackNum = 2;			// スクロールに必要な背景数
	constexpr int kScrollSpeedBack = 1;		// スクロール速度奥
	constexpr int kScrollSpeedMiddle = 2;	// スクロール速度真ん中
	constexpr int kScrollSpeedFront = 3;		// スクロール速度手前


	/*ファイルパス関係*/
	const std::string kSelectPath = "Data/Image/Select/";		// 画像ファイルパス
	// 背景画像パス
	const std::string kBackPath[kBackImgNum] =
	{
		kSelectPath + "Background/back1.png",
		kSelectPath + "Background/back2.png",
		kSelectPath + "Background/back3.png",
		kSelectPath + "Background/back4.png",
		kSelectPath + "Background/back5.png",
		kSelectPath + "Background/back6.png",
		kSelectPath + "Background/back7.png",
		kSelectPath + "Background/back8.png",
		kSelectPath + "Background/back9.png",
	};
}

SceneSelect::SceneSelect():
	m_scrollXBack(0),
	m_scrollXMiddle(0),
	m_scrollXFront(0)
{
	/*画像のロード*/
	for (int i = 0; i < kBackImgNum; i++)
	{
		m_backH.push_back(LoadGraph(kBackPath[i].c_str()));
		// ロードに失敗したら止める
		assert(m_backH[i] != -1);
	}

	// 背景画像サイズ取得
	GetGraphSize(m_backH[0], &m_backWidth, &m_backHeight);
}

SceneSelect::~SceneSelect()
{
	/*画像のデリート*/
	for (auto& img : m_backH)
	{
		DeleteGraph(img);
	}
}

void SceneSelect::Init()
{
}

std::shared_ptr<SceneBase> SceneSelect::Update()
{

	// スクロール値の更新
	m_scrollXBack += kScrollSpeedBack;
	m_scrollXMiddle += kScrollSpeedMiddle;
	m_scrollXFront += kScrollSpeedFront;

	return shared_from_this();
}

void SceneSelect::Draw()
{
	// 背景描画
	BackDraw();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Select");
#endif // _DEBUG
}

void SceneSelect::End()
{
}

void SceneSelect::BackDraw()
{
	// 動かない背景
	for (int i = 0; i < kStopBackNum; i++)
	{
		DrawGraph(0, 0, m_backH[i], true);
	}
	// 描画した背景数
	int drawBack = kStopBackNum;
	/*スクロール処理
	手前側に来るほどスクロールが早くなる*/
	// 後ろ
	int scroll = m_scrollXBack % m_backWidth;
	for (int i = 0; i < kBackBackNum; i++)
	{
		for (int index = 0; index < kIndexBackNum; index++)
		{
			DrawGraph(-scroll + index * m_backWidth,
				0, m_backH[drawBack + i], true);
		}
	}

	// 真ん中
	drawBack += kBackBackNum;
	scroll = m_scrollXMiddle % m_backWidth;
	for (int i = 0; i < kMiddleBackNum; i++)
	{
		for (int index = 0; index < kIndexBackNum; index++)
		{
			DrawGraph(-scroll + index * m_backWidth,
				0, m_backH[drawBack + i], true);
		}
	}

	// 手前
	drawBack += kMiddleBackNum;
	scroll = m_scrollXFront % m_backWidth;
	for (int i = 0; i < kFrontBackNum; i++)
	{
		for (int index = 0; index < kIndexBackNum; index++)
		{
			DrawGraph(-scroll + index * m_backWidth,
				0, m_backH[drawBack + i], true);
		}
	}
}
