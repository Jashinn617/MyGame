#pragma once
#include "../Util/Game.h"

#include <memory>
#include <list>
#include <functional>

class EnemyBase;
class ItemBase;
class ObjectBase;
class Player;
class Field;
class Camera;
class EnemyManager;
class ItemManager;
class Collision;
class SkyDome;
class Time;
class ToonShader;
class ShadowMapShader;

class ObjectManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stage">ステージの種類</param>
	ObjectManager(Game::Stage stageKind);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ObjectManager();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// オブジェクトの追加
	/// </summary>
	/// <typeparam name="T">ObjectBaseを継承し型名</typeparam>
	/// <param name="pObj">何のオブジェクトを追加するか</param>
	template <class T>
	void AddObject(T* pObj)
	{
		m_pObject.push_back(pObj);
		m_pObject.back()->SetMain(this);
	}

	/// <summary>
	/// プレイヤーが存在するかどうか
	/// </summary>
	/// <returns>存在フラグ</returns>
	bool IsPlayerExist();

	/// <summary>
	/// 敵の数の取得
	/// </summary>
	/// <returns>敵の数</returns>
	int GetItemNum()const;

	/// <summary>
	/// ゲームをクリアしたかどうか
	/// </summary>
	/// <returns>クリアフラグ</returns>
	bool IsGameClear()const { return m_isGameClear; }

	/// <summary>
	/// ステージが終了したかどうか
	/// </summary>
	/// <returns>ステージ終了フラグ</returns>
	bool IsStageEnd()const { return m_isStageEnd; }

	/// <summary>
	/// オブジェクトのステージ終了処理が終わったかどうか
	/// </summary>
	/// <returns>ステージ終了フラグ</returns>
	bool IsObjStageEnd();

	/// <summary>
	/// プレイヤーポインタの取得
	/// </summary>
	/// <returns>プレイヤーポインタ</returns>
	Player* const GetPlayer();

	/// <summary>
	/// エネミーマネージャーポインタの取得
	/// </summary>
	/// <returns>エネミーマネージャーポインタ</returns>
	std::shared_ptr<EnemyManager> const GetEnemyManager() { return m_pEnemyManager; }

	/// <summary>
	/// 強制的にゲームクリアにする
	/// </summary>
	void SetGameClear();

private:	// 関数
	/// <summary>
	/// ステージクリア時の更新処理
	/// </summary>
	void GameClearUpdate();

	/// <summary>
	/// ゲーム終了時の更新処理
	/// </summary>
	void GameEndUpdate();

private:	// 変数
	bool m_isGameClear;		// ゲームをクリアしたか
	bool m_isStageEnd;		// ステージが終了したか

	std::shared_ptr<Collision> m_pCollision;				// 当たり判定
	std::shared_ptr<SkyDome> m_pSkyDome;					// スカイドーム
	std::shared_ptr<EnemyManager> m_pEnemyManager;			// エネミーマネージャー
	std::shared_ptr<ItemManager> m_pItemManager;			// アイテムマネージャー
	std::shared_ptr<ToonShader> m_pToonShader;				// トゥーンシェーダ
	std::shared_ptr<ShadowMapShader> m_pShadowMapShader;	// シャドウマップ
	std::list<ObjectBase*> m_pObject;						// オブジェクト
	std::shared_ptr<Time> m_gameEndTime;					// ゲーム終了してからの時間
};