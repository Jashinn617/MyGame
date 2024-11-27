#include "EnemyRobot.h"
#include "EShot.h"

#include "../Model.h"

#include "../../Common/CsvLoad.h"

#include "../../Utility/CollisionShape.h"
#include "../../Utility/Time.h"

#include "../../UI/HpBar/HpBarBase.h"
#include "../../UI/HpBar/HpBarEnemy.h"

#include <cassert>

namespace
{
	constexpr int kAttackInterval = 80;						// 攻撃感覚
	constexpr float kCapsuleRadius = 30.0f;					// カプセルの半径
	constexpr float kRotSpeed = 9.0f;						// 回転速度
	constexpr VECTOR kModelScale = { 0.15f,0.2f,0.15f };	// モデルスケール
	constexpr float kSearchRadius = 800.0f;					// 索敵範囲の半径
	constexpr float kSearchHeight = 70.0f;					// 索敵範囲の高さ
	constexpr float kHandRadius = 10.0f;					// 腕の当たり判定の半径
	constexpr float kMeleeAttackRange = 100.0f;				// 近距離攻撃射程
	constexpr float kShotAttackRange = 500.0f;				// 遠距離攻撃射程
	const char* const kName = "Robot";						// 名前
}

EnemyRobot::EnemyRobot(VECTOR pos)
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
	m_shotAttackRange = kShotAttackRange;

	// 攻撃タイプ設定
	m_attackType = AttackType::Mulch;

	// 索敵範囲設定
	m_pSearchRange = std::make_shared<CollisionShape>(m_characterInfo.pos, kSearchRadius, kSearchHeight);

	// 攻撃間隔
	m_pAttackInterval = std::make_shared<Time>(kAttackInterval);

	// HPバーポインタ作成
	m_pHpBar = std::make_shared<HpBarEnemy>(m_statusData.hp, m_characterInfo.pos);

	// 遠距離攻撃
	m_pShot = std::make_shared<EShot>(m_statusData.shotAtk);
}

EnemyRobot::~EnemyRobot()
{
	/*処理無し*/
}

void EnemyRobot::Init()
{
	// モデル取得
	m_pModel = std::make_shared<Model>(m_modelH);
	// モデル頂点取得
	m_topFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"head_end");
	assert(m_topFrameIndex != -1);
	assert(m_topFrameIndex != -2);
	m_characterInfo.topPos = MV1GetFramePosition(m_pModel->GetModelHandle(),
	m_topFrameIndex);
	// モデル底辺取得
	m_bottomFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"wheel_end");
	assert(m_bottomFrameIndex != -1);
	assert(m_bottomFrameIndex != -2);
	m_characterInfo.bottomPos = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_bottomFrameIndex);
	// 右手当たり判定頂点座標取得
	m_melleAttack.Coll1TopFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"armr.001");
	assert(m_melleAttack.Coll1TopFrameIndex != -1);
	assert(m_melleAttack.Coll1TopFrameIndex != -2);
	m_melleAttack.Coll1Top = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.Coll1TopFrameIndex);
	// 左手当たり判定頂点座標取得
	m_melleAttack.Coll2TopFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"arml.001");
	assert(m_melleAttack.Coll2TopFrameIndex != -1);
	assert(m_melleAttack.Coll2TopFrameIndex != -2);
	m_melleAttack.Coll2Top = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.Coll2TopFrameIndex);
	// 右手当たり判定底辺座標取得
	m_melleAttack.Coll1BottomFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"iktargetleft_end");
	assert(m_melleAttack.Coll1BottomFrameIndex != -1);
	assert(m_melleAttack.Coll1BottomFrameIndex != -2);
	m_melleAttack.Coll1Bottom = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.Coll1BottomFrameIndex);
	// 左手当たり判定底辺座標取得
	m_melleAttack.Coll2BottomFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"iktargetright_end");
	assert(m_melleAttack.Coll2BottomFrameIndex != -1);
	assert(m_melleAttack.Coll2BottomFrameIndex != -2);
	m_melleAttack.Coll2Bottom = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.Coll2BottomFrameIndex);

	// 当たり判定カプセルポインタ作成
	m_pCollShape = std::make_shared<CollisionShape>(m_characterInfo.topPos,
		m_characterInfo.bottomPos, kCapsuleRadius);
	// 右手当たり判定作成
	m_pMelleAttackCol1 = std::make_shared<CollisionShape>(m_melleAttack.Coll1Top, m_melleAttack.Coll1Bottom,
		kHandRadius);
	// 左手当たり判定作成
	m_pMelleAttackCol2 = std::make_shared<CollisionShape>(m_melleAttack.Coll2Top, m_melleAttack.Coll2Bottom,
		kHandRadius);

	// アニメーション設定
	m_pModel->SetAnim(m_animData.idle, true, true);
	// スケール設定
	m_pModel->SetScale(kModelScale);
	// 回転量初期化
	m_pModel->SetRot(m_characterInfo.rot);
	// 座標初期化
	m_pModel->SetPos(m_characterInfo.pos);
}

void EnemyRobot::UpdateAngle()
{
	// 向きたい方向
	float nextAngle = static_cast<float>(atan2(-m_moveDirection.x, -m_moveDirection.z));

	// 滑らかに指定した方向に向くための関数
	SmoothAngle(m_angle, nextAngle);
}
