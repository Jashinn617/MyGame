#include "DxLib.h"
#include "SceneSelect.h"
#include "SceneRanking.h"
#include "SceneStage.h"

#include "../Util/SoundManager.h"
#include "../Util/Input.h"
#include "../Util/Pad.h"
#include "../Util/Game.h"

#include <cassert>

namespace
{
	// 画像のファイルパス
	const char* const kBackGroundFineName = "Data/Img/Select/Background.png";

	// セレクトボックスファイルパス
	const char* const kSelectBoxFileName[4] =
	{
		"Data/Img/Select/Stage1Box.png",
		"Data/Img/Select/Stage1Box.png",
		"Data/Img/Select/OnlineRankingBox.png",
		"Data/Img/Select/GameEndBox.png"
	};

	constexpr int kIndexBackNum = 2;	// スクロールに必要な背景の数

	constexpr int kScrollSpeed = 1;		// スクロールのスピード

	/*セレクトボックスの座標*/
	constexpr int kSelectBoxPosX1 = 600;
	constexpr int kSelectBoxPosX2 = 1300;
	constexpr int kSelectBoxPosX3 = 700;
	constexpr int kSelectBoxPosX4 = 1100;
	constexpr int kUpSelectBoxPosY = 400;		// 上のセレクトボックスのY位置
	constexpr int kDownSelectBoxPosY = 820;		// 下のセレクトボックスのY位置

	constexpr float kUpBoxSize = 0.7f;
	constexpr float kDownBoxSize = 0.6f;

	constexpr float kBoxSinSpeed = 0.07f;	// ボックスが拡縮するスピード
	constexpr float kBoxAnimSwing = 0.03f;	// ボックスの拡縮幅
}

SceneSelect::SceneSelect() :
	m_backgroundH(-1),
	m_scrollX(0),
	m_backWidth(0),
	m_backHeight(0),
	m_isUp(true),
	m_isLeft(true),
	m_upBoxSize1(0.0f),
	m_upBoxSize2(0.0f),
	m_downBoxSize1(0.0f),
	m_downBoxSize2(0.0f),
	m_expansionBoxSize(0.0f),
	m_boxSinCount(0.0f),
	m_boxSinSize(0.0f),
	m_next(NextScene::My)
{
	/*画像ハンドルのロード*/
	m_backgroundH = LoadGraph(kBackGroundFineName);
	assert(m_backgroundH != -1);
	for (int i = 0; i < m_SelectBoxH.size(); i++)
	{
		m_SelectBoxH[i] = LoadGraph(kSelectBoxFileName[i]);
		assert(m_SelectBoxH[i] != -1);
	}

	// 背景画像のサイズの取得
	GetGraphSize(m_backgroundH, &m_backWidth, &m_backHeight);
}

SceneSelect::~SceneSelect()
{
	/*画像ハンドルのデリート*/
	DeleteGraph(m_backgroundH);
	for (int i = 0; i < m_SelectBoxH.size(); i++)
	{
		DeleteGraph(m_SelectBoxH[i]);
	}
}

void SceneSelect::Init()
{
	/*BGMを流す*/
	SoundManager::GetInstance().Play("SelectScene");
}

std::shared_ptr<SceneBase> SceneSelect::Update(Input& input)
{
	UpdateFade();

	// 背景のスクロール
	m_scrollX += kScrollSpeed;

	// 上下の選択の入れ替え
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		SoundManager::GetInstance().Play("Select");
		m_isUp = !m_isUp;
	}
	// 左右の入れ替え
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		SoundManager::GetInstance().Play("Select");
		m_isLeft = !m_isLeft;
	}

	SelectBoxUpdate();


	SelectUpdate();

	switch (m_next)
	{
	case SceneSelect::NextScene::My:
		return shared_from_this();
		break;

	case SceneSelect::NextScene::Stage1:
		return std::make_shared<SceneStage>(Game::Stage::Stage1);
		break;

	case SceneSelect::NextScene::Stage2:
		return std::make_shared<SceneStage>(Game::Stage::Stage2);
		break;

	case SceneSelect::NextScene::Ranking:
		//return std::make_shared<SceneRanking>();
		break;

	case SceneSelect::NextScene::End:
		DxLib_End();
		break;

	default:
		break;
	}

	return shared_from_this();
}

