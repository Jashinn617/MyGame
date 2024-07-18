#include "ItemBase.h"
#include <assert.h>

namespace
{
	constexpr float kScale = 0.05f;
}

ItemBase::ItemBase(int modelHandle):
	m_modelHandle(-1),
	m_psH(-1),
	m_vsH(-1),
	m_rad(4),
	m_scale(0),
	m_pos{0,0,0},
	m_angle(0),
	m_angleSpeed(0)
{
	// モデルの読み込み
	m_modelHandle = MV1DuplicateModel(modelHandle);
	assert(m_modelHandle != -1);
	// シェーダのロード
	m_psH = LoadPixelShader("PixelTest.pso");
	assert(m_psH != -1);
	m_vsH = LoadVertexShader("VertexShader.vso");
	assert(m_vsH != -1);

	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}

ItemBase::~ItemBase()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void ItemBase::Draw()
{
	// 当たり判定のデバッグ表示
#ifdef _DEBUG
	DrawSphere3D(m_pos, m_rad, 32, 0xff0000, 0xff00000, false);
#endif // _DEBUG
	// シェーダを適用する
	MV1SetUseOrigShader(true);
	SetUseVertexShader(m_vsH);
	SetUsePixelShader(m_psH);
	// モデルの描画
	MV1DrawModel(m_modelHandle);
	// シェーダを無効化する
	MV1SetUseOrigShader(false);
	SetUseVertexShader(-1);
	SetUsePixelShader(-1);
}

void ItemBase::UpdateAngle()
{
}
