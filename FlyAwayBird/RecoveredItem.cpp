#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"
#include "Player.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem(shared_ptr<Player> pPlayer):
	m_pos{0,0,0},
	m_handle(-1),
	m_w(0),
	m_h(0),
	m_isExist(true),
	m_sinCount(0),
	m_sinPosY(0),
	m_pPlayer(pPlayer),
	m_pSprite(nullptr)
{
	/*処理無し*/
}

RecoveredItem::~RecoveredItem()
{
	/*画像のデリート*/
	DeleteGraph(m_handle);
}

void RecoveredItem::Init(float x, float z)
{
	//画像のロード
	m_handle = LoadGraph("Data/Img/Cake.png");
	assert(m_handle != -1);
	// 画像サイズの取得
	GetGraphSize(m_handle, &m_w, &m_h);

	int rand = GetRand(1);
	if (rand == 0)
	{
		m_pos = VGet(x, kDownPosY, z);
	}
	else if (rand == 1)
	{
		m_pos = VGet(x, kUpPosY, z);
	}


	//ポインタの生成
	m_pSprite = make_shared<WorldSprite>();
	// スプライトの生成
	m_pSprite->Initialize(m_handle, m_w, m_h);
}

void RecoveredItem::Update()
{
	if (!m_isExist) return;
	// 当たり判定
	CollisionToPlayer(m_pPlayer->GetPos(), m_pPlayer->GetRadius());
	// 移動
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;
	// 位置、サイズの設定
	m_pSprite->SetTransform(m_pos, kSize);


}

void RecoveredItem::Draw()
{
	if (!m_isExist) return;
	m_pSprite->Draw();

	// 当たり判定の表示
#ifdef _DEBUG
	VECTOR pos = m_pos;
	pos.y -= 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0xff0000, 0xff0000, false);
#endif // _DEBUG
}

void RecoveredItem::CollisionToPlayer(VECTOR pVec, float pRad)
{
	// プレイヤーとアイテムの半径の合計
	float rad = kRadius + pRad;
	// プレイヤーとアイテムの距離の計算
	VECTOR dirVec = VSub(m_pos, pVec);
	float dir = VSize(dirVec);
	
	// プレイヤーと当たっているかどうか
	if (dir < rad)
	{
#ifdef _DEBUG
		printfDx("当たった");
#endif // _DEBUG
		m_isExist = false;
	}
}
