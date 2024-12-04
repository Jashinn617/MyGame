#include "SceneSelect.h"

#include <string>
#include <cassert>

namespace
{
	constexpr int kBackImgNum = 9;		// 背景画像数
	constexpr int kStopBackNum = 3;		// 動かない背景の数

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

SceneSelect::SceneSelect()
{
	/*画像のロード*/
	for (int i = 0; i < kBackImgNum; i++)
	{
		m_backH.push_back(LoadGraph(kBackPath[i].c_str()));
		// ロードに失敗したら止める
		assert(m_backH[i] != -1);
	}
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
	/*手前側に来るほどスクロールが早くなる*/

	// 動かない背景
	for (int i = 0; i < kStopBackNum; i++)
	{
		DrawGraph(0, 0, m_backH[i], true);
	}
}
