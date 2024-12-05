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

	constexpr int kMaxCursorCount = 2;		// カーソルカウント最大値

	constexpr int kStageSelectpBoxPosX = Game::kScreenWidth * 0.28f;		// ステージ選択ボックス座標X
	constexpr int kStageSelectpBoxPosY = Game::kScreenHeight * 0.32f;		// ステージ選択ボックス座標Y
	constexpr int kGearBoxPosX = Game::kScreenWidth * 0.76f;				// 装備ボックス座標X
	constexpr int kGearBoxPosY = Game::kScreenHeight * 0.18f;				// 装備ボックス座標Y
	constexpr int kOptionBoxPosX = Game::kScreenWidth * 0.65f;				// オプションボックス座標X
	constexpr int kOptionBoxPosY = Game::kScreenHeight * 0.47f;				// オプションボックス座標Y
	constexpr int kGameEndBoxPosX = Game::kScreenWidth * 0.87f;				// ゲーム終了ボックス座標X
	constexpr int kGameEndBoxPosY = Game::kScreenHeight * 0.47f;			// ゲーム終了ボックス座標Y
	constexpr int kDescriptionBoxPosX = Game::kScreenWidth * 0.02f;			// 説明文ボックス座標X
	constexpr int kDescriptionBoxPosY = Game::kScreenHeight * 0.65f;		// 説明文ボックス座標Y
	constexpr int kButtonPosX = Game::kScreenWidth * 0.8f;					// ボタン座標X
	constexpr int kSelectButtonPosY = Game::kScreenHeight * 0.65f;			// 選択ボタン座標Y
	constexpr int kDecisionButtonPosY = Game::kScreenHeight * 0.8f;			// 決定ボタン座標Y

	constexpr double kNormalBoxExtRate = 1.0;								// 通常時ボックス拡大率

	constexpr double kBoxSinSpeed = 0.07;									// ボックス拡縮速度
	constexpr double kBoxAnimSwing = 0.03;									// ボックス拡縮幅

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

SceneSelect::SceneSelect() :
	m_scrollXBack(0),
	m_scrollXMiddle(0),
	m_scrollXFront(0),
	m_cursorCount(0),
	m_boxSinCount(0.0),
	m_expansionBoxExtRate(0.0),
	m_stageSelectBoxExtRate(0.0),
	m_gearBoxExtRate(0.0),
	m_optionBoxExtRate(0.0),
	m_gameEndBoxExtRate(0.0),
	m_isCursorUp(true),
	m_nextScene(nullptr)
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
	/*処理無し*/
}

std::shared_ptr<SceneBase> SceneSelect::Update()
{
	m_nextScene = shared_from_this();

	// カーソル更新
	UpdateCursor();

	// ボックス更新
	UpdateBox();

	// スクロール値の更新
	m_scrollXBack += kScrollSpeedBack;
	m_scrollXMiddle += kScrollSpeedMiddle;
	m_scrollXFront += kScrollSpeedFront;

	return m_nextScene;
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
	// 左ボタンが押されたらカウントを減らす
	if (Pad::IsTrigger(PAD_INPUT_LEFT)) m_cursorCount--;
	// 右ボタンが押されたらカウントを増やす
	else if (Pad::IsTrigger(PAD_INPUT_RIGHT)) m_cursorCount++;
	
	// カーソルをループさせる
	// カーソルが上下どちらにいるかでループさせる値が変わる
	if (m_isCursorUp)
	{
		if (m_cursorCount > kMaxCursorCount - 1) m_cursorCount = 0;
		if (m_cursorCount < 0) m_cursorCount = kMaxCursorCount - 1;
	}
	else
	{
		if (m_cursorCount > kMaxCursorCount) m_cursorCount = 0;
		if (m_cursorCount < 0) m_cursorCount = kMaxCursorCount;
	}
	

	// 上下ボタンが押されたら上下を入れ替える
	if (Pad::IsTrigger(PAD_INPUT_UP) || Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_isCursorUp = !m_isCursorUp;
	}
}

void SceneSelect::UpdateBox()
{
	// 選択中ボックス拡縮処理
	m_boxSinCount += kBoxSinSpeed;
	m_expansionBoxExtRate = sinf(m_boxSinCount) * kBoxAnimSwing;

	// カーソルカウントが0の場合はステージ選択ボックスを選択している
	if (m_cursorCount == 0)
	{
		m_stageSelectBoxExtRate = kNormalBoxExtRate + m_expansionBoxExtRate;
		m_gearBoxExtRate = kNormalBoxExtRate;
		m_optionBoxExtRate = kNormalBoxExtRate;
		m_gameEndBoxExtRate = kNormalBoxExtRate;

		m_isCursorUp = true;
	}
	else if (m_cursorCount == 1)
	{
		// カーソルが上だった場合は装備ボックスを選択している
		if (m_isCursorUp)
		{
			m_stageSelectBoxExtRate = kNormalBoxExtRate;
			m_gearBoxExtRate = kNormalBoxExtRate + m_expansionBoxExtRate;
			m_optionBoxExtRate = kNormalBoxExtRate;
			m_gameEndBoxExtRate = kNormalBoxExtRate;
		}
		// 下だった場合はオプションボックスを選択している
		else
		{
			m_stageSelectBoxExtRate = kNormalBoxExtRate;
			m_gearBoxExtRate = kNormalBoxExtRate;
			m_optionBoxExtRate = kNormalBoxExtRate + m_expansionBoxExtRate;
			m_gameEndBoxExtRate = kNormalBoxExtRate;
		}
	}
	else
	{
		m_stageSelectBoxExtRate = kNormalBoxExtRate;
		m_gearBoxExtRate = kNormalBoxExtRate;
		m_optionBoxExtRate = kNormalBoxExtRate;
		m_gameEndBoxExtRate = kNormalBoxExtRate + m_expansionBoxExtRate;

		// Aボタンが押されたらゲーム終了
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			m_nextScene = nullptr;
		}
	}
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
	DrawRotaGraph(kStageSelectpBoxPosX, kStageSelectpBoxPosY,
		m_stageSelectBoxExtRate, 0.0,
		m_stageSelectBoxH, true);
	// 装備
	DrawRotaGraph(kGearBoxPosX, kGearBoxPosY,
		m_gearBoxExtRate, 0.0,
		m_gearBoxH, true);
	// オプション
	DrawRotaGraph(kOptionBoxPosX, kOptionBoxPosY,
		m_optionBoxExtRate, 0.0,
		m_optionBoxH, true);
	// ゲーム終了
	DrawRotaGraph(kGameEndBoxPosX, kGameEndBoxPosY,
		m_gameEndBoxExtRate, 0.0,
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
