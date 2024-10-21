#pragma once

#include "../Utility/Game.h"

#include <memory>
#include <list>

class ObjectBase;
class Collision;
class Player;
class ToonShader;
class ShadowMapShader;

class ObjectManager
{
public:		// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	ObjectManager(Game::StageKind stageKind);

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
	/// <typeparam name="T">オブジェクトベースを継承した型</typeparam>
	/// <param name="pObj">追加するオブジェクト</param>
	template <class T>
	void AddObject(T* pObj)
	{
		m_pObject.push_back(pObj);
		m_pObject.back()->SetObjectManager(this);
	}


	/// <summary>
	/// プレイヤーポインタの取得
	/// </summary>
	/// <returns>プレイヤーポインタ</returns>
	Player* const GetPlayer();

	

private:	// 変数

	std::shared_ptr<Collision> m_pCollision;		// 当たり判定
	std::shared_ptr<ToonShader> m_pToon;			// トゥーンシェーダ
	//std::shared_ptr<ShadowMapShader> m_pShadowMap;	// シャドウマップシェーダ

	std::list<ObjectBase*> m_pObject;				// オブジェクト
};

