#pragma once

#include "../Utility/Game.h"

#include <memory>
#include <list>

class ObjectBase;

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
		m_pObject.back()->SetMain(this);
	}

	

private:	// 変数

	std::list<ObjectBase*> m_pObject;		// オブジェクト

};

