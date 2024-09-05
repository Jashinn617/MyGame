#include "DxLib.h"
#include "SceneSelect.h"

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

	constexpr float kMinUpBoxSize = 0.7f;
	constexpr float kMaxUpBoxSize = 0.7f;
	constexpr float kMinDownBoxSize = 0.6f;
	constexpr float kMaxDownBoxSize = 0.6f;
}

SceneSelect::SceneSelect() :
	m_backgroundH(-1),
	m_scrollX(0),
	m_backWidth(0),
	m_backHeight(0),
	m_isUp(true),
	m_isLeft(true),
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
		m_isUp = !m_isUp;
	}
	// 左右の入れ替え
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_isLeft = !m_isLeft;
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
		kMinUpBoxSize, 0.0f, m_SelectBoxH[0], true);
	DrawRotaGraph(kSelectBoxPosX2, kUpSelectBoxPosY,
		kMinUpBoxSize, 0.0f, m_SelectBoxH[1], true);

	DrawRotaGraph(kSelectBoxPosX1, kDownSelectBoxPosY,
		kMinDownBoxSize, 0.0f, m_SelectBoxH[2], true);
	DrawRotaGraph(kSelectBoxPosX2, kDownSelectBoxPosY,
		kMinDownBoxSize, 0.0f, m_SelectBoxH[3], true);
}
