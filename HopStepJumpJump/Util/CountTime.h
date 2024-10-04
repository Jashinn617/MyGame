#pragma once

#include <memory>
#include <array>

class CountTime
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CountTime();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CountTime();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="time">現在タイム</param>
	void Update(int time);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	int m_time;								// 現在の秒数
	int m_colonH;							// コロンの画像ハンドル
	std::array<int, 10> m_numberH{};		// 数字の画像ハンドル
};