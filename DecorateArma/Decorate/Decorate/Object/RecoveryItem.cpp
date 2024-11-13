#include "RecoveryItem.h"
#include "Model.h"

#include "Player/Player.h"

#include "../Utility/CollisionShape.h"

namespace
{
	constexpr int kRecoveryNum = 30;					// HP回復量
	constexpr float kRadius = 35.0f;					// 半径
	constexpr float kHeight = -5.0f;					// 高さ
	constexpr float kApproachRadius = 200.0f;			// 近付く範囲の半径
	constexpr float kApproachHeight = -5.0f;			// 近付く範囲の高さ
	constexpr float kFlyHeight = 90.0f;					// プレイヤーの方向に飛んでいく高さ
	constexpr float kSpeed = 10.0f;						// 近付く速度
	constexpr float kSinSpeed = 0.04f;					// 昇降速度
	constexpr float kSinSwing = 0.5f;					// 昇降幅
	constexpr float kYRot = DX_PI_F * 180;				// モデルY角度
	constexpr VECTOR kScale = { 0.3f,0.3f,0.3f };		// モデルスケール
}

RecoveryItem::RecoveryItem(VECTOR pos):
	m_sinCount(0),
	m_sinPosY(0),
	m_isApproaching(0)
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
	m_pCollShape = std::make_shared<CollisionShape>(m_characterInfo.pos, kRadius, kHeight);
	// 近付く範囲の当たり判定作成(球)
	m_pApproachColl = std::make_shared<CollisionShape>(m_characterInfo.pos, kApproachRadius, kApproachHeight);

	// モデル座標設定
	m_pModel->SetPos(m_characterInfo.pos);
	// モデルスケール設定
	m_pModel->SetScale(kScale);
}

void RecoveryItem::Update()
{
	// プレイヤーを追いかけていないときは上下にふわふわ動く
	if (!m_isApproaching)
	{
		// 昇降
		m_sinCount += kSinSpeed;
		m_sinPosY = sinf(m_sinCount) * kSinSwing;
		m_characterInfo.pos.y += m_sinPosY;
	}


	// モデル座標更新
	m_pModel->SetPos(m_characterInfo.pos);
}

void RecoveryItem::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// 描画
	m_pModel->Draw();

	// 当たり判定デバッグ表示
	m_pCollShape->DebugDraw(0xff00ff);
	// 近付く範囲当たり判定デバッグ表示
	m_pApproachColl->DebugDraw(0x00ffff);
}

void RecoveryItem::OnGet(Player* pPlayer)
{
	// 衝突判定
	if (m_pCollShape->IsCollide(pPlayer->GetCollShape()))
	{
		// 回復処理
		pPlayer->OnRecovery(kRecoveryNum);
		// 存在を消す
		m_characterInfo.isExist = false;
	}
}

void RecoveryItem::OnApproach(ObjectBase* pPlayer)
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