#pragma once
#include "../Util/Game.h"

#include <memory>
#include <functional>

class Input;
class ObjectManager;
class CountTime;

class StageSceneManager
{
public:

	enum class SceneType
	{
		Counddown,		// 最初のカウントダウン
		Main,			// メイン
		Clear,			// クリア
	};
public:
	StageSceneManager(Game::Stage stageKind);
	virtual ~StageSceneManager();

	void Init();

	void Update(Input& input);
	void Draw();

	void AttachGameClear(std::function<void(void)> gameClear);

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
	int GetGameClearTime() const{return m_gameClearTime; }

private:	// 関数
	/// <summary>
	/// カウントダウン更新
	/// </summary>
	void CountdownUpdate(Input& input);
	/// <summary>
	/// メイン更新
	/// </summary>
	void MainUpdate(Input& input);
	/// <summary>
	///	クリア更新
	/// </summary>
	void ClearUpdate(Input& input);

	/// <summary>
	/// カウントダウン描画
	/// </summary>
	void CountdownDraw();
	/// <summary>
	/// メイン描画
	/// </summary>
	void MainDraw();
	/// <summary>
	/// クリア描画
	/// </summary>
	void ClearDraw();

private:	// 変数
	int m_gameClearTime ;		// クリアタイム
	bool m_isGameClear;			// ゲームをクリアしたかどうか
	bool m_isPlayClearSE;			// クリアSEをならしたかどうか
	
	Game::Stage m_stageKind;	// ステージの種類

	SceneType m_sceneType;		// シーンタイプ

	std::shared_ptr<ObjectManager> m_pObjectManager;	// オブジェクトマネージャークラスのポインタ
	std::shared_ptr<CountTime> m_pCountTime;		// 秒数カウントのポインタ

	std::function<void(void)> m_gameClear = [] {};	// ゲームクリア時の関数(空のラムダ式)
};