void SceneSelect::Draw()
{
	BackDraw();

	SelectBoxDraw();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Select");
	if (m_isUp) DrawFormatString(0, 20, 0x000000, "上");
	if (!m_isUp) DrawFormatString(0, 20, 0x000000, "下");
	if (m_isLeft) DrawFormatString(0, 40, 0x000000, "左");
	if (!m_isLeft) DrawFormatString(0, 40, 0x000000, "右");
	
#endif // _DEBUG   

	DrawFade();
}

void SceneSelect::End()
{
	SoundManager::GetInstance().DesignationStopSound("SelectScene");
}

void SceneSelect::SelectUpdate()
{
	// AボタンかBボタンが押されたら次のシーンに遷移する
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
	{
		// SEを鳴らす
		SoundManager::GetInstance().Play("Decide");

		if (m_isUp)	// 上の選択している
		{
			if (m_isLeft)	// 左を選択している
			{
				m_next = NextScene::Stage1;
			}
			else
			{
				m_next = NextScene::Stage2;
			}

		}
		else	// 下の選択をしている
		{
			if (m_isLeft)	// 左を選択している
			{
				m_next = NextScene::Ranking;
			}
			else
			{
				m_next = NextScene::End;
			}
		}
	}
	else
	{
		m_next = NextScene::My;
	}
}

void SceneSelect::SelectBoxUpdate()
{
	// 現在選ばれているボックスを拡縮する

	// 拡縮処理
	m_boxSinCount += kBoxSinSpeed;
	m_expansionBoxSize = sinf(m_boxSinCount) * kBoxAnimSwing;

	if (m_isUp)	// 上の選択している
	{
		if (m_isLeft)	// 左を選択している
		{
			m_upBoxSize1 = m_expansionBoxSize + kUpBoxSize;
			m_upBoxSize2 = kUpBoxSize;
			m_downBoxSize1 = kDownBoxSize;
			m_downBoxSize2 = kDownBoxSize;
		}
		else
		{
			m_upBoxSize1 = kUpBoxSize;
			m_upBoxSize2 = m_expansionBoxSize + kUpBoxSize;
			m_downBoxSize1 = kDownBoxSize;
			m_downBoxSize2 = kDownBoxSize;
		}

	}
	else	// 下の選択をしている
	{
		if (m_isLeft)	// 左を選択している
		{
			m_upBoxSize1 = kUpBoxSize;
			m_upBoxSize2 = kUpBoxSize;
			m_downBoxSize1 = m_expansionBoxSize + kDownBoxSize;
			m_downBoxSize2 = kDownBoxSize;
		}
		else
		{
			m_upBoxSize1 = kUpBoxSize;
			m_upBoxSize2 = kUpBoxSize;
			m_downBoxSize1 = kDownBoxSize;
			m_downBoxSize2 = m_expansionBoxSize + kDownBoxSize;
		}
	}

}

void SceneSelect::BackDraw()
{
	// 背景をスクロールさせる
	int scrollBack = m_scrollX % m_backWidth;
	for (int index = 0; index < kIndexBackNum; index++)
	{
		DrawGraph(-scrollBack + index * m_backWidth,
			0, m_backgroundH, true);
	}
}

void SceneSelect::SelectBoxDraw()
{
	DrawRotaGraph(kSelectBoxPosX1, kUpSelectBoxPosY,
		m_upBoxSize1, 0.0f, m_SelectBoxH[0], true);
	DrawRotaGraph(kSelectBoxPosX2, kUpSelectBoxPosY,
		m_upBoxSize2, 0.0f, m_SelectBoxH[1], true);

	DrawRotaGraph(kSelectBoxPosX1, kDownSelectBoxPosY,
		m_downBoxSize1, 0.0f, m_SelectBoxH[2], true);
	DrawRotaGraph(kSelectBoxPosX2, kDownSelectBoxPosY,
		m_downBoxSize2, 0.0f, m_SelectBoxH[3], true);
}
