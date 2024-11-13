#include "RecoveryItem.h"
#include "Model.h"
#include "CharacterBase.h"

#include "../Utility/CollisionShape.h"

namespace
{
	constexpr float kRadius = 35.0f;					// 半径
	constexpr float kHeight = -5.0f;					// 高さ
	constexpr float kApproachRadius = 200.0f;			// 近付く範囲の半径
	constexpr float kApproachHeight = -5.0f;			// 近付く範囲の高さ
	constexpr float kFlyHeight = 90.0f;					// プレイヤーの方向に飛んでいく高さ
	constexpr float kSpeed = 10.0f;						// 近付く速度
	constexpr VECTOR kScale = { 0.3f,0.3f,0.3f };		// モデルスケール
}

RecoveryItem::RecoveryItem(VECTOR pos)
{
	// 座標設定
	m_characterInfo.pos = pos;
}

RecoveryItem::~RecoveryItem()
{
}

void RecoveryItem::Init()
{
	// モデル設定
	m_pModel = std::make_shared<Model>(m_modelH);
	// 当たり判定作成(球)
	m_pColl = std::make_shared<CollisionShape>(m_characterInfo.pos, kRadius, kHeight);
	// 近付く範囲の当たり判定作成(球)
	m_pApproachColl = std::make_shared<CollisionShape>(m_characterInfo.pos, kApproachRadius, kApproachHeight);

	// モデル座標設定
	m_pModel->SetPos(m_characterInfo.pos);
	// モデルスケール設定
	m_pModel->SetScale(kScale);
}

void RecoveryItem::Update()
{
	// モデル座標更新
	m_pModel->SetPos(m_characterInfo.pos);
}

void RecoveryItem::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// 描画
	m_pModel->Draw();

	// 当たり判定デバッグ表示
	m_pColl->DebugDraw(0xff00ff);
	// 近付く範囲当たり判定デバッグ表示
	m_pApproachColl->DebugDraw(0x00ffff);
}

void RecoveryItem::OnGet(CharacterBase* pPlayer)
{
	// 衝突判定
	if (m_pColl->IsCollide(pPlayer->GetCollShape()))
	{
		m_characterInfo.isExist = false;
	}
}

void RecoveryItem::OnApproach(CharacterBase* pPlayer)
{
	// 衝突判定
	if (m_pApproachColl->IsCollide(pPlayer->GetCollShape()))
	{
		// プレイヤーまでのベクトルを求める
		VECTOR itemToPlayer = VSub(pPlayer->GetInfo().pos, m_characterInfo.pos);
		// 高さ調整
		itemToPlayer.y += kFlyHeight;
		// プレイヤーがいる方向を出す
		VECTOR direction = VNorm(itemToPlayer);

		// その方向に進む
		m_characterInfo.pos = VAdd(m_characterInfo.pos, VScale(direction, kSpeed));
	}
}