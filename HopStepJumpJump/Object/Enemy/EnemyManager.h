#pragma once
#include "../../Util/Game.h"

#include <vector>
#include <memory>
#include <array>

class SpownEnemy;
class ObjectManager;

class EnemyManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	/// <param name="pObjectManager">オブジェクトマネージャー</param>
	EnemyManager(Game::StageKind stageKind, ObjectManager* pObjectManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	ObjectManager* m_pObjectManager;		// オブジェクトマネージャーポインタ
	std::shared_ptr<SpownEnemy> m_pSpown;	// スポーンエネミーポインタ
};
