#include "DxLib.h"
#include "CountGetItem.h"
#include "../../Util/Game.h"

namespace
{
	/*画像ファイルパス*/
	// テキスト
	const char* const kTextFileName[2] =
	{
		"Data/Img/ItemNum/ItemNumImg1.png",
		"Data/Img/ItemNum/ItemNumImg2.png",
	};
	// 数字
	const char* const kNumberFileName[10] =
	{
		"Data/Img/ItemNum/ItemNum0.png",
		"Data/Img/ItemNum/ItemNum1.png",
		"Data/Img/ItemNum/ItemNum2.png",
		"Data/Img/ItemNum/ItemNum3.png",
		"Data/Img/ItemNum/ItemNum4.png",
		"Data/Img/ItemNum/ItemNum5.png",
		"Data/Img/ItemNum/ItemNum6.png",
		"Data/Img/ItemNum/ItemNum7.png",
		"Data/Img/ItemNum/ItemNum8.png",
		"Data/Img/ItemNum/ItemNum9.png",
	};

	/*座標*/
	constexpr int kImagePosX1 = 820;		// テキスト画像1X
	constexpr int kImagePosX2 = 1150;		// テキスト画像2X
	constexpr int kNumberPosX = 1007;		// 数字(一桁時)
	constexpr int kNumberFirstPosX = 1056;	// 数字(二桁時一の位)X
	constexpr int kNumberSecondPosX = 960;	// 数字(二桁時十の位)X
	constexpr int kImgPosY = 100;			// 画像Y(全画像Y位置は統一)

	constexpr float kImgSize = 0.5f;	// 画像サイズ
	constexpr int kImgAlpha = 170;	// 画像の不透明度
}

CountGetItem::CountGetItem(int maxCount) :
	m_getItemCount(0),
	m_maxItemNum(maxCount)
{
	/*画像ロード*/
	// テキスト
	for (int i = 0; i < m_textH.size(); i++)
	{
		m_textH[i] = LoadGraph(kTextFileName[i]);
	}
	// 数字
	for (int i = 0; i < m_numberH.size(); i++)
	{
		m_numberH[i] = LoadGraph(kNumberFileName[i]);
	}
}

CountGetItem::~CountGetItem()
{
	/*画像デリート*/
	for (int i = 0; i < m_textH.size(); i++)
	{
		DeleteGraph(m_textH[i]);
	}
	for (int i = 0; i < m_numberH.size(); i++)
	{
		DeleteGraph(m_numberH[i]);
	}
}

void CountGetItem::Draw()
{
	// 残りアイテムの数
	int remainingItem = m_maxItemNum - m_getItemCount;

	// 残りのアイテムの数が0の場合は何も描画しない
	if (remainingItem <= 0)return;

	// テキスト画像の描画
	DrawRotaGraph(kImagePosX1, kImgPosY,
		kImgSize, 0.0f,
		m_textH[0], true);

	DrawRotaGraph(kImagePosX2, kImgPosY,
		kImgSize, 0.0f,
		m_textH[1], true);

	// 残りのアイテム数が一桁の時
	if (remainingItem < 10)
	{
		DrawRotaGraph(kNumberPosX, kImgPosY,
			kImgSize, 0.0f,
			m_numberH[remainingItem], true);
	}
	else // 残りのアイテム数が二桁の時
	{
		int numFirst = remainingItem % 10;	// 一の位
		int numSecond = remainingItem / 10;	// 十の位

		DrawRotaGraph(kNumberFirstPosX, kImgPosY,
			kImgSize, 0.0f,
			m_numberH[numFirst], true);
		DrawRotaGraph(kNumberSecondPosX, kImgPosY,
			kImgSize, 0.0f,
			m_numberH[numSecond], true);
	}

#ifdef _DEBUG
	// 残りアイテム数デバッグ表示
	DrawFormatString(0, 80, 0xffffff, "残りのアイテム数：%d", remainingItem);
#endif // _DEBUG
}

void CountGetItem::Add()
{
	/// <summary>
	/// カウントの追加
	/// カウントの最大値以上にはならないようにする
	/// </summary>
	m_getItemCount = min(m_getItemCount++, m_maxItemNum);
}

bool CountGetItem::IsCountMax()
{
	// カウントが最大値以上になっていた場合trueを返す
	if (m_getItemCount >= m_maxItemNum) return true;

	// そうでなければfalseを返す
	return false;
}
