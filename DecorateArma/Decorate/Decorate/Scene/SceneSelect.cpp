#include "SceneSelect.h"

#include "SceneGear.h"

#include "../Utility/Game.h"
#include "../Utility/Pad.h"

#include <string>
#include <cassert>

namespace
{
	constexpr int kBackImgNum = 9;		// 背景画像数
	constexpr int kStopBackNum = 3;		// 動かない背景の数
	constexpr int kBackBackNum = 2;		// 後ろの背景の数
	constexpr int kMiddleBackNum = 2;	// 真ん中の背景の数
	constexpr int kFrontBackNum = 2;	// 手前の背景の数

	constexpr int kIndexBackNum = 2;		// スクロールに必要な背景数
	constexpr int kScrollSpeedBack = 1;		// スクロール速度奥
	constexpr int kScrollSpeedMiddle = 2;	// スクロール速度真ん中
	constexpr int kScrollSpeedFront = 3;	// スクロール速度手前


	constexpr int kStageSelectpBoxPosX = Game::kScreenWidth * 0.03f;		// ステージ選択ボックス座標X
	constexpr int kStageSelectpBoxPosY = Game::kScreenHeight * 0.05f;		// ステージ選択ボックス座標Y
	constexpr int kGearBoxPosX = Game::kScreenWidth * 0.555f;				// 装備ボックス座標X
	constexpr int kGearBoxPosY = Game::kScreenHeight * 0.05f;				// 装備ボックス座標Y
	constexpr int kOptionBoxPosX = Game::kScreenWidth * 0.55f;			// オプションボックス座標X
	constexpr int kOptionBoxPosY = Game::kScreenHeight * 0.4f;			// オプションボックス座標Y
	constexpr int kGameEndBoxPosX = Game::kScreenWidth * 0.77f;			// ゲーム終了ボックス座標X
	constexpr int kGameEndBoxPosY = Game::kScreenHeight * 0.4f;			// ゲーム終了ボックス座標Y
	constexpr int kDescriptionBoxPosX = Game::kScreenWidth * 0.02f;		// 説明文ボックス座標X
	constexpr int kDescriptionBoxPosY = Game::kScreenHeight * 0.65f;		// 説明文ボックス座標Y
	constexpr int kButtonPosX = Game::kScreenWidth * 0.8f;				// ボタン座標X
	constexpr int kSelectButtonPosY = Game::kScreenHeight * 0.65f;		// 選択ボタン座標Y
	constexpr int kDecisionButtonPosY = Game::kScreenHeight * 0.8f;		// 決定ボタン座標Y

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
	const std::string kStageSelectBoxPath = kSelectPath + "Box/StageSelect.png";	// ステージ選択ボックスパス
	const std::string kGearBoxPath = kSelectPath + "Box/Gear.png";					// 装備ボックスパス
	const std::string kOptionBoxPath = kSelectPath + "Box/Option.png";				// オプションボックスパス
	const std::string kGameEndBoxPath = kSelectPath + "Box/GameEnd.png";			// ゲーム終了ボックスパス
	const std::string kDescriptionBoxPath = kSelectPath + "Box/Description.png";	// 説明文ボックスパス
	const std::string kSelectButtonPath = kSelectPath + "Box/Select.png";			// 選択ボタンパス
	const std::string kDecisionButtonPath = kSelectPath + "Box/Decision.png";		// 決定ボタンパス

}

SceneSelect::SceneSelect():
	m_scrollXBack(0),
	m_scrollXMiddle(0),
	m_scrollXFront(0),
	m_isCursorUp(true),
	m_isCursorLeft(true),
	m_isCursorGameEnd(false)
{
	/*画像のロード*/
	for (int i = 0; i < kBackImgNum; i++)
	{
		m_backH.push_back(LoadGraph(kBackPath[i].c_str()));
		// ロードに失敗したら止める
		assert(m_backH[i] != -1);
	}
	m_stageSelectBoxH = LoadGraph(kStageSelectBoxPath.c_str());
	assert(m_stageSelectBoxH != -1);
	m_gearBoxH = LoadGraph(kGearBoxPath.c_str());
	assert(m_gearBoxH != -1);
	m_optionBoxH = LoadGraph(kOptionBoxPath.c_str());
	assert(m_optionBoxH != -1);
	m_gameEndBoxH = LoadGraph(kGameEndBoxPath.c_str());
	assert(m_gameEndBoxH != -1);
	m_descriptionBoxH = LoadGraph(kDescriptionBoxPath.c_str());
	assert(m_decisionButtonH != -1);
	m_selectButtonH = LoadGraph(kSelectButtonPath.c_str());
	assert(m_selectButtonH != -1);
	m_decisionButtonH = LoadGraph(kDecisionButtonPath.c_str());
	assert(m_decisionButtonH != -1);

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
	DeleteGraph(m_stageSelectBoxH);
	DeleteGraph(m_gearBoxH);
	DeleteGraph(m_optionBoxH);
	DeleteGraph(m_gameEndBoxH);
	DeleteGraph(m_descriptionBoxH);
	DeleteGraph(m_selectButtonH);
	DeleteGraph(m_decisionButtonH);
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
	DrawBack();

	// ボックス描画
	DrawBox();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Select");
#endif // _DEBUG
}

void SceneSelect::End()
{
}

void SceneSelect::UpdateCursor()
{
	// 左右ボタンが押されたらカーソルの左右を切り替える
}

void SceneSelect::DrawBack()
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

void SceneSelect::DrawBox()
{
	// ステージ選択
	DrawGraph(kStageSelectpBoxPosX, kStageSelectpBoxPosY,
		m_stageSelectBoxH, true);
	// 装備
	DrawGraph(kGearBoxPosX, kGearBoxPosY,
		m_gearBoxH, true);
	// オプション
	DrawGraph(kOptionBoxPosX, kOptionBoxPosY,
		m_optionBoxH, true);
	// ゲーム終了
	DrawGraph(kGameEndBoxPosX, kGameEndBoxPosY,
		m_gameEndBoxH, true);
	// 説明文
	DrawGraph(kDescriptionBoxPosX, kDescriptionBoxPosY,
		m_descriptionBoxH, true);
	// 選択ボタン
	DrawGraph(kButtonPosX, kSelectButtonPosY,
		m_selectButtonH, true);
	// 決定ボタン
	DrawGraph(kButtonPosX, kDecisionButtonPosY,
		m_decisionButtonH, true);
}
