#include "EnemyBossParasite.h"

#include "../Model.h"

#include "../../Common/CsvLoad.h"

#include "../../Utility/CollisionShape.h"
#include "../../Utility/Time.h"

#include "../../UI/HpBar/HpBarBase.h"

namespace
{
	constexpr int kAttackInterval = 150;					// 攻撃感覚
	constexpr float kCapsuleRadius = 30.0f;					// カプセルの半径
	constexpr float kRotSpeed = 9.0f;						// 回転速度
	constexpr VECTOR kModelScale = { 0.15f,0.2f,0.15f };	// モデルスケール
	constexpr float kSearchRadius = 800.0f;					// 索敵範囲の半径
	constexpr float kSearchHeight = 70.0f;					// 索敵範囲の高さ
	constexpr float kHandRadius = 10.0f;					// 腕の当たり判定の半径
	constexpr float kMeleeAttackRange = 100.0f;				// 近距離攻撃射程
	const char* const kName = "BossParasite";				// 名前
}

EnemyBossParasite::EnemyBossParasite(VECTOR pos)
{
	// 座標初期化
	m_characterInfo.pos = pos;

	// ステータス初期化
	CsvLoad::GetInstance().StatusLoad(m_statusData, kName);
	// アニメーション設定
	CsvLoad::GetInstance().AnimLoad(m_animData, kName);

	// 移動速度設定
	InitMoveSpeed(m_statusData.spd);

	// 回転速度設定
	m_moveData.rotSpeed = kRotSpeed;

	// 攻撃範囲設定
	m_meleeAttackRange = kMeleeAttackRange;

	// 攻撃タイプ設定
	m_attackType = AttackType::Melee;

	// 索敵範囲設定
	m_pSearchRange = std::make_shared<CollisionShape>(m_characterInfo.pos, kSearchRadius, kSearchHeight);

	// 攻撃間隔
	m_pAttackInterval = std::make_shared<Time>(kAttackInterval);

	// 敵タイプ設定
	m_enemyType = EnemyType::Boss;
}

EnemyBossParasite::~EnemyBossParasite()
{
}

void EnemyBossParasite::Init()
{
}

void EnemyBossParasite::Draw(std::shared_ptr<ToonShader> pToonShader)
{
}

void EnemyBossParasite::Draw2D()
{
}
