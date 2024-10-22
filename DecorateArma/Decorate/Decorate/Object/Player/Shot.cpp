#include "Shot.h"

#include "../Model.h"

#include <cmath>

namespace
{
	const char* const kFileName = "Data/Model/ShotWeapon/UFO.mv1";	// モデルファイルパス

	

	constexpr float kPlayerDistance = 20.0f;					// プレイヤーとの距離
	constexpr float kPlayerToHeight = 55.0f;					// プレイヤーからの高さ
	constexpr float kPlayerLeftBack = DX_PI_F * 5.0f / 4.0f;	// プレイヤーの左後ろ
	constexpr VECTOR kScaleVec = { 0.01f,0.05f,0.01f };			// スケール

	constexpr float kSinSpeed = 0.03f;		// 上下移動スピード
	constexpr float kSinSwing = 4.0f;		// 上下移動幅
}

Shot::Shot():
	m_sinCount(0.0f),
	m_sinPosY(0.0f),
	m_pos{0.0f,0.0f,0.0f},
	m_pModel(std::make_shared<Model>(kFileName))
{
	// モデルスケール設定
	m_pModel->SetScale(kScaleVec);
}

Shot::~Shot()
{
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

	// 上下移動
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kSinSwing;
	m_pos.y += m_sinPosY;

	// モデル座標更新
	m_pModel->SetPos(m_pos);
	// モデル回転更新
	m_pModel->SetRot(VGet(0.0f, playerRot, 0.0f));
}

void Shot::Draw()
{
	// 描画
	m_pModel->Draw();

#ifdef _DEBUG
	DrawFormatString(0, 160, 0xffffff, "遠距離攻撃武器座標：%f,%f,%f"
	, m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG

}
