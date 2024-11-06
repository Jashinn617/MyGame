#include "EShot.h"

#include "../CharacterBase.h"
#include "../Model.h"

#include "../../Utility/CollisionShape.h"
#include "../../Utility/Time.h"

#include <cassert>

namespace
{
	const char* const kFileName = "Data/Model/Enemy/Shot.mv1";	// 弾モデルファイルパス

	constexpr int kNum = 50;						// 弾数
	constexpr int kVanishTime = 50;					// 弾が消えるまでの時間
	constexpr int kIntervalTime = 10;				// 次の球が発射されるまでの時間
	constexpr float kRadius = 10;					// 弾の半径
	constexpr float kSpeed = 5.0f;					// 弾の速度
	constexpr float kStartPosHeight = 5.0f;			// 弾を発射する高さ
	constexpr VECTOR kScale = { 0.4f,0.4f,0.4f };	// 弾のスケール
}

EShot::EShot(int atkPoint):
	m_atkPoint(atkPoint),
	m_pos{0.0f,0.0f,0.0f},
	m_pBulletIntervalTime(std::make_shared<Time>(kIntervalTime))
{
	// 弾のモデルハンドル取得
	int H = MV1LoadModel(kFileName);
	assert(H != -1);

	// 弾生成
	m_bullet.resize(kNum);
	for (auto& bullet : m_bullet)
	{
		// 存在フラグ初期化
		bullet.isExist = false;
		// 座標初期化
		bullet.pos = VGet(0.0f, 0.0f, 0.0f);
		// 進む向きの初期化
		bullet.direction = VGet(0.0f, 0.0f, 0.0f);
		// 消えるまでの時間の生成
		bullet.vanishTime = std::make_shared<Time>(kVanishTime);
		// 当たり判定の生成
		bullet.coll = std::make_shared<CollisionShape>(bullet.pos, kRadius, 0.0f);
		// モデルの生成
		bullet.model = std::make_shared<Model>(H);
		// 弾のスケールの設定
		bullet.model->SetScale(kScale);
	}
}

EShot::~EShot()
{
	/*処理無し*/
}

void EShot::Update(VECTOR targetPos, bool isAttack)
{
	// 存在していたら発射する
	for (auto& bullet : m_bullet)
	{
		if (bullet.isExist)
		{
			// 一定時間経ったら消す
			if (bullet.vanishTime->Update())
			{
				bullet.isExist = false;
				bullet.vanishTime->Reset();
			}
			else
			{
				// 弾を撃つ
				bullet.pos.x += bullet.direction.x * kSpeed;
				bullet.pos.y += bullet.direction.y * kSpeed;
				bullet.pos.z += bullet.direction.z * kSpeed;

				// モデル座標更新
				bullet.model->SetPos(bullet.pos);
			}
		}
	}

	// 弾生成
	Make(targetPos, isAttack);
}

void EShot::Draw()
{
	for (auto& bullet : m_bullet)
	{
		// 存在していた場合は描画する
		if (bullet.isExist)
		{
			// モデル描画
			bullet.model->Draw();
			bullet.coll->DebugDraw(0xff0000);
		}
	}
}

void EShot::OnAttack(CharacterBase* pPlayer)
{
	for (auto& bullet : m_bullet)
	{
		// 衝突判定
		if (bullet.coll->IsCollide(pPlayer->GetCollShape()) && bullet.isExist)
		{
			// 当たっていたらダメージを与える
			pPlayer->OnDamage(m_pos, m_atkPoint);

			// 弾を消す
			bullet.isExist = false;
		}
		else
		{
			continue;
		}
	}
}

void EShot::Make(VECTOR targetPos, bool isAttack)
{
	// 攻撃中でない場合は弾を出さない
	if (!isAttack) return;
	// 前の弾が発射されてから一定時間経ってないと弾を出さない
	if (!m_pBulletIntervalTime->Update()) return;

	// 存在していなかったら発射する
	for (auto& bullet : m_bullet)
	{
		// 存在フラグを立てる
		bullet.isExist = true;
		// 位置の決定
		bullet.pos = m_pos;
		bullet.pos.y += kStartPosHeight;
		// モデル座標更新
		bullet.model->SetPos(bullet.pos);

		// 高さ調整
		targetPos.y += 0.0f;

		// 進む方向の決定
		bullet.direction = VNorm(VSub(targetPos, bullet.pos));

		break;
	}
	// タイムリセット
	m_pBulletIntervalTime->Reset();
}
