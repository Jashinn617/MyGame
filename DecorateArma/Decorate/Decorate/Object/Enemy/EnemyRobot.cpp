﻿#include "EnemyRobot.h"

#include "../Model.h"

#include "../../Common/CsvLoad.h"

#include "../../Utility/Sphere.h"
#include "../../Utility/Capsule.h"

#include <cassert>

namespace
{
	constexpr float kSize = 10.0f;						// サイズ
	constexpr float kHeight = 20.0f;					// 高さ
	constexpr float kCapsuleRadius = 30.0f;				// カプセルの半径
	constexpr float kRotSpeed = 9.0f;					// 回転速度
	constexpr VECTOR kModelScale = { 0.2f,0.3f,0.2f };	// モデルスケール
}

EnemyRobot::EnemyRobot(VECTOR pos)
{
	// 座標初期化
	m_characterInfo.pos = pos;
	// スケール設定

	// ステータス初期化
	CsvLoad::GetInstance().StatusLoad(m_statusData, "Robot");
	// アニメーション設定
	CsvLoad::GetInstance().AnimLoad(m_animData, "Robot");

	// 攻撃タイプ
	m_attackType = AttackType::Mulch;

	// 回転速度設定
	m_moveData.rotSpeed = kRotSpeed;
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

	// 当たり判定カプセルポインタ作成
	m_pCapsule = std::make_shared<Capsule>(m_characterInfo.topPos,
		m_characterInfo.bottomPos, kCapsuleRadius);

	// アニメーション設定
	m_pModel->SetAnim(m_animData.idle, true, true);
	// スケール設定
	m_pModel->SetScale(kModelScale);
	// 回転量初期化
	m_pModel->SetRot(m_characterInfo.rot);
	// 座標初期化
	m_pModel->SetPos(m_characterInfo.pos);
}