#include "WorldSprite.h"

void WorldSprite::Init(int textureGraph, int chipPixelSize, int spriteNo)
{
	this->m_textureGraph = textureGraph;

	// 初期化時に固定しているが、変更したければ自分で関数を追加する必要がある
	// 4頂点分のUVデータを設定する
	int texW, texH;
	GetGraphTextureSize(textureGraph, &texW, &texH);
	int chipNum = texW / chipPixelSize;
	int chipNoX = spriteNo % chipNum;
	int chipNoY = spriteNo / chipNum;
	float oneChipUVRate = 1.0f / static_cast<float>(chipNum);	// テクスチャ全部を1.0とした時のchip一個に対するUVのサイズ
	m_vertex[0].u = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[0].v = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[1].u = (chipNoX + 1.0f) * oneChipUVRate;
	m_vertex[1].v = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[2].u = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[2].v = (chipNoX + 1.0f) * oneChipUVRate;
	m_vertex[3].u = (chipNoX + 1.0f) * oneChipUVRate;
	m_vertex[3].v = (chipNoX + 1.0f) * oneChipUVRate;

	// ディフューズ、スぺキュラは初期化時に固定
	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].dif = GetColorU8(255, 255, 255, 255);
		m_vertex[i].spc = GetColorU8(0, 0, 0, 0);
		m_vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);	//	回転をサポートしないのでノーマルも固定

		// 補助テクスチャをサポートしないのでUV固定
		m_vertex[i].sv = 0.0f;
		m_vertex[i].sv = 0.0f;
	}

	// 2ポリゴン分のインデックスデータをセット
	m_index[0] = 0;
	m_index[1] = 1;
	m_index[2] = 2;
	m_index[3] = 3;
	m_index[4] = 2;
	m_index[5] = 1;
}

void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
	this->m_pos = pos;
	// ピボット中心で設定
	m_vertex[0].pos = VScale(VGet(-1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	m_vertex[0].pos = VScale(VGet(1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	m_vertex[0].pos = VScale(VGet(-1.0f, -1.0f, 0.0f), spriteSize * 0.5f);
	m_vertex[0].pos = VScale(VGet(1.0f, -1.0f, 0.0f), spriteSize * 0.5f);

	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].pos = VAdd(m_vertex[i].pos, pos);
	}
}

void WorldSprite::Draw()
{
	// 2ポリゴンの描画
	DrawPolygonIndexed3D(m_vertex, 4, m_index, 2, m_textureGraph, false);
}
