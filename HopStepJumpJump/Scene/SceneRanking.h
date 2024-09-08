#pragma once
#include "SceneBase.h"

#include <array>
#include <vector>
#include <memory>

class Ranking;

class SceneRanking : public SceneBase
{
public:
	SceneRanking();
	virtual ~SceneRanking();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
	virtual SceneKind GetSceneKind() { return SceneKind::Ranking; }

private:
	void RankTimeDraw(int ranking);

private:
	int m_backgroundH;	// 背景画像ハンドル
	int m_textBoxH;		// テキストボックス画像ハンドル
	int m_buttonH;		// ボタン画像ハンドル
	bool m_isStage1;	// ステージ1のランキングかどうか



	std::array<int, 11> m_rankingTimeNumH{};	// ランキングタイムの画像ハンドル
	std::array<int, 3> m_rankingH{};			// ランキング画像ハンドル

	std::vector<int> m_stage1Ranking{};
	std::vector<int> m_stage2Ranking{};

	std::shared_ptr<Ranking> m_pRanking;

};

