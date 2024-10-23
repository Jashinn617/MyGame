﻿#pragma once

/// <summary>
/// 一定タイムが経過しているかを返すクラス
/// </summary>
class Time
{
public:		// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="rimitTime">判定したいタイム</param>
	Time(int rimitTime);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Time();

	/// <summary>
	/// タイムリセット
	/// </summary>
	void Reset();

	/// <summary>
	/// タイム更新
	/// </summary>
	/// <returns>リミット時間を超えているかどうか</returns>
	bool Update();

private:	// 変数
	int m_time;			// 経過時間
	int m_rimitTime;	// リミット時間
};

