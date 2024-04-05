#pragma once
#include "DxLib.h"

/// <summary>
/// 3D座標空間にスプライトを表示する仕組み(ピボットは中心固定、画像のgraphは外で管理)
/// </summary>
class WorldSprite
{
public:

	WorldSprite();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="textureGraph">テクスチャの画像ハンドル</param>
	/// <param name="chipPixelSize">スプライトの1チップのピクセルサイズ</param>
	/// <param name="spriteNo">スプライト番号</param>
	void Init(int textureGraph, int chipPixelSize, int spriteNo);
	/// <summary>
	/// サイズとポジションに応じて4頂点分の頂点位置を調整
	/// </summary>
	/// <param name="pos">ポジション</param>
	/// <param name="spriteSize">配置するワールドスプライトのサイズ</param>
	void SetTransform(const VECTOR& pos, float spriteSize);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	const VECTOR& GetPos()const { return m_pos; }

private:
	int m_textureGraph;		// スプライトを作成する元テクスチャのグラフィックハンドル
	VECTOR m_pos;				// 描画ポジション
	VERTEX3D m_vertex[4];		// 頂点バッファ
	WORD m_index[6];			// インデックスバッファ
};

