#include "EnemySkull.h"

#include "../Circle.h"
#include "../Model.h"
#include "../ObjectManager.h"

#include "../Player/Player.h"

#include "../../Util/CsvLoad.h"
#include "../../Util/Time.h"

#include "../../Shader/ToonShader.h"

namespace
{
	constexpr float kModelScalse = 0.3f;	// モデルスケール
	constexpr float kEnemySize = 20;		// サイズ
	constexpr float kHeight = 20.0f;		// 高さ
}

EnemySkull::EnemySkull(VECTOR pos, float speed)
{
	// アニメーションの初期化
	CsvLoad::GetInstance().AnimLoad(m_animData, "Skull");

	// 情報初期化
	m_info.pos = pos;
	// 初期角度設定
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	// サイズ設定
	m_objSize = kEnemySize;
	// 当たり判定の円の作成
	m_pCircle = std::make_shared<Circle>(m_info.pos, kEnemySize, kHeight);
	// 速度の初期化
	InitMoveSpeed(m_statusData.spd);
	m_moveSpeed = speed;
}

EnemySkull::~EnemySkull()
{
	/*処理無し*/
}

void EnemySkull::Init()
{
	// モデルポインタ作成
	m_pModel = std::make_shared<Model>(m_modelH);
	// モデルアニメーション設定
	m_pModel->SetAnim(m_animData.idle, true, true);
	// モデルスケール設定
	m_pModel->SetScale(VGet(kModelScalse, kModelScalse, kModelScalse));
	// モデル角度初期化
	m_pModel->SetRot(m_info.rot);
	// モデル座標初期化
	m_pModel->SetPos(m_info.pos);
}

void EnemySkull::MoveDirectionUpdate()
{
	/*プレイヤーのいる方向に向けて進む*/
	// プレイヤーまでのベクトルを計算する
	m_enemyToPlayerVec = VSub(m_pObjectManager->GetPlayer()->GetInfo().pos, m_info.pos);
	// 正規化
	m_moveDirectionVec = VNorm(m_enemyToPlayerVec);
}

VECTOR EnemySkull::MoveUpdate()
{
	// 移動方向の更新
	MoveDirectionUpdate();
	// 角度の更新
	AngleUpdate();

	// 移動方向に速度をかける
	m_moveDirectionVec = VScale(m_moveDirectionVec, m_moveSpeed);

	return m_moveDirectionVec;
}
