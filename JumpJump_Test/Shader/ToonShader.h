#pragma once

#include "DxLib.h"

class ToonShader
{
public:
	ToonShader();
	virtual ~ToonShader();

	void Update();
	void SetShader(int shaderType);
	void SetShaderField(int shaderType);
	void ShaderEnd();

private:
	int m_vertexShader4FrameH;		// 頂点シェーダ4フレームのハンドル	
	int m_vertexShader8FrameH;		// 頂点シェーダ8フレームのハンドル
	int m_pixelShaderH;				// ピクセルシェーダのハンドル
	int m_pixelShaderFieldH;		// ピクセルシェーダのフィールドに適用するハンドル
	int m_graphH;
	/*定数バッファのハンドル*/
	int m_cbufferLightDirH;				// ライトの向き
	int m_cbufferCameraTargetPosH;		// カメラのターゲットの位置
	int m_cbufferCameraPosH;			// カメラの位置

	/*定数バッファをいじるためのアドレスのコピー*/
	VECTOR* m_pCbufferLightDir;				// ライトの向き
	VECTOR* m_pCbuffferCameraTargetPos;		// カメラのターゲットの位置
	VECTOR* m_pCbufferCameraPos;			// カメラの位置
};

