#pragma once

#include <memory>
#include <array>

class CountGetItem
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="maxCount">カウントの最大値(初期のカギの数)</param>
	CountGetItem(int maxCount);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CountGetItem();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// カウントの追加
	/// </summary>
	void Add();

	/// <summary>
	/// カウントが最大値以上になっているかどうか
	/// </summary>
	/// <returns>カウントが最大値以上になっているか</returns>
	bool IsCountMax();

	/// <summary>
	/// 取得したアイテム数の取得
	/// </summary>
	/// <returns>取得アイテム数</returns>
	int GetGetItemCount()const { return m_getItemCount; }
	
private:
	int m_getItemCount;						// 取得アイテム数
	int m_maxItemNum;						// アイテムのの最大数
	std::array<int, 2> m_textH{};			// テキスト画像ハンドル
	std::array<int, 10>m_numberH{};			// 数字の画像ハンドル
};

