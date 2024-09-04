#pragma once
#include "../Util/Game.h"

#include <memory>
#include <vector>
#include <array>
#include <functional>

class Input;
class ObjectManager;
class CountTime;
class Ranking;
class Time;

class StageSceneManager
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
	StageSceneManager(Game::Stage stageKind);
	virtual ~StageSceneManager();

	void Init();

	void Update(Input& input);
	void Draw();

	void SetGameClear();

	/// <summary>
	/// ステージの取得
	/// </summary>
	/// <returns>ステージの種類</returns>
	Game::Stage GetStageKind() const { return m_stageKind; }
	const std::shared_ptr<ObjectManager> GetObjectManager() { return m_pObjectManager; }
	/// <summary>
	/// ゲームクリア時間の取得
	/// </summary>
	/// <returns></returns>
	int GetGameClearTime() const{return m_clearTime; }

	/// <summary>
	/// ゲームクリアかどうか
	/// </summary>
	/// <returns></returns>
	bool IsGameClear()const { return m_isGameClear; }

private:	// 関数
	void ClearUpdate();
	void ClearDraw();

	void ImageLoad();
	void ImageDelete();

	void TextDraw();
	void TimeDraw();
	void RankingDraw();
	void RankDraw();
	void RankTimeDraw(int ranking);
	void MyRankTimeDraw(int ranking);
	void ButtonDraw();

private:	// 変数
	int m_clearTime;			// クリア時間
	bool m_isGameClear;			// ゲームをクリアしたかどうか

	bool m_isFall;				// 落下中か
	bool m_isMyRank;			// 自分のタイムが反映されているか

	int m_minusPosY;				// 引くY座標

	std::array<int, 11> m_myTimeNumH{};	// 自身のクリアタイムの画像ハンドル
	std::array<int, 11> m_rankingTimeNumH{};	// ランキングのタイムの画像ハンドル
	std::array<int, 4> m_rankH{};			// ランク画像ハンドル
	std::array<int, 3> m_textH{};	// テキスト画像ハンドル
	std::array<int, 3> m_rankingH{};	// ランキング画像ハンドル
	std::array<int, 2> m_textBoxH{};	// テキストボックス画像ハンドル
	std::array<int, 2> m_buttonH{};		// ボタンの画像ハンドル

	Rank m_rank;			// ランク
	
	std::vector<int> m_ranking{};	// ランキング
	Game::Stage m_stageKind;	// ステージの種類

	std::shared_ptr<ObjectManager> m_pObjectManager;	// オブジェクトマネージャークラスのポインタ
	std::shared_ptr<CountTime> m_pCountTime;		// 秒数カウントのポインタ
	std::shared_ptr<Time> m_pImageDrawTime;		// 画像が表示されるまでの時間
	std::shared_ptr<Time> m_pStageClearSETime;	// ステージクリア時のサウンドの開始時間
	std::shared_ptr<Ranking> m_pRanking;	// ランキング

};

