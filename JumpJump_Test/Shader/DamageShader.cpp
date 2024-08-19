#include "DamageShader.h"
#include "../Util/Game.h"

#include <cassert>
#include <array>

DamageShader::DamageShader():
	m_colDensity(0),
	m_isUseShader(false)
{
	m_vertexShader4FrameH = LoadVertexShader("MV1VertexShader4Frame.vso");
	assert(m_vertexShader4FrameH != -1);
	m_vertexShader8FrameH = LoadVertexShader("MV1VertexShader8Frame.vso");
	assert(m_vertexShader8FrameH != -1);
	m_pixelShaderH = LoadPixelShader("DamageShader.pso");
	assert(m_pixelShaderH != -1);
	m_graphH = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	assert(m_graphH != -1);

	/*タイムの定数バッファの作成*/
	m_cbufferTimeH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferTimeH != -1);
	// アドレスの取得
	m_cbufferTime = static_cast<float*>(GetBufferShaderConstantBuffer(m_cbufferTimeH));

	/*ライトの定数バッファの作成*/
	m_cbufferLightDirH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferLightDirH != -1);
	// アドレスの取得
	m_pCbufferLightDir = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferLightDirH));

	/*カメラのターゲットの位置の定数バッファの作成*/
	m_cbufferCameraTargetPosH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferCameraTargetPosH != -1);
	// アドレスの取得
	m_pCbuffferCameraTargetPos = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferCameraTargetPosH));

	/*カメラの位置の定数バッファの作成*/
	m_cbufferCameraPosH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferCameraPosH != -1);
	m_pCbufferCameraPos = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferCameraPosH));
}

DamageShader::~DamageShader()
{
	// シェーダのデリート
	DeleteShader(m_vertexShader4FrameH);
	DeleteShader(m_vertexShader8FrameH);
	DeleteShader(m_pixelShaderH);
	DeleteShader(m_graphH);
	DeleteShaderConstantBuffer(m_cbufferTimeH);
	DeleteShaderConstantBuffer(m_cbufferLightDirH);
	DeleteShaderConstantBuffer(m_cbufferCameraTargetPosH);
	DeleteShaderConstantBuffer(m_cbufferCameraPosH);
}

void DamageShader::Update()
{
	m_colDensity = max(m_colDensity - 0.02f, 0.0f);

	if (m_colDensity <= 0.0f)
	{
		m_isUseShader = false;
	}

	m_cbufferTime[0] = m_colDensity;
}

void DamageShader::DrawFirst(int shaderType)
{
	// ライトの向きの取得
	m_pCbufferLightDir[0] = GetLightDirection();
	// カメラのターゲットの位置の取得
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();
	// カメラの位置の取得
	m_pCbufferCameraPos[0] = GetCameraPosition();

	/*書き込んだ値をGPUに反映する*/
	// タイム
	UpdateShaderConstantBuffer(m_cbufferTimeH);
	SetShaderConstantBuffer(m_cbufferTimeH, DX_SHADERTYPE_PIXEL, 0);
	// ライトの向き
	UpdateShaderConstantBuffer(m_cbufferLightDirH);
	SetShaderConstantBuffer(m_cbufferLightDirH, DX_SHADERTYPE_PIXEL, 1);
	// カメラのターゲットの位置
	UpdateShaderConstantBuffer(m_cbufferCameraTargetPosH);
	SetShaderConstantBuffer(m_cbufferCameraTargetPosH, DX_SHADERTYPE_PIXEL, 2);
	// カメラの位置
	UpdateShaderConstantBuffer(m_cbufferCameraPosH);
	SetShaderConstantBuffer(m_cbufferCameraPosH, DX_SHADERTYPE_PIXEL, 3);

	// シェーダを適用する
	MV1SetUseOrigShader(true);

	// モデルの頂点タイプによって適応させるシェーダを変える
	if (shaderType == DX_MV1_VERTEX_TYPE_4FRAME)
	{
		SetUseVertexShader(m_vertexShader4FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_8FRAME)
	{
		SetUseVertexShader(m_vertexShader8FrameH);
	}
	else
	{
		MV1SetUseOrigShader(false);
	}

	// ピクセルシェーダのセット
	SetUsePixelShader(m_pixelShaderH);
}

void DamageShader::UseShader()
{
	// シェーダを使う
	m_isUseShader = true;
	m_colDensity = 1.0f;
}

void DamageShader::DrawEnd()
{
	// 描画の終了
	MV1SetUseOrigShader(false);
	SetShaderConstantBuffer(-1, DX_SHADERTYPE_PIXEL, 8);
}
