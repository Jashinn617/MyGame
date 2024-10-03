#pragma once
#include "DxLib.h"
#include "../../Util/Game.h"

#include <vector>
#include <memory>
#include <array>

class SpownItem;
class ObjectManager;
class CountGetItem;

class ItemManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	/// <param name="pObjectManager"></param>
	ItemManager(Game::Stage stageKind, ObjectManager* pObjectManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemManager();

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

	/// <summary>
	/// アイテムの取得数の追加
	/// </summary>
	void AddGetNum();

	/// <summary>
	/// クリア状態かどうか
	/// </summary>
	/// <returns></returns>
	bool IsClear()const { return m_isClear; }

private:
	bool m_isSpown;									// アイテムを出現させるかどうか
	bool m_isClear;									// クリアしたかどうか
	ObjectManager* m_pObjectManager;				// オブジェクトマネージャーのポインタ
	std::shared_ptr<CountGetItem> m_pCountGetItem;	// アイテムの取得数
	std::shared_ptr<SpownItem> m_pSpown;			// アイテムの出現
};

