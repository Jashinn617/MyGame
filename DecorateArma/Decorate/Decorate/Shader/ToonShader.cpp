#include "ToonShader.h"

#include "../Utility/Game.h"

#include <cassert>

ToonShader::ToonShader()
{
	/*シェーダのロード
	ロードに失敗したら止める*/
	m_pixelShaderH = LoadPixelShader("Data/Shader/PixelShader/ToonPixelShader.pso");
	assert(m_pixelShaderH != -1);
	m_pixelShaderFieldH = LoadPixelShader("Data/Shader/PixelShader/ToonFieldPixelShader.pso");
	assert(m_pixelShaderFieldH != -1);

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

ToonShader::~ToonShader()
{
	/*ピクセルシェーダのデリート*/
	DeleteShader(m_pixelShaderH);
	DeleteShader(m_pixelShaderFieldH);
	/*定数バッファのデリート*/
	DeleteShaderConstantBuffer(m_cbufferLightDirH);
	DeleteShaderConstantBuffer(m_cbufferCameraTargetPosH);
	DeleteShaderConstantBuffer(m_cbufferCameraPosH);
}

void ToonShader::SetShader(int vertexH)
{
	// 頂点シェーダが無かった場合は止める
	assert(vertexH != -1);

	// ライトの向きの取得
	m_pCbufferLightDir[0] = GetLightDirection();
	// カメラのターゲットの位置の取得
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();
	// カメラの位置の取得
	m_pCbufferCameraPos[0] = GetCameraPosition();
	/*書き込んだ値をGPUに反映する*/
	// ライトの向き
	UpdateShaderConstantBuffer(m_cbufferLightDirH);
	SetShaderConstantBuffer(m_cbufferLightDirH, DX_SHADERTYPE_PIXEL, 0);
	// カメラのターゲットの位置
	UpdateShaderConstantBuffer(m_cbufferCameraTargetPosH);
	SetShaderConstantBuffer(m_cbufferCameraTargetPosH, DX_SHADERTYPE_PIXEL, 1);
	// カメラの位置
	UpdateShaderConstantBuffer(m_cbufferCameraPosH);
	SetShaderConstantBuffer(m_cbufferCameraPosH, DX_SHADERTYPE_PIXEL, 2);

	// シェーダを適用する
	MV1SetUseOrigShader(true);

	// 頂点シェーダを適用する
	SetUseVertexShader(vertexH);

	// ピクセルシェーダのセット
	SetUsePixelShader(m_pixelShaderH);
}

void ToonShader::SetShaderField(int vertexH)
{
	// 頂点シェーダが無かった場合は止める
	assert(vertexH != -1);

	// ライトの向きの取得
	m_pCbufferLightDir[0] = GetLightDirection();
	// カメラのターゲットの位置の取得
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();
	// カメラの位置の取得
	m_pCbufferCameraPos[0] = GetCameraPosition();
	/*書き込んだ値をGPUに反映する*/
	// ライトの向き
	UpdateShaderConstantBuffer(m_cbufferLightDirH);
	SetShaderConstantBuffer(m_cbufferLightDirH, DX_SHADERTYPE_PIXEL, 0);
	// カメラのターゲットの位置
	UpdateShaderConstantBuffer(m_cbufferCameraTargetPosH);
	SetShaderConstantBuffer(m_cbufferCameraTargetPosH, DX_SHADERTYPE_PIXEL, 1);
	// カメラの位置
	UpdateShaderConstantBuffer(m_cbufferCameraPosH);
	SetShaderConstantBuffer(m_cbufferCameraPosH, DX_SHADERTYPE_PIXEL, 2);

	// シェーダを適用する
	MV1SetUseOrigShader(true);

	// 頂点シェーダを適用する
	SetUseVertexShader(vertexH);

	// ピクセルシェーダのセット
	SetUsePixelShader(m_pixelShaderFieldH);
}

void ToonShader::ShaderEnd()
{
	/*シェーダを使わない*/
	MV1SetUseOrigShader(false);
}
