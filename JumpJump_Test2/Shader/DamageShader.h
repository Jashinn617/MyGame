#pragma once
#include "DxLib.h"

#include <memory>

class DamageShader
{
public:
	DamageShader();
	virtual ~DamageShader();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void DrawFirst(int shaderType);

	void UseShader();

	void DrawEnd();

	bool GetUseShader()const { return m_isUseShader; }

private:
	/*頂点シェーダ*/
	int m_vertexShader1FrameH;				//頂点シェーダー1フレームハンドル
	int m_vertexShader4FrameH;				//頂点シェーダー4フレームハンドル
	int m_vertexShader8FrameH;				//頂点シェーダー8フレームハンドル
	int m_vertexShaderNormal4FrameH;		//頂点シェーダー4フレーム法線マップありハンドル
	int m_vertexShaderNormal8FrameH;		//頂点シェーダー8フレーム法線マップありハンドル
	/*ピクセルシェーダ*/
	int m_pixelShaderH;				// ピクセルシェーダのハンドル

	int m_graphH;					// 画像ハンドル

	/*定数バッファのハンドル*/
	int m_cbufferTimeH;					// タイム
	int m_cbufferLightDirH;				// ライトの向き
	int m_cbufferCameraTargetPosH;		// カメラのターゲットの位置
	int m_cbufferCameraPosH;			// カメラの位置

	/*定数バッファをいじるためのアドレスのコピー*/
	float* m_cbufferTime;					// タイム
	VECTOR* m_pCbufferLightDir;				// ライトの向き
	VECTOR* m_pCbuffferCameraTargetPos;		// カメラのターゲットの位置
	VECTOR* m_pCbufferCameraPos;			// カメラの位置

	float m_colDensity;		// 色の濃さ

	bool m_isUseShader;		// シェーダを使うかどうか
};

