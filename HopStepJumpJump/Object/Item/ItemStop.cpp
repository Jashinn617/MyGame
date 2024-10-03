#include "ItemStop.h"

#include "../Circle.h"
#include "../Model.h"

#include "../../Shader/ToonShader.h"

#include <math.h>

namespace
{
	constexpr float kAngleZ = 270.0f * DX_PI_F / 180.0f;	// Z軸の角度
	constexpr float kMoveSinSpeed = 0.03f;					// 上下移動の速度
	constexpr float kMoveSwing = 0.1f;						// 上下移動の移動幅
	constexpr float kAngleSpeed = 0.05f;					// 回転スピード
	constexpr float kModelScalse = 0.21f;					// モデルスケール
	constexpr float kItemSize = 13;							// サイズ
	constexpr float kHeight = -10.0f;						// 高さ
}

ItemStop::ItemStop(VECTOR pos):
	m_angleX(0),
	m_moveSinCount(0)
{
	// 座標の初期化
	m_info.pos = pos;
	// サイズの設定
	m_objSize = kItemSize;
	// 当たり判定用球ポインタ作成
	m_pCircle = std::make_shared<Circle>(m_info.pos, kItemSize, kHeight);
	// 角度初期化
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	// 回転スピードの設定
	m_moveData.rotSpeed = kAngleSpeed;
}

ItemStop::~ItemStop()
{
	/*処理無し*/
}

void ItemStop::Init()
{
	// モデルポインタ作成
	m_pModel = std::make_shared<Model>(m_modelH);
	// モデルスケール設定
	m_pModel->SetScale(VGet(kModelScalse, kModelScalse, kModelScalse));
	// モデル角度初期化
	m_pModel->SetRot(m_info.rot);
	// モデル座標初期化
	m_pModel->SetPos(m_info.pos);
}

void ItemStop::MoveDirectionUpdate()
{
	// 上下移動
	m_moveSinCount += kMoveSinSpeed;
	m_moveDirectionVec.y = sinf(m_moveSinCount) * kMoveSwing;	
}

VECTOR ItemStop::MoveUpdate()
{
	// 移動方向の更新
	MoveDirectionUpdate();
	// 角度更新
	AngleUpdate();

	return m_moveDirectionVec;
}

void ItemStop::AngleUpdate()
{
	// その場で回転する
	m_angleX += kAngleSpeed;
	// モデル角度更新
	m_pModel->SetRot(VGet(m_angleX, 0.0f, kAngleZ));
}
