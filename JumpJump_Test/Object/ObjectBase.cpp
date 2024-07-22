#include "ObjectBase.h"
#include "Model.h"
#include "ObjectManager.h"
#include "../Util/Time.h"
#include "Player.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;	// 最大当たり判定ポリゴン数
	constexpr int kMaxColHitTryNum = 16;	// 壁押し出し処理の最大試行回数
	constexpr float kColHitSlideLength = 1.0f;		// 壁押し出し時にスライドさせる距離
	constexpr float kMove = 0.01f;			// 移動したかを判断するための変数
	constexpr float kWallPolyBorder = 0.4f;	// 壁ポリゴンか床ポリゴン化を判断するための変数
	constexpr float kWallPolyHeight = 5.0f;	// 壁ポリゴンと判断するための高さ変数
	constexpr int kExistTimeCount = 10;		// 死んでからの時間
	constexpr float kHeadHeight = 40.0f;	// 頭の高さ
}


ObjectBase::ObjectBase():
	m_objSize(0.0f),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_modelH(-1),
	m_isMove(false),
	m_isHit(false),
	m_wallNum(0),
	m_floorNum(0),
	m_hitDim{},
	m_pWallPoly{},
	m_pFloorPoly{},
	m_pPoly(nullptr),
	m_lineRes{},
	m_oldPos{0,0,0},
	m_nextPos{0,0,0},
	m_pExistCountTime(std::make_shared<Time>(kExistTimeCount))
{
	m_info.pos = VGet(0.0f, 0.0f, 0.0f);
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.isExist = true;
}

ObjectBase::~ObjectBase()
{
}

bool ObjectBase::IsExistCount()
{
	// 規定時間が過ぎたら存在を消す
	if (m_pExistCountTime->Update())
	{
		return true;
	}
	return false;
}

void ObjectBase::End()
{
	*m_pWallPoly = nullptr;
	*m_pFloorPoly = nullptr;
	m_pPoly = nullptr;
}

void ObjectBase::MoveCollFieldUpdate(ObjectBase* pField)
{
	// 移動前の座標を保存しておく
	m_oldPos = m_info.pos;
	// 移動後の座標を計算する
	m_nextPos = VAdd(m_oldPos, GetInfo().vec);

	// プレイヤーの周囲にあるステージポリゴンを取得する
	// 移動距離も考慮してから検出する
	m_hitDim = MV1CollCheck_Sphere(pField->GetModel()->GetModelHandle(), -1, GetInfo().pos,
		dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius() + VSize(GetInfo().vec);
}

void ObjectBase::CheckWallAndFloor()
{
	

}

void ObjectBase::FixPosWithWall()
{
}

void ObjectBase::FixPosWithWallInternal()
{
}

void ObjectBase::FixPosWithFloor()
{
}
