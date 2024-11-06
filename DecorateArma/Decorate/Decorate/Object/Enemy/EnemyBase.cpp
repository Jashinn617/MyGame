#include "EnemyBase.h"

#include "../ObjectManager.h"
#include "../Player/Player.h"
#include "../Model.h"

#include "../../Utility/CollisionShape.h"
#include "../../Utility/Time.h"

#include "../../UI/HpBar/HpBarBase.h"

using namespace CharacterData;

namespace
{
	constexpr float kDashSpeedRate = 2.0f;	// ダッシュ速度倍率
	constexpr float kAccRate = 0.5f;		// 加速度倍率
}

EnemyBase::EnemyBase():
	m_attackRange(0.0f),
	m_isAttack(false),
	m_isFinding(false),
	m_moveDirection{0.0f,0.0f,0.0f},
	m_enemyToPlayer{0.0f,0.0f,0.0f},
	m_attackType(AttackType::Melee),
	m_pSearchRange(nullptr),
	m_pRightHandColl(nullptr),
	m_pLeftHandColl(nullptr),
	m_pAttackInterval(nullptr)
{
	// 近距離攻撃当たり判定座標初期化
	m_melleAttack.rightTopFrameIndex = -1;
	m_melleAttack.rightBottomFrameIndex = -1;
	m_melleAttack.leftTopFrameIndex = -1;
	m_melleAttack.leftBottomFrameIndex = -1;
	m_melleAttack.rightTop = VGet(0.0f, 0.0f, 0.0f);
	m_melleAttack.rightBottom = VGet(0.0f, 0.0f, 0.0f);
	m_melleAttack.leftTop = VGet(0.0f, 0.0f, 0.0f);
	m_melleAttack.leftBottom = VGet(0.0f, 0.0f, 0.0f);
	// キャラクター情報初期化
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.topPos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.bottomPos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	// ステータス初期化
	m_statusData.hp = 0;
	m_statusData.meleeAtk = 0;
	m_statusData.shotAtk = 0;
	m_statusData.def = 0;
	m_statusData.spd = 0.0f;

	m_objSize = 0.0f;

	// メンバ関数初期化
	m_updateFunc = &EnemyBase::UpdateIdleState;
}

EnemyBase::EnemyBase(VECTOR pos):
	m_attackRange(0.0f),
	m_isAttack(false),
	m_isFinding(false),
	m_moveDirection{ 0.0f,0.0f,0.0f },
	m_enemyToPlayer{ 0.0f,0.0f,0.0f },
	m_attackType(AttackType::Melee),
	m_pSearchRange(nullptr),
	m_pRightHandColl(nullptr),
	m_pLeftHandColl(nullptr)
{
	// 近距離攻撃当たり判定座標初期化
	m_melleAttack.rightTopFrameIndex = -1;
	m_melleAttack.rightBottomFrameIndex = -1;
	m_melleAttack.leftTopFrameIndex = -1;
	m_melleAttack.leftBottomFrameIndex = -1;
	m_melleAttack.rightTop = VGet(0.0f, 0.0f, 0.0f);
	m_melleAttack.rightBottom = VGet(0.0f, 0.0f, 0.0f);
	m_melleAttack.leftTop = VGet(0.0f, 0.0f, 0.0f);
	m_melleAttack.leftBottom = VGet(0.0f, 0.0f, 0.0f);
	// キャラクター情報初期化
	m_characterInfo.pos = pos;
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	// ステータス初期化
	m_statusData.hp = 0;
	m_statusData.meleeAtk = 0;
	m_statusData.shotAtk = 0;
	m_statusData.def = 0;
	m_statusData.spd = 0.0f;

	m_objSize = 0.0f;

	// メンバ関数初期化
	m_updateFunc = &EnemyBase::UpdateIdleState;
}

EnemyBase::~EnemyBase()
{
	/*処理無し*/
}

void EnemyBase::Update()
{
	// 状態に合わせた更新
	UpdateStateTransition();
	(this->*m_updateFunc)();

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

	// 座標更新
	m_characterInfo.topPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_topFrameIndex);
	m_characterInfo.bottomPos = MV1GetFramePosition(m_pModel->GetModelHandle(), m_bottomFrameIndex);
	m_melleAttack.rightTop = MV1GetFramePosition(m_pModel->GetModelHandle(), m_melleAttack.rightTopFrameIndex);
	m_melleAttack.rightBottom= MV1GetFramePosition(m_pModel->GetModelHandle(), m_melleAttack.rightBottomFrameIndex);
	m_melleAttack.leftTop= MV1GetFramePosition(m_pModel->GetModelHandle(), m_melleAttack.leftTopFrameIndex);
	m_melleAttack.leftBottom= MV1GetFramePosition(m_pModel->GetModelHandle(), m_melleAttack.leftBottomFrameIndex);

	// HPバー更新
	m_pHpBar->Update();
}

void EnemyBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	m_pModel->Draw();

	m_pCollShape->DebugDraw(0x00ff00);
	m_pSearchRange->DebugDraw(0x000000);
	m_pRightHandColl->DebugDraw(0xff00ff);
	m_pLeftHandColl->DebugDraw(0xff00ff);
}

void EnemyBase::Draw2D()
{
	// HPバー描画
	m_pHpBar->Draw();
}

