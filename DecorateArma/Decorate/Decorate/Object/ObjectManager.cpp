#include "ObjectManager.h"

#include "../Object/ObjectBase.h"
#include "../Object/Field.h"
#include "../Object/Camera.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyBase.h"

#include "../Utility/Collision.h"

#include "../Common/Spawn.h"

#include "../Shader/ToonShader.h"

namespace
{
	constexpr float kLockOnRange = 10000.0f;					// ロックオンできる範囲

	constexpr float kMinLockOnValidRangeMin = -DX_PI_F * 0.4f;	// ロックオンの有効範囲
	constexpr float kMinLockOnValidRangeMax = DX_PI_F * 0.4f;	// ロックオンの有効範囲
	constexpr float kMaxLockOnValidRangeMin = -DX_PI_F * 0.8f;	// ロックオンの有効範囲
	constexpr float kMaxLockOnValidRangeMax = DX_PI_F * 0.8f;	// ロックオンの有効範囲
}

ObjectManager::ObjectManager(Game::StageKind stageKind) :
	m_pLockOnEnemy(nullptr),
	m_pCollision(std::make_shared<Collision>()),
	m_pSpawn(std::make_shared<Spawn>(stageKind,this)),
	m_pToon(std::make_shared<ToonShader>())
	//m_pShadowMap(std::make_shared<ShadowMapShader>())
{
	// プレイヤーの追加
	AddObject(new Player);
	// フィールド追加
	AddObject(new Field(stageKind));
	// オブジェクト出現
	m_pSpawn->Init();
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
			// プレイヤー以外
			if (obj->GetColType() != ObjectBase::ColType::Player)
			{
				// ロックオンされていた場合
				if (m_pLockOnEnemy == obj)
				{
					m_pLockOnEnemy = nullptr;
				}

				// ポインタを解放する
				delete obj;
				obj = nullptr;
				it = m_pObject.erase(it);
			}			
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

void ObjectManager::InitLockOnEnemy()
{
	// ロックオン出来る範囲の設定
	float nearEnemyToPlayerVec = kLockOnRange;
	// カメラの向いている方向の取得
	float cameraAngle = GetPlayer()->GetCamera()->GetCameraAngleX();

	// ロックオンしている敵のポインタを空にする
	m_pLockOnEnemy = nullptr;

	for (auto& obj : m_pObject)
	{
		// 当たり判定の種類がエネミーじゃなかったらcontinueする
		if (obj->GetColType() != ObjectBase::ColType::Enemy) continue;

		// 敵からプレイヤーまでのベクトルを求める
		VECTOR enemyToPlayerVec = VSub(GetPlayer()->GetInfo().pos, obj->GetInfo().pos);

		// 敵からプレイヤーまでの角度を求める
		float enemyToPlayerAngle = atan2(enemyToPlayerVec.x, enemyToPlayerVec.z);
		// カメラの角度と敵からプレイヤーまでの角度の差を求める
		float differenceAngle = cameraAngle - enemyToPlayerAngle;

		// ロックオンできる範囲に入っているかどうか調べる
		bool isLockOnRangeMin = differenceAngle < kMinLockOnValidRangeMax && differenceAngle > kMinLockOnValidRangeMin;
		bool isLockOnRangeMax = differenceAngle > kMaxLockOnValidRangeMax || differenceAngle < kMaxLockOnValidRangeMin;

		// 角度の違いによってロックオンできる敵かどうかを判断する
		if (isLockOnRangeMin || isLockOnRangeMax)
		{
			// 敵からプレイヤーまでの距離を求める
			float EnemyToPlayerLen = VSize(dynamic_cast<EnemyBase*>(obj)->GetEnemyToPlayerVec());

			// 今見ている敵が今までに見た敵よりも近くにいる場合
			if (nearEnemyToPlayerVec > EnemyToPlayerLen)
			{
				// 一番近い距離を設定する
				nearEnemyToPlayerVec = EnemyToPlayerLen;
				// 今見ている敵をロックオンする敵にする
				m_pLockOnEnemy = dynamic_cast<EnemyBase*>(obj);
			}
		}
	}
}
