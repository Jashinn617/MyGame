#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem():
	m_pos{0,0,0},
	m_handle(-1),
	m_w(0),
	m_h(0),
	m_sinCount(0),
	m_sinPosY(0),
	m_pSprite(nullptr)
{
	/*処理無し*/
}

RecoveredItem::~RecoveredItem()
{
	/*画像のデリート*/
	DeleteGraph(m_handle);
}

void RecoveredItem::Init()
{
	//画像のロード
	m_handle = LoadGraph("Data/Img/Cake.png");
	assert(m_handle != -1);
	// 画像サイズの取得
	GetGraphSize(m_handle, &m_w, &m_h);

	m_pos.y = kDownPosY;

	//ポインタの生成
	m_pSprite = make_shared<WorldSprite>();
	// スプライトの生成
	m_pSprite->Initialize(m_handle, m_w, m_h);
}

void RecoveredItem::Update()
{
	// 移動
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;
	// 位置、サイズの設定
	m_pSprite->SetTransform(m_pos, kSize);

}

void RecoveredItem::Draw()
{
	m_pSprite->Draw();

	// 当たり判定の表示
#ifdef _DEBUG
	VECTOR pos = m_pos;
	pos.y -= 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0xff0000, 0xff0000, false);
#endif // _DEBUG
}
