#pragma once

/// <summary>
/// 頂点シェーダのロードと設定を行うクラス
/// </summary>
class SetVertexShader
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SetVertexShader();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SetVertexShader();
	
	/// <summary>
	/// 頂点シェーダハンドルを設定する
	/// </summary>
	/// <param name="vertexShaderType">頂点タイプ</param>
	/// <returns>頂点シェーダハンドル</returns>
	int SetVertexShaderH(int vertexShaderType);

private:	// 変数
	/*頂点シェーダ*/
	int m_vertexShader1FrameH;				//頂点シェーダー1フレームハンドル
	int m_vertexShader4FrameH;				//頂点シェーダー4フレームハンドル
	int m_vertexShader8FrameH;				//頂点シェーダー8フレームハンドル
	int m_vertexShaderNormal4FrameH;		//頂点シェーダー4フレーム法線マップありハンドル
	int m_vertexShaderNormal8FrameH;		//頂点シェーダー8フレーム法線マップありハンドル
};