void EnemyBase::OnDamage(VECTOR targetPos, int damagePoint)
{
	// HPを減らす
	m_statusData.hp -= damagePoint;

	// HPが0以下になって死亡状態でなかった場合
	if (m_statusData.hp <= 0 && !m_isDead)
	{
		// 死亡する
		m_isDead = true;
	}

	// ダメージを受けた状態にする
	m_isDamage = true;
}

void EnemyBase::OnDead()
{
}

void EnemyBase::OnSearch(CharacterBase* pPlayer)
{
	// 衝突判定
	if (m_pSearchRange->IsCollide(pPlayer->GetCollShape()))
	{
		// 発見SEを鳴らす

		// 当たっていたら発見状態になる
		m_isFinding = true;
	}
	else
	{
		// 当たっていなかったら通常の行動に戻る
		m_isFinding = false;
	}
}

void EnemyBase::OnMeleeAttack(CharacterBase* pPlayer)
{
	// 攻撃中でないときは判定しない
	if (!m_isAttack) return;

	// 衝突判定
	if (m_pRightHandColl->IsCollide(pPlayer->GetCollShape()))
	{
		if (m_pLeftHandColl->IsCollide(pPlayer->GetCollShape()))
		{
			// 右手か左手どちらか当たってたらダメージを与える
			pPlayer->OnDamage(m_characterInfo.pos, m_statusData.meleeAtk);
		}
	}
}

void EnemyBase::InitMoveSpeed(float moveSpeed)
{
	m_moveData.walkSpeed = moveSpeed;
	m_moveData.dashSpeed = moveSpeed * kDashSpeedRate;
	m_moveData.acc = moveSpeed * kAccRate;
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

void EnemyBase::UpdateStateTransition()
{
	// 死亡状態だった時は何もしない
	if (StateTransitionDead()) return;

	// 優先度の高い状態だったら何もしない
	if (m_updateFunc == &EnemyBase::UpdateIdleState)return;
	if (m_updateFunc == &EnemyBase::UpdateDeadState)return;

	// 攻撃状態になったら処理を終了する
	if (StateTransitionMeleeAttack())return;

	// どれでもなかった場合は移動状態になる
	m_updateFunc = &EnemyBase::UpdateMoveState;
}

bool EnemyBase::StateTransitionDead()
{
	// HPが1以上残っていたらfalseを返す
	if (m_statusData.hp > 0)return false;

	m_updateFunc = &EnemyBase::UpdateDeadState;
	return true;
}

bool EnemyBase::StateTransitionMeleeAttack()
{
	// 攻撃タイプが近距離以外だった場合は何もしない
	if (m_attackType != AttackType::Melee) return false;
	// 攻撃中だったらtrueを返す
	if (m_updateFunc == &EnemyBase::UpdateMeleeAttackState) return true;

	// プレイヤーから敵までの方向ベクトルを求める
	m_enemyToPlayer = VSub(m_pObjectManager->GetPlayer()->GetInfo().pos, m_characterInfo.pos);

	// プレイヤーが攻撃範囲内に入ったら攻撃状態に移行する
	if (VSize(m_enemyToPlayer) < m_attackRange)
	{
		// 攻撃間隔のリセット
		m_pAttackInterval->Reset();
		// 攻撃フラグを立てる
		m_isAttack = true;
		// 攻撃状態に遷移する
		m_updateFunc = &EnemyBase::UpdateMeleeAttackState;
		
		return true;
	}
	
	// どの条件にも当てはまらなければfalseを返す
	return false;
}

bool EnemyBase::StateTransitionShotAttack()
{
	return false;
}

void EnemyBase::UpdateIdleState()
{
	// アニメーション再生
	m_pModel->ChangeAnim(m_animData.idle, true, false, 1);

	// 索敵範囲に入ったら移動状態になる
	if (m_isFinding)
	{
		m_updateFunc = &EnemyBase::UpdateMoveState;
	}
}

void EnemyBase::UpdateMoveState()
{
	// アニメーション再生
	m_pModel->ChangeAnim(m_animData.walk, true, false, 1);

	// 移動速度を出す
	m_moveSpeed = min(m_moveSpeed + m_moveData.acc, m_moveData.walkSpeed);
}

void EnemyBase::UpdateDeadState()
{
	m_moveSpeed = 0.0f;

	// 存在を消す
	m_characterInfo.isExist = false;
}

void EnemyBase::UpdateMeleeAttackState()
{
	// 攻撃中は移動をしない
	m_moveSpeed = 0.0f;

	// 攻撃間隔時間は攻撃しない
	if (!m_pAttackInterval->Update())
	{
		// アニメーション再生
		m_pModel->ChangeAnim(m_animData.idle, true, false, 1);
		UpdateMoveDirection();
		UpdateAngle();
		return;
	}

	// アニメーション再生
	m_pModel->ChangeAnim(m_animData.attack1, false, false, 2);
	m_isAttack = true;

	// 攻撃が終わったら移動状態になる
	if (m_pModel->IsAnimEnd())
	{
		m_pModel->ChangeAnim(m_animData.walk, true, false, 1);
		m_updateFunc = &EnemyBase::UpdateMoveState;
		m_isAttack = false;
	}
}

void EnemyBase::UpdateShotAttackState()
{
}