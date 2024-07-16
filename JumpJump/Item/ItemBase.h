#include "DxLib.h"
#pragma once
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const {}

protected:	// 変数
	int m_modelHandle;	// モデルハンドル
	int  m_psH;			// ピクセルシェーダハンドル
	int m_vsH;			// 頂点シェーダハンドル
	float m_rad;		// 半径
	float m_scale;		// スケール
	VECTOR m_pos;		// 位置
	VECTOR m_angle;
};