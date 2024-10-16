#pragma once

/// <summary>
/// 頂点シェーダのロードを行うクラス
/// </summary>
class VertexShader
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	VertexShader();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~VertexShader();
	
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