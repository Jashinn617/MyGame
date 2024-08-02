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


ObjectManager::ObjectManager():
	m_isGameClear(false),
	m_isGoal(false),
	m_isTutorial(false)
{
	m_pCollision = std::make_shared<Collision>();
	m_pSkyDome = std::make_shared<SkyDome>();
	m_pEnemyManager = std::make_shared<EnemyManager>();

	AddObject(new Player);
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
}

void ObjectManager::Draw()
{
}

bool ObjectManager::IsPlayerExist()
{
	return false;
}

bool ObjectManager::IsEnemyExist()
{
	return false;
}

bool ObjectManager::IsItemExist()
{
	return false;
}

int ObjectManager::GetItemNum() const
{
	return 0;
}

Player* const ObjectManager::GetPlayer()
{
	return nullptr;
}

void ObjectManager::SetGameClear()
{
}

void ObjectManager::GameClearUpdate()
{
}
