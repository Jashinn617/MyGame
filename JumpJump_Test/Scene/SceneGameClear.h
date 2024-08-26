#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "../Util/Game.h"

#include <memory>
#include <vector>
#include <array>

class Input;
class StageSceneManager;
class Time;
class Result;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear();
	SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager, Game::Stage stageKind);
	~SceneGameClear();

	virtual void Init() override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	// シーンの種類の取得
	virtual SceneKind GetSceneKind() { return SceneKind::GameClear; }

private:	// 関数
	void ChangeMainScene();
	void ChangeTitleScene();

private:	// 変数
	int m_backgroundH;		// 画像ハンドル
	int m_stageClearTime;	// ステージのクリアタイム
	bool m_isSceneEnd;	// シーンが終了したかどうか
	bool m_isNextScene;	// 次のシーンに移動可能かどうか

	std::array<int, 10> m_myTimeNumH{};	// 自身のクリアタイムの画像ハンドル
	std::array<int, 10> m_rankingTimeNumH{};	// ランキングのタイムの画像ハンドル
	std::array<int, 3> m_textH{};	// テキスト画像ハンドル
	std::array<int, 3> m_rankingH{};	// ランキング画像ハンドル
	std::array<int, 2> m_textBoxH{};	// テキストボックス画像ハンドル
	std::array<int, 2> m_buttonH{};		// ボタンの画像ハンドル


	std::vector<int> m_ranking{};	// ランキング
	Game::Stage m_stageKind;		// ステージの種類

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;
	std::shared_ptr<Time> m_pImageDrawTime;
	std::shared_ptr<Result> m_pResult;
};

