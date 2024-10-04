﻿#include "ObjectManager.h"
#include "../Shader/ToonShader.h"
#include "../Shader/ShadowMapShader.h"

#include "../Object/Field.h"
#include "../Object/ObjectBase.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Item/ItemBase.h"
#include "../Object/Item/ItemManager.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"

#include "../Util/Time.h"
#include "../Util/Collision.h"

#include "Model.h"

namespace
{	
	constexpr float kRotSpeed = 0.4f;	// 回転速度
	constexpr int kGameEndTime = 120;	// ゴールについてから次のシーンに移行するまでの時間
}

ObjectManager::ObjectManager(Game::StageKind stageKind):
	m_isGameClear(false),
	m_isStageEnd(false),
	m_pCollision(std::make_shared<Collision>()),
	m_pSkyDome(std::make_shared<SkyDome>()),
	m_pEnemyManager(std::make_shared<EnemyManager>(stageKind,this)),
	m_pItemManager(std::make_shared<ItemManager>(stageKind,this)),
	m_pToonShader(std::make_shared<ToonShader>()),
	m_pShadowMapShader(std::make_shared<ShadowMapShader>()),
	m_gameEndTime(std::make_shared<Time>(kGameEndTime))
{
	// オブジェクトの追加
	AddObject(new Player);
	AddObject(new Field(stageKind));

	// アイテムマネージャーの初期化
	m_pItemManager->Init();
	// エネミーマネージャーの初期化
	m_pEnemyManager->Init();
}

ObjectManager::~ObjectManager()
{
	// オブジェクトのポインタを解放する
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
			// オブジェクトがアイテムだった場合
			if (obj->GetColType() == ObjectBase::ColType::Item)
			{
				// ゲット数を増やす
				m_pItemManager->AddGetNum();
			}

			// オブジェクトがプレイヤー以外だった場合
			if (obj->GetColType() != ObjectBase::ColType::Player)
			{
				delete obj;
				obj = nullptr;
				it = m_pObject.erase(it);
			}
			else
			{
				// イテレータを進める
				it++;
			}
		}
		else
		{
			// イテレータを進める
			it++;
		}
	}

	if (m_pItemManager->IsClear()) // アイテムをすべて集めた場合
	{
		// ステージを終了する
		m_isStageEnd = true;
	}
	
	if (m_isStageEnd)	// ステージが終了した場合
	{
		if (IsObjStageEnd()) 	// 全オブジェクトの終了処理が終わったら
		{
			// クリアフラグを立てる
			m_isStageEnd = false;
			m_isGameClear = true;
		}
		else	// 終わっていなかったら
		{
			// 終了処理を続ける
			GameEndUpdate();
		}
	}

	if (m_isGameClear)	// クリアフラグが立ったら
	{
		// クリア時の処理をする
		GameClearUpdate();
	}

	// スカイドームの更新
	m_pSkyDome->Update(GetPlayer()->GetInfo().pos);

	// クリアしている場合は当たり判定処理を行わない
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
		// カメラに映っていないときは描画をしない
		if (!CheckCameraViewClip(obj->GetInfo().pos))
		{
			obj->Draw(m_pToonShader);
		}
	}

	// シャドウマップの書き込み開始
	m_pShadowMapShader->WriteStart(GetPlayer()->GetPos());

	for (auto& obj : m_pObject)
	{
		// フィールド以外に処理を行う
		// (フィールドにシャドウマップを張り付けるため)
		if (obj->GetColType() != ObjectBase::ColType::Field)
		{
			obj->ShadowMapDraw(m_pShadowMapShader);
		}
	}

	// 終了
	m_pShadowMapShader->WriteEnd();

	// カメラの位置のリセット
	GetPlayer()->GetCamera()->ResetCamera();

	// フィールドにシャドウマップを張り付ける準備をする
	m_pShadowMapShader->SetShaderField(GetPlayer()->GetPos());
	for (auto& obj : m_pObject)
	{
		//ここではフィールドだけ描画を行う
		if (obj->GetColType() == ObjectBase::ColType::Field)
		{
			obj->ShadowMapDraw(m_pShadowMapShader);
		}
	}
	// 作業終了
	m_pShadowMapShader->WriteEnd();

	 //ステージクリア時は描画をしない
	if (!m_isGameClear)
	{
		// カメラの位置のリセット
		GetPlayer()->GetCamera()->ResetCamera();

	// 2D描画
		for (auto& obj : m_pObject)
		{
			obj->Draw2D();
		}
		// 残りアイテム数描画
		m_pItemManager->Draw();		
	}
	 //カメラの位置のリセット
	GetPlayer()->GetCamera()->ResetCamera();
}

bool ObjectManager::IsPlayerExist()
{
	return GetPlayer()->GetInfo().isExist;
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

bool ObjectManager::IsObjStageEnd()
{
	for (auto& obj : m_pObject)
	{
		// 何か一つでも終了処理を終えていないオブジェクトがあったら
		// falseで返す
		if (!obj->IsStageEnd())
		{
			return false;
		}
	}

	// すべてのオブジェクトの終了処理が終えてから
	// 一定時間たったら次のシーンに飛ぶ
	if (m_gameEndTime->Update())
	{
		return true;
	}
	
	return false;
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

void ObjectManager::SetGameClear()
{
	// クリアフラグをtrueにする
	m_isGameClear = true;
	// クリア時の処理を行う
	GameClearUpdate();
}

void ObjectManager::GameClearUpdate()
{
	for (auto& obj : m_pObject)
	{
		// ステージクリア処理
		obj->StageClear();
	}
}

void ObjectManager::GameEndUpdate()
{
	for (auto& obj : m_pObject)
	{
		// 終了処理
		obj->StageEnd();
	}
}
