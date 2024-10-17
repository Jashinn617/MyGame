#pragma once

#include "DxLib.h"

/// <summary>
/// トゥーンシェーダを設定するクラス
/// </summary>
class ToonShader
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ToonShader();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ToonShader();

	/// <summary>
	/// シェーダの設定
	/// </summary>
	/// <param name="vertexH">頂点シェーダハンドル</param>
	void SetShader(int vertexH);

	/// <summary>
	/// フィールドシェーダの設定
	/// </summary>
	/// <param name="vertexH">頂点シェーダハンドル</param>
	void SetShaderField(int vertexH);

	/// <summary>
	/// シェーダを使わない設定する
	/// </summary>
	void ShaderEnd();

private:
	/*ピクセルシェーダ*/
	int m_pixelShaderH;				// ピクセルシェーダのハンドル
	int m_pixelShaderFieldH;		// ピクセルシェーダのフィールドに適用するハンドル

	/*定数バッファのハンドル*/
	int m_cbufferLightDirH;				// ライトの向き
	int m_cbufferCameraTargetPosH;		// カメラのターゲットの位置
	int m_cbufferCameraPosH;			// カメラの位置

	/*定数バッファをいじるためのアドレスのコピー*/
	VECTOR* m_pCbufferLightDir;				// ライトの向き
	VECTOR* m_pCbuffferCameraTargetPos;		// カメラのターゲットの位置
	VECTOR* m_pCbufferCameraPos;			// カメラの位置
};