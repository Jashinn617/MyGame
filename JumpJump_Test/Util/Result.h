#pragma once
#include "../Util/Game.h"
#include "../Util/Vec2.h"

#include <memory>
#include <array>
#include <string>

class ExpansionImage;
class FadeImage;
class Time;
class ActionTime;

class Result
{
public:
	// ランク
	enum class Rank
	{
		S,
		A,
		B,
		C,
		RankNum,
	};

public:
	Result(int stageClearTime, Game::Stage stage);
	~Result();

	void Update();

	void Draw();

	/// <summary>
	/// リザルトが終了したかどうかの取得
	/// </summary>
	/// <returns></returns>
	bool IsEnd()const { return m_isEnd; }

private:	// 関数
	/// <summary>
	/// ランク計算
	/// </summary>
	void CalcRank();

private:	// 変数
	int m_timeImageH;		// リザルトの画像ハンドル
	std::array<int, 10> m_timeNumH{};	// 秒数の画像ハンドル
	std::array<int, 4> m_rankH{};

	int m_clearTime;		// ステージのクリア時間

	bool m_isEnd;			// リザルトを終了するかどうか
	
	std::string m_clearMinutesTimeStr;	// クリア時間(分)
	std::string m_clearSecondTimeStr;	// クリア時間(秒)

	Vec2 m_clearTimePos;	// クリア時間の表示位置
	Vec2 m_rankPos;			// ランクの位置

	Rank m_rank;			// ランク

	std::shared_ptr<Time> m_pResultTime;			// 画面を出現させるまでの時間
};

