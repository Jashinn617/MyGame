#include "ObjectManager.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Field.h"
#include "../Object/Camera.h"

#include "../Utility/Collision.h"

#include "../Shader/ToonShader.h"

ObjectManager::ObjectManager(Game::StageKind stageKind) :
	m_pCollision(std::make_shared<Collision>()),
	m_pToon(std::make_shared<ToonShader>())
	//m_pShadowMap(std::make_shared<ShadowMapShader>())
{
	// プレイやーの追加
	AddObject(new Player);
	// フィールド追加
	AddObject(new Field(stageKind));
}

ObjectManager::~ObjectManager()
{
	// オブジェクトポインタ解放
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pObject.erase(it);
	}
}

void ObjectManager::Update()
{
	// オブジェクト配列の最初のイテレータを取得する
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		// オブジェクトの更新
		auto obj = (*it);
		obj->Update();
		// オブジェクトが存在していない場合
		if (!obj->GetInfo().isExist)
		{
			// ポインタを解放する
			delete obj;
			obj = nullptr;
			it = m_pObject.erase(it);
			// イテレータを進める
			it++;
		}
		else
		{
			// イテレータを進める
			it++;
		}
	}

	// 当たり判定
	for (auto& myObj : m_pObject)
	{
		for (auto& targetObj : m_pObject)
		{
			// 同じオブジェクトの場合は当たり判定の処理をしない
			if (myObj == targetObj)continue;
			// 当たり判定の処理
			m_pCollision->UpdateCollision(myObj, targetObj);
		}
	}
}

void ObjectManager::Draw()
{
	// カメラ位置リセット
	GetPlayer()->GetCamera()->ResetCamera();

	// オブジェクト描画
	for (auto& obj : m_pObject)
	{
		// カメラに移っていない時は描画しない
		/*if (!CheckCameraViewClip(obj->GetInfo().pos))
		{*/
			obj->Draw(m_pToon);
		//}
	}

	// カメラ位置リセット
	GetPlayer()->GetCamera()->ResetCamera();

	// 2D描画
	for (auto& obj : m_pObject)
	{
		obj->Draw2D();
	}

	// カメラ位置リセット
	GetPlayer()->GetCamera()->ResetCamera();
}

Player* const ObjectManager::GetPlayer()
{
	// 全オブジェクトを検索してプレイヤーを見つける
	for (auto& obj : m_pObject)
	{
		if (obj->GetColType() != ObjectBase::ColType::Player) continue;

		return dynamic_cast<Player*>(obj);
	}

	return nullptr;
}