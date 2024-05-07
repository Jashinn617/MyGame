#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"
#include "Player.h"
#include "Util/Game.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem(shared_ptr<Player> pPlayer):
	m_pos{0,0,0},
	m_modelHandle(-1),
	m_chatchSeHandle(-1),
	m_w(0),
	m_h(0),
	m_isExist(true),
	m_sinCount(0),
	m_sinPosY(0),
	m_pPlayer(pPlayer)
{
	/*処理無し*/
}

RecoveredItem::~RecoveredItem()
{
	/*モデルのデリート*/
	MV1DeleteModel(m_modelHandle);
	/*SEのデリート*/
	DeleteSoundMem(m_chatchSeHandle);
}

void RecoveredItem::Init(float x, float z)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/Heart.mv1");
	assert(m_modelHandle != -1);
	/*SEのロード*/
	m_chatchSeHandle = LoadSoundMem("Data/Sound/SE/ItemChatchSE.mp3");
	assert(m_chatchSeHandle != -1);
	/*SEの音量調整*/
	ChangeVolumeSoundMem(kSeVolume, m_chatchSeHandle);

	int rand = GetRand(1);
	if (rand == 0)
	{
		m_pos = VGet(x, kDownPosY, z);
	}
	else if (rand == 1)
	{
		m_pos = VGet(x, kUpPosY, z);
	}
}

void RecoveredItem::Update()
{
	if (!m_isExist) return;

	// モデルのスケールを設定する
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f,0.0f, 0.0f));

	// 当たり判定
	CollisionToPlayer(m_pPlayer->GetPos(), m_pPlayer->GetRadius());
	// 移動
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;

	MV1SetPosition(m_modelHandle, m_pos);


}

void RecoveredItem::Draw()
{
	if (!m_isExist) return;

	MV1DrawModel(m_modelHandle);

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
		PlaySoundMem(m_chatchSeHandle, DX_PLAYTYPE_BACK);
		m_isExist = false;
	}
}
