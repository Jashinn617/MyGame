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
	int GetGameClearTime() const{return m_gameClearTime; }

	/// <summary>
	/// ゲームクリアかどうか
	/// </summary>
	/// <returns></returns>
	bool IsGameClear()const { return m_isGameClear; }

private:	// 変数
	int m_gameClearTime ;		// クリアタイム
	bool m_isGameClear;			// ゲームをクリアしたかどうか
	
	Game::Stage m_stageKind;	// ステージの種類

	std::shared_ptr<ObjectManager> m_pObjectManager;	// オブジェクトマネージャークラスのポインタ
	std::shared_ptr<CountTime> m_pCountTime;		// 秒数カウントのポインタ
};

