#pragma once
#include "../Util/Game.h"

#include <memory>
#include <functional>

class ObjectManager;

class StageSceneManager
{
public:
	StageSceneManager(Game::Stage stageKind);
	virtual ~StageSceneManager();

	void Init();

	void Update();
	void Draw();

	void AttachGameClear(std::function<void(void)> gameClear);

	void SetGameClear();

	Game::Stage GetStageKind() const { return m_stageKind; }
	const std::shared_ptr<ObjectManager> GetObjectManager() { return m_pObjectManager; }
	int GetGameClearTime() const{return m_gameClearTime; }


private:	// 変数
	int m_gameClearTime ;		// クリアタイム
	bool m_isGameClear;			// ゲームをクリアしたかどうか
	Game::Stage m_stageKind;	// ステージの種類
	std::shared_ptr<ObjectManager> m_pObjectManager;	// オブジェクトマネージャークラスのポインタ

	std::function<void(void)> m_gameClear = [] {};	// ゲームクリア時の関数(ラムダ式)

};

