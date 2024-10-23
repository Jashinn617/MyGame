#include "Shot.h"

#include "../Model.h"

#include "../../Utility/Time.h"
#include "../../Utility/Sphere.h"
#include "../../Utility/Pad.h"

#include <cmath>

namespace
{
	const char* const kFileName = "Data/Model/ShotWeapon/UFO.mv1";					// モデルファイルパス
	const char* const kBulletFileName = "Data/Model/ShotWeapon/Bullet/Shot.mv1";	// 弾ファイルパス
	
	constexpr float kPlayerDistance = 40.0f;					// プレイヤーとの距離
	constexpr float kPlayerToHeight = 55.0f;					// プレイヤーからの高さ
	constexpr float kPlayerLeftBack = DX_PI_F * 5.0f / 4.0f;	// プレイヤーの左後ろ
	constexpr float kSinSpeed = 0.03f;							// 昇降スピード
	constexpr float kSinSwing = 4.0f;							// 昇降幅
	constexpr VECTOR kScaleVec = { 0.01f,0.05f,0.01f };			// スケール

	constexpr int kBulletNum = 50;							// 弾数
	constexpr int kBulletVanishTime = 50;					// 弾が消えるまでの時間
	constexpr int kBulletIntervalTime = 5;					// 次の球が発射されるまでの時間
	constexpr float kBulletRadius = 2;						// 弾の半径
	constexpr float kBulletSpeed = 15.0f;					// 弾の速度
	constexpr float kBulletStartPosHeight = 5.0f;			// 弾を発射する高さ
	constexpr VECTOR kBulletScale = { 0.2f,0.2f,0.2f };		// 弾のスケール
}

Shot::Shot():
	m_sinCount(0.0f),
	m_sinPosY(0.0f),
	m_pos{0.0f,0.0f,0.0f},
	m_cameraRotMtx(MGetRotY(0)),
	m_pModel(std::make_shared<Model>(kFileName)),
	m_pBulletIntervalTime(std::make_shared<Time>(kBulletIntervalTime))
{
	// 弾のモデルハンドルの取得
	int bulletH = MV1LoadModel(kBulletFileName);

	// 弾の生成
	m_bullet.resize(kBulletNum);
	for (auto& bullet : m_bullet)
	{
		// 存在フラグ初期化
		bullet.isExist = false;
		// 座標初期化
		bullet.pos = VGet(0.0f, 0.0f, 0.0f);
		// 進む向きの初期化
		bullet.direction = VGet(0.0f, 0.0f,0.0f);
		// 消えるまでの時間の生成
		bullet.vanishTime = std::make_shared<Time>(kBulletVanishTime);
		// 当たり判定の生成
		bullet.coll = std::make_shared<Sphere>(bullet.pos, kBulletRadius, kBulletRadius);
		// モデルの生成
		bullet.model = std::make_shared<Model>(bulletH);
		// 弾のスケールの設定
		bullet.model->SetScale(kBulletScale);
	}

	// モデルスケール設定
	m_pModel->SetScale(kScaleVec);
}

Shot::~Shot()
{
	/*処理無し*/
}

void Shot::Update(const VECTOR& playerPos, float playerRot)
{
	// プレイヤーの左後ろ計算
	float angle = playerRot + kPlayerLeftBack;

	// オフセット計算
	float offsetX = cosf(angle) * kPlayerDistance;
	float offsetZ = sinf(angle) * kPlayerDistance;

	// 物体の位置の設定
	m_pos = VGet(playerPos.x + offsetX,
		playerPos.y + kPlayerToHeight,
		playerPos.z + offsetZ);

	// 昇降
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kSinSwing;
	m_pos.y += m_sinPosY;

	// モデル座標更新
	m_pModel->SetPos(m_pos);
	// モデル回転更新
	m_pModel->SetRot(VGet(0.0f, playerRot, 0.0f));

	// 弾生成
	MakeBullet();
	// 弾更新
	UpdateBullet();
}

void Shot::Draw()
{
	// 描画
	m_pModel->Draw();

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

#ifdef _DEBUG
	DrawFormatString(0, 160, 0xffffff, "遠距離攻撃武器座標：%f,%f,%f"
	, m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG
}

void Shot::UpdateBullet()
{
	// 存在していなかったら発射する
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
				bullet.pos.x += bullet.direction.x * kBulletSpeed;
				bullet.pos.y += bullet.direction.y * kBulletSpeed;
				bullet.pos.z += bullet.direction.z * kBulletSpeed;

				// モデル座標更新
				bullet.model->SetPos(bullet.pos);
			}
		}
	}

}

void Shot::MakeBullet()
{
	// LBボタンが押された場合
	if (Pad::IsPress(PAD_INPUT_5))
	{
		// 前の弾が発射されてから一定時間経った場合
		if (m_pBulletIntervalTime->Update())
		{
			// 存在していなかったら発射する
			for (auto& bullet : m_bullet)
			{
				if (!bullet.isExist)
				{
					// 存在フラグを立てる
					bullet.isExist = true;
					// 位置の決定
					bullet.pos = m_pos;
					bullet.pos.y += kBulletStartPosHeight;
					// モデル座標更新
					bullet.model->SetPos(bullet.pos);
					// 進む方向の決定(カメラから見て前に飛ばす)	
					bullet.direction= VGet(-m_cameraRotMtx.m[2][0], 
						-m_cameraRotMtx.m[2][1],
						-m_cameraRotMtx.m[2][2]);

					break;
				}
			}
			m_pBulletIntervalTime->Reset();
		}
		
	}
}
