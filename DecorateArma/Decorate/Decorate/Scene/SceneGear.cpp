#include "SceneGear.h"

#include "../Object/Player/Gear.h"

#include "../Utility/Pad.h"

#include <cassert>

namespace
{
	constexpr int kTextImgNum = 15;					// テキストの画像数
	// テキスト画像名
	const char* kImgNamePath[kTextImgNum] = 
	{
		"Data/Image/Gear/Text/HPUPS.png",
		"Data/Image/Gear/Text/HPUPM.png",
		"Data/Image/Gear/Text/HPUPL.png",
		"Data/Image/Gear/Text/MATKUPS.png",
		"Data/Image/Gear/Text/MATKUPM.png",
		"Data/Image/Gear/Text/MATKUPL.png",
		"Data/Image/Gear/Text/SATKUPS.png",
		"Data/Image/Gear/Text/SATKUPM.png",
		"Data/Image/Gear/Text/SATKUPL.png",
		"Data/Image/Gear/Text/DEFUPS.png",
		"Data/Image/Gear/Text/DEFUPM.png",
		"Data/Image/Gear/Text/DEFUPL.png",
		"Data/Image/Gear/Text/AllUPS.png",
		"Data/Image/Gear/Text/AllUPM.png",
		"Data/Image/Gear/Text/AllUPL.png",
	};
	// 数字画像名
	const char* kNumPath[10] =
	{
		"Data/Image/Gear/Number/0.png",
		"Data/Image/Gear/Number/1.png",
		"Data/Image/Gear/Number/2.png",
		"Data/Image/Gear/Number/3.png",
		"Data/Image/Gear/Number/4.png",
		"Data/Image/Gear/Number/5.png",
		"Data/Image/Gear/Number/6.png",
		"Data/Image/Gear/Number/7.png",
		"Data/Image/Gear/Number/8.png",
		"Data/Image/Gear/Number/9.png",
	};
	const char* kMulMarkPath = "Data/Image/Gear/MulMark.png";	// ×マーク画像ハンドル
	const char* kCursorPath = "Data/Image/Gear/CursorBox.png";	// カーソル画像ハンドル

	constexpr int kGearLeftPosX = 200;						// 装備品名左側座標
	constexpr int kGearRightPosX = 800;						// 装備品名右側座標
	constexpr int kMulMarkPosX = 400;						// ×マーク座標
	constexpr int kNumSecondPosX = kMulMarkPosX + 50;		// 十の位数字座標
	constexpr int kNumFirstPosX = kNumSecondPosX + 30;		// 一の位数字座標
	constexpr int kCursorPosX = -20;						// カーソルX座標
	constexpr int kMulMarkPosY = 10;						// ×マークY座標調整
	constexpr int kGearStartPosY = 100;						// 装備品名Y座標の最初の位置
	constexpr int kGearIntervalPosY = 80;					// 装備品名Y座標の間隔
	constexpr int kCursorPosY = -10;						// カーソルY座標
}

SceneGear::SceneGear():
	m_isCursorLeft(true),
	m_pGear(std::make_shared<Gear>())
{
	// 画像のロード
	for (int i = 0; i < kTextImgNum; i++)
	{
		m_gearH.push_back(LoadGraph(kImgNamePath[i]));
		// 画像が無ければ止める
		assert(m_gearH[i] != -1);
	}
	for (int i = 0; i < 10; i++)
	{
		m_numH.push_back(LoadGraph(kNumPath[i]));
		assert(m_numH[i] != -1);
	}

	m_mulMarkH = LoadGraph(kMulMarkPath);
	assert(m_mulMarkH != -1);
	m_cursorH = LoadGraph(kCursorPath);
	assert(m_cursorH != -1);
}

SceneGear::~SceneGear()
{
	// 画像のデリート
	for (auto& img : m_gearH)
	{
		DeleteGraph(img);
	}
	for (auto& num : m_numH)
	{
		DeleteGraph(num);
	}
	DeleteGraph(m_mulMarkH);
	DeleteGraph(m_cursorH);
}

void SceneGear::Init()
{
}

std::shared_ptr<SceneBase> SceneGear::Update()
{
	// カーソル更新
	UpdateCursor();

	return shared_from_this();
}

void SceneGear::Draw()
{
	// テキスト描画
	DrawGearText();
	// 装備品数描画
	DrawGearNum();
	// カーソル描画
	DrawCursor();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "装備画面");
#endif // _DEBUG

}

void SceneGear::End()
{
}

void SceneGear::UpdateCursor()
{
	// 左右ボタンを押したらカーソルが左右に動く
	if (Pad::IsTrigger(PAD_INPUT_LEFT) || Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		// 左右切り替え
		m_isCursorLeft = !m_isCursorLeft;
	}
}

void SceneGear::DrawGearText()
{
	int leftPosY = kGearStartPosY;	// 左側Y座標
	int rightPosY = kGearStartPosY;	// 右側Y座標

	// テキスト描画
	for (int i = 0; i < m_gearH.size(); i++)
	{
		// iが偶数だった場合
		if (i % 2 == 0)
		{
			// 左に描画
			DrawGraph(kGearLeftPosX, leftPosY, m_gearH[i], true);
			// ×マーク描画
			DrawGraph(kGearLeftPosX + kMulMarkPosX, leftPosY + kMulMarkPosY,
				m_mulMarkH, true);
			// Y座標を足す
			leftPosY += kGearIntervalPosY;
		}
		// iが奇数だった場合
		else
		{
			// 右に描画
			DrawGraph(kGearRightPosX, rightPosY, m_gearH[i], true);
			// ×マーク描画
			DrawGraph(kGearRightPosX + kMulMarkPosX, rightPosY + kMulMarkPosY,
				m_mulMarkH, true);
			// Y座標を足す
			rightPosY += kGearIntervalPosY;
		}
	}
}

void SceneGear::DrawGearNum()
{
	int leftPosY = kGearStartPosY;	// 左側Y座標
	int rightPosY = kGearStartPosY;	// 右側Y座標

	// 数字描画
	for (int i = 0; i < m_gearH.size(); i++)
	{
		// 数取得
		int gearNum = m_pGear->GetGearNum(i).num;

		int numFirst = gearNum % 10;	// 一の位
		int numSecond = gearNum / 10;	// 十の位

		// iが偶数だった場合
		if (i % 2 == 0)
		{
			// 左に描画
			// 一の位
			DrawGraph(kGearLeftPosX + kNumFirstPosX,
				leftPosY, m_numH[numFirst], true);
			// 十の位
			DrawGraph(kGearLeftPosX + kNumSecondPosX,
				leftPosY, m_numH[numSecond], true);
			// Y座標を足す
			leftPosY += kGearIntervalPosY;
		}
		// i が奇数だった場合
		else
		{
			// 右に描画
				// 一の位
			DrawGraph(kGearRightPosX + kNumFirstPosX,
				rightPosY, m_numH[numFirst], true);
			// 十の位
			DrawGraph(kGearRightPosX + kNumSecondPosX,
				rightPosY, m_numH[numSecond], true);

			// Y座標を足す
			rightPosY += kGearIntervalPosY;
		}
	}
}

void SceneGear::DrawCursor()
{
	// カーソルを左に描画
	if (m_isCursorLeft)
	{
		DrawGraph(kGearLeftPosX + kCursorPosX,
			kGearStartPosY + kCursorPosY, m_cursorH, true);
	}
	// カーソルを右に描画
	else
	{
		DrawGraph(kGearRightPosX + kCursorPosX,
			kGearStartPosY + kCursorPosY, m_cursorH, true);
	}
}
