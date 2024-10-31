#include "EnemyBase.h"

#include "../ObjectManager.h"
#include "../Player/Player.h"
#include "../Model.h"

#include "../../Utility/CollisionShape.h"

using namespace CharacterData;

EnemyBase::EnemyBase():
	m_moveDirection{0.0f,0.0f,0.0f},
	m_enemyToPlayer{0.0f,0.0f,0.0f},
	m_attackType(AttackType::Melee)
{
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.topPos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.bottomPos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	// ステータス初期化
	m_statusData.hp = 0;
	m_statusData.atk = 0;
	m_statusData.def = 0;
	m_statusData.spd = 0.0f;

	m_objSize = 0.0f;
	
}

EnemyBase::EnemyBase(VECTOR pos):
	m_moveDirection{ 0.0f,0.0f,0.0f },
	m_enemyToPlayer{ 0.0f,0.0f,0.0f },
	m_attackType(AttackType::Melee)
{
	m_characterInfo.pos = pos;
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	// ステータス初期化
	m_statusData.hp = 0;
	m_statusData.atk = 0;
	m_statusData.def = 0;
	m_statusData.spd = 0.0f;

	m_objSize = 0.0f;

}

EnemyBase::~EnemyBase()
{
	/*処理無し*/
}

void EnemyBase::Update()
{
	// 移動ベクトルの取得
	m_characterInfo.vec = UpdateMove();
	// 重力更新
	UpdateGravity();

	// アニメーション更新
	m_pModel->Update();
	// モデル座標更新
	m_pModel->SetPos(m_characterInfo.pos);
	// モデル角度更新
	m_pModel->SetRot(VGet(0.0f, m_angle + DX_PI_F, 0.0f));

	// 座標設定
	m_characterInfo.topPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_topFrameIndex);
	m_characterInfo.bottomPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_bottomFrameIndex);
}

void EnemyBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	m_pModel->Draw();

	m_pCollShape->DebugDraw(0x00ff00);
}

void EnemyBase::Draw2D()
{
}

void EnemyBase::OnDamage(VECTOR targetPos)
{
}

void EnemyBase::OnDead()
{
}

void EnemyBase::UpdateAngle()
{
	// 向きたい方向
	float nextAngle = atan2(m_moveDirection.x, m_moveDirection.z);

	// 滑らかに指定した方向に向くための関数
	SmoothAngle(m_angle, nextAngle);
}

void EnemyBase::UpdateMoveDirection()
{
	// プレイヤーから敵までのベクトルを求める
	m_enemyToPlayer = VSub(m_pObjectManager->GetPlayer()->GetInfo().pos,
		m_characterInfo.pos);
	// プレイヤーがいる方向に進むベクトルを作る
	m_moveDirection = VNorm(m_enemyToPlayer);

	// 進みたい方向のY軸を省く
	m_moveDirection.y = 0.0f;
}

VECTOR EnemyBase::UpdateMove()
{
	//if (m_moveSpeed == 0.0f)return VGet(0.0f, 0.0f, 0.0f);

	// 移動方向更新
	UpdateMoveDirection();
	// 角度更新
	UpdateAngle();

	// 移動ベクトル生成
	VECTOR move = VNorm(m_moveDirection);

	move.x *= m_moveSpeed;
	move.z *= m_moveSpeed;

	return move;
}
