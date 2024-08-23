#include "DxLib.h"
#include "CountGetItem.h"
#include "../../Util/Game.h"
#include "../../Util/Font.h"

namespace
{
	const char* const kFileName = "";
	const char* const kNumberFileName[10] =
	{
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
	};

	constexpr int kAlpha = 170;	// 画像の透明度
	/*画像の座標*/
	constexpr int kImagePosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kImagePosY = 100;	// Y
	/*文字の座標*/
	constexpr int kStringPosX = static_cast<int>(Game::kScreenWidth * 0.5f - 75);	// X
	constexpr int kStringPosY = 85;	// Y
	/*数字の座標*/
	constexpr int kNumberPosX = static_cast<int>(Game::kScreenWidth * 0.5f + 17);	// X
	constexpr int kNumberPosY = 100;	// Y
	/*数字の座標(一の位)*/
	constexpr int kNumberFirstPosX = static_cast<int>(Game::kScreenWidth * 0.5f + 30);	// X
	constexpr int kNumberFirstPosY = 100;	// Y
	/*数字の座標(十の位)*/
	constexpr int kNumberSecondPosX = static_cast<int>(Game::kScreenWidth * 0.5f - 4);	// X
	constexpr int kNumberSecondPosY = 100;	// Y

	constexpr float kFontSize = 0.26f;	// 文字のサイズ
}

CountGetItem::CountGetItem(int maxCount):
	m_count(0),
	m_maxCount(maxCount)
{
	m_H = LoadGraph(kFileName);

	// 数字画像ハンドルロード
	for (int i = 0; i < m_numberH.size(); i++)
	{
		m_numberH[i] = LoadGraph(kNumberFileName[i]);
	}
}

CountGetItem::~CountGetItem()
{
	DeleteGraph(m_H);

	for (int i = 0; i < m_numberH.size(); i++)
	{
		DeleteGraph(m_numberH[i]);
	}
}

void CountGetItem::Draw()
{
	// 残りアイテムの数
	int remainingItem = m_maxCount - m_count;

	// 残りのアイテムの数が0の場合は何も描画しない
	if (remainingItem <= 0)return;

	// 残りのアイテム数の画像の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawRotaGraph(kImagePosX, kImagePosY,
		1.0f, 0.0f,
		m_H, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 残りのアイテム数が一桁の時
	if (remainingItem < 10)
	{
		DrawRotaGraph(kNumberPosX, kNumberPosY, 
			kFontSize, 0.0f,
			m_numberH[remainingItem], true);
	}
	else // 残りのアイテム数が二桁の時
	{
		int numFirst = remainingItem % 10;	// 一の位
		int numSecond = remainingItem / 10;	// 十の位

		DrawRotaGraph(kNumberFirstPosX, kNumberFirstPosY, 
			kFontSize, 0.0f, 
			m_numberH[numFirst], true);
		DrawRotaGraph(kNumberSecondPosX, kNumberSecondPosY, 
			kFontSize, 0.0f,
			m_numberH[numSecond], true);
	}

#ifdef _DEBUG
	DrawFormatString(0, 80, 0xffffff, "残りのアイテム数：%d", remainingItem);
#endif // _DEBUG
}

void CountGetItem::Add()
{
	m_count = min(m_count++, m_maxCount);
}

bool CountGetItem::IsCountMax()
{
	// カウントが最大値以上になっていた場合
	if (m_count >= m_maxCount) return true;

	return false;
}
