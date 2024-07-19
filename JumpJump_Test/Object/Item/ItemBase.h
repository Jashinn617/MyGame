#include "DxLib.h"
#pragma once
class ItemBase
{
public:
	ItemBase(int modelHandle);
	virtual ~ItemBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const {}

	void SetPos(const VECTOR pos) { m_pos = pos; }
	void SetAngleSpeed(const float angle) { m_angleSpeed = angle; }
	void SetRadius(const float radius) { m_radius = radius; }

protected:	// 関数
	void UpdateAngle();

protected:	// 変数
	int m_modelHandle;	// モデルハンドル
	int  m_psH;			// ピクセルシェーダハンドル
	int m_vsH;			// 頂点シェーダハンドル
	float m_rad;		// 半径
	float m_scale;		// スケール
	VECTOR m_pos;		// 位置
	float m_angle;		// 角度
	float m_angleSpeed;		// 回転速度
	float m_radius;			// 回転する円の半径
};