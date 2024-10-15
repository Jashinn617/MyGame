#include "ObjectBase.h"

#include "Model.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;		// 最大当たり判定ポリゴン数
	constexpr int kMaxColHitTryNum = 16;		// 壁押し出し処理の最大試行回数
	constexpr float kColHitSlideLength = 1.0f;	// 壁押し出し時にスライドさせる距離
	constexpr float kMove = 0.01f;				// 移動したかを判断するための変数
	constexpr float kWallPolyBorder = 0.4f;		// 壁ポリゴンか床ポリゴンかを判断する為の変数
	constexpr float kWallPolyHeight = 20.0f;	// 壁ポリゴンと判断するための高さ変数
}

ObjectBase::ObjectBase():
	m_modelH(-1),
	m_objSize(0.0f),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_isDamage(false),
	m_pModel(nullptr),
	m_pObjectManager(nullptr),
	m_wallNum(0),
	m_floorNum(0),
	m_isMove(false),
	m_isPolygonHit(false),
	m_prevPos{0.0f,0.0f,0.0f},
	m_nextPos{0.0f,0.0f,0.0f},
	m_pPoly(nullptr)
{
	// キャラクター情報の初期化
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.isExist = true;
}

ObjectBase::~ObjectBase()
{
	/*処理無し*/
}

void ObjectBase::End()
{
	/*ポインタの解放*/
	*m_pWallPoly = nullptr;
	*m_pFloorPoly = nullptr;
	m_pPoly = nullptr;
}

void ObjectBase::ShaderMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader)
{
	// モデルポインタが無い場合は何もしない
	if (m_pModel == nullptr)return;

	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// シェーダの設定

		// 描画
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// シェーダを使わない設定に戻す

}

void ObjectBase::MoveCollFieldUpdate(ObjectBase* pField)
{
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
