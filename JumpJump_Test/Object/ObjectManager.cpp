#include "ObjectManager.h"
#include "../Object/ObjectBase.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"
#include "../Util/Input.h"
#include "../Util/Time.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"
#include "../Util/Collision.h"
#include "Model.h"

namespace
{	
	constexpr float kRotSpeed = 0.4f;	// 回転速度
	constexpr int kGameClearTime = 40;	// ゴールについてから次のシーンに移行するまでの時間
}


ObjectManager::ObjectManager(Game::Stage stage):
	m_isGameClear(false),
	m_isGoal(false),
	m_isTutorial(false)
{
	m_pCollision = std::make_shared<Collision>();
	m_pSkyDome = std::make_shared<SkyDome>();
	m_pEnemyManager = std::make_shared<EnemyManager>(stage, this);

	AddObject(new Player);
}

ObjectManager::~ObjectManager()
{
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it != m_pObject.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pObject.erase(it);
	}
}

void ObjectManager::Update(Input& input)
{
	// オブジェクト配列の最初のイテレータを取得する
	std::list<ObjectBase*>::iterator it = m_pObject.begin();
	while (it!=m_pObject.end())
	{
		// オブジェクトの更新
		auto obj = (*it);
		obj->Update(input);

		// オブジェクトが存在していない場合
		if (!obj->GetInfo().isExist)
		{
			// 存在が消えてからの時間をカウントする
			if (!obj->IsExistCount())
			{
				it++;
				continue;
			}

			// オブジェクトが敵だった場合
			if (obj->GetColType() == ObjectBase::ColType::Enemy)
			{

			}
			// オブジェクトがアイテムだった場合
			if (obj->GetColType() == ObjectBase::ColType::Item)
			{

			}
			// オブジェクトがプレイヤーだった場合
			if (obj->GetColType() == ObjectBase::ColType::Player)
			{
				delete obj;
				obj = nullptr;
				it = m_pObject.erase(it);
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}

	// クリアしている場合は更新処理を行わない
	if (m_isGameClear) return;

	// 当たり判定
	for (auto& myObj : m_pObject)
	{
		for (auto& targetObj : m_pObject)
		{
			// 同じオブジェクトの場合は当たり判定の処理をしない
			if (myObj == targetObj)continue;
			// 当たり判定の処理
			m_pCollision->Update(myObj, targetObj);
		}
	}

	// エネミーマネージャーの更新

	// スカイドームの更新
	m_pSkyDome->Update(GetPlayer()->GetInfo().pos);
}

void ObjectManager::Draw()
{
	// カメラの位置のリセット
	GetPlayer()->GetCamera()->ResetCamera();

	// スカイドームの描画
	m_pSkyDome->Draw();

	// オブジェクトの描画
	for (auto& obj : m_pObject)
	{
		obj->Draw();
	}

	// シャドウマップの書き込み開始

	// 終了

	// カメラの位置のリセット
	GetPlayer()->GetCamera()->ResetCamera();

	// フィールドにシャドウマップを張り付ける準備をする

	// 作業終了

	// ステージクリア時は2D描画をしない
	if (!m_isGameClear)
	{
		// カメラの位置のリセット
		GetPlayer()->GetCamera()->ResetCamera();
		for (auto& obj : m_pObject)
		{
			obj->Draw2D();
		}
		
	}

	// カメラの位置のリセット
	GetPlayer()->GetCamera()->ResetCamera();
}

bool ObjectManager::IsPlayerExist()
{
	if (GetPlayer()->GetInfo().isExist) return true;
	return false;
}

bool ObjectManager::IsEnemyExist()
{
	for (auto& enemy : m_pObject)
	{
		if (enemy->GetColType() != ObjectBase::ColType::Enemy) continue;

		if (enemy->GetInfo().isExist) return true;
	}
	return false;
}

bool ObjectManager::IsItemExist()
{
	for (auto& item : m_pObject)
	{
		if (item->GetColType() != ObjectBase::ColType::Item) continue;

		if (item->GetInfo().isExist) return true;
	}
	return false;
}

int ObjectManager::GetItemNum() const
{
	// 残りアイテムの数
	int itemNum = 0;

	for (auto& item : m_pObject)
	{
		if (item->GetColType() != ObjectBase::ColType::Item) continue;

		itemNum++;
	}
	return itemNum;
}

Player* const ObjectManager::GetPlayer()
{
	// 全オブジェクトを検索する
	for (auto& obj : m_pObject)
	{
		if (obj->GetColType() != ObjectBase::ColType::Player) continue;

		return dynamic_cast<Player*>(obj);
	}

	return nullptr;
}

void ObjectManager::SetGameClear()
{
	m_isGameClear = true;
	GameClearUpdate();
}

void ObjectManager::GameClearUpdate()
{
	for (auto& obj : m_pObject)
	{
		obj->StageClear();
	}
}
