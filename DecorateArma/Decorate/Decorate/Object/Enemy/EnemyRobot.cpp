#include "EnemyRobot.h"

#include "../Model.h"

#include "../../Common/CsvLoad.h"

#include "../../Utility/CollisionShape.h"
#include "../../Utility/Time.h"

#include <cassert>

namespace
{
	constexpr int kAttackInterval = 35;						// 攻撃感覚
	constexpr float kCapsuleRadius = 30.0f;					// カプセルの半径
	constexpr float kRotSpeed = 9.0f;						// 回転速度
	constexpr VECTOR kModelScale = { 0.15f,0.2f,0.15f };	// モデルスケール
	constexpr float kSearchRadius = 700.0f;					// 索敵範囲の半径
	constexpr float kSearchHeight = 70.0f;					// 索敵範囲の高さ
	constexpr float kHandRadius = 10.0f;					// 腕の当たり判定の半径
}

EnemyRobot::EnemyRobot(VECTOR pos)
{
	// 座標初期化
	m_characterInfo.pos = pos;

	// ステータス初期化
	CsvLoad::GetInstance().StatusLoad(m_statusData, "Robot");
	// アニメーション設定
	CsvLoad::GetInstance().AnimLoad(m_animData, "Robot");

	// 攻撃タイプ
	m_attackType = AttackType::Mulch;

	// 回転速度設定
	m_moveData.rotSpeed = kRotSpeed;

	// 索敵範囲設定
	m_pSearchRange = std::make_shared<CollisionShape>(m_characterInfo.pos, kSearchRadius, kSearchHeight);

	// 攻撃間隔
	m_pAttackInterval = std::make_shared<Time>(kAttackInterval);
}

EnemyRobot::~EnemyRobot()
{
}

void EnemyRobot::Init()
{
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
	m_melleAttack.rightTopFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"armr.001");
	assert(m_melleAttack.rightTopFrameIndex != -1);
	assert(m_melleAttack.rightTopFrameIndex != -2);
	m_melleAttack.rightTop = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.rightTopFrameIndex);
	// 左手当たり判定頂点座標取得
	m_melleAttack.leftTopFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"arml.001");
	assert(m_melleAttack.leftTopFrameIndex != -1);
	assert(m_melleAttack.leftTopFrameIndex != -2);
	m_melleAttack.leftTop = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.leftTopFrameIndex);
	// 右手当たり判定底辺座標取得
	m_melleAttack.rightBottomFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"minigun_end");
	assert(m_melleAttack.rightBottomFrameIndex != -1);
	assert(m_melleAttack.rightBottomFrameIndex != -2);
	m_melleAttack.rightBottom = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.rightBottomFrameIndex);
	// 左手当たり判定底辺座標取得
	m_melleAttack.leftBottomFrameIndex = MV1SearchFrame(m_pModel->GetModelHandle(),
		"handdown.001_end");
	assert(m_melleAttack.leftBottomFrameIndex != -1);
	assert(m_melleAttack.leftBottomFrameIndex != -2);
	m_melleAttack.leftBottom = MV1GetFramePosition(m_pModel->GetModelHandle(),
		m_melleAttack.leftBottomFrameIndex);

	// 当たり判定カプセルポインタ作成
	m_pCollShape = std::make_shared<CollisionShape>(m_characterInfo.topPos,
		m_characterInfo.bottomPos, kCapsuleRadius);
	// 右手当たり判定作成
	m_pRightHandColl = std::make_shared<CollisionShape>(m_melleAttack.rightTop, m_melleAttack.rightBottom,
		kHandRadius);
	// 左手当たり判定作成
	m_pLeftHandColl = std::make_shared<CollisionShape>(m_melleAttack.leftTop, m_melleAttack.leftBottom,
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
