#include "DxLib.h"
#include "CountTime.h"

#include "Game.h"

#include <assert.h>

namespace
{
	/*画像ファイルパス*/
	const char* const kColonFileName = "Data/Img/Time/Colon.png";	// コロン
	// 秒数
	const char* const kMyTimeNumFileName[10] =
	{
		 "Data/Img/Time/TimeNum0.png",
		 "Data/Img/Time/TimeNum1.png",
		 "Data/Img/Time/TimeNum2.png",
		 "Data/Img/Time/TimeNum3.png",
		 "Data/Img/Time/TimeNum4.png",
		 "Data/Img/Time/TimeNum5.png",
		 "Data/Img/Time/TimeNum6.png",
		 "Data/Img/Time/TimeNum7.png",
		 "Data/Img/Time/TimeNum8.png",
		 "Data/Img/Time/TimeNum9.png",
	};

	constexpr int kImagePosX1 = 960;		// コロン画像X座標
	constexpr int kImagePosY1 = 230;		// コロン画像Y座標
	constexpr int kMinutesFirstPosX = 864;	// 数字のX座標(一の位)
	constexpr int kMinutesFirstPosY = 230;	// 数字のY座標(一の位)
	constexpr int kMinutesSecondPosX = 748;	// 数字のX座標(十の位)
	constexpr int kMinutesSecondPosY = 230;	// 数字のY座標(十の位)
	constexpr int kSecondFirstPosX = 1171;	// 数字のX座標(一の位)
	constexpr int kSecondFirstPosY = 230;	// 数字のY座標(一の位)
	constexpr int kSecondSecondPosX = 1056;	// 数字のX座標(十の位)
	constexpr int kSecondSecondPosY = 230;	// 数字のY座標(十の位)

	constexpr float kImgSize = 0.5f;	// 画像サイズ
}

CountTime::CountTime():
	m_time(0),
	m_colonH(-1)
{
	/*画像ロード*/
	// ロード失敗時は止める
	m_colonH = LoadGraph(kColonFileName);
	assert(m_colonH != -1);
	for (int i = 0; i < m_numberH.size(); i++)
	{
		m_numberH[i] = LoadGraph(kMyTimeNumFileName[i]);
		assert(m_numberH[i] != -1);
	}
}

CountTime::~CountTime()
{
	/*画像デリート*/
	DeleteGraph(m_colonH);
	for (int i = 0; i < m_numberH.size(); i++)
	{
		DeleteGraph(m_numberH[i]);
	}
}

void CountTime::Update(int time)
{
	// タイム更新
	m_time = time;
}

void CountTime::Draw()
{
	// コロン描画
	DrawRotaGraph(kImagePosX1, kImagePosY1,
		kImgSize, 0.0f,
		m_colonH, true);

	// 現在の秒数計算
	int nowTime = m_time / 60;
	// 分数の計算と描画
	int minutesTime = nowTime / 60;
	int minutesTimeFirst = minutesTime % 10;	// 一の位
	int minutesTimeSecond = minutesTime / 10;	// 十の位

	// 分数描画
	DrawRotaGraph(kMinutesFirstPosX, kMinutesFirstPosY,
		kImgSize, 0.0f,
		m_numberH[minutesTimeFirst], true);
	DrawRotaGraph(kMinutesSecondPosX, kMinutesSecondPosY,
		kImgSize, 0.0f,
		m_numberH[minutesTimeSecond], true);

	// 秒数の計算と描画
	int secondTime = nowTime % 60;
	int secondTimeFirst = secondTime % 10;	// 一の位
	int secondTimeSecond = secondTime / 10;	// 十の位

	// 秒数描画
	DrawRotaGraph(kSecondFirstPosX, kSecondFirstPosY,
		kImgSize, 0.0f,
		m_numberH[secondTimeFirst], true);
	DrawRotaGraph(kSecondSecondPosX, kSecondSecondPosY,
		kImgSize, 0.0f,
		m_numberH[secondTimeSecond], true);
}
