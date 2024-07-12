#pragma once
#include "DxLib.h"

class EnemyBase
{
public:
	EnemyBase(int modelHandle);
	virtual ~EnemyBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const { return m_pos; }
	const float GetRad() const { return m_rad; }

protected:	// 関数
	int GetModelHandle()const { return m_modelHandle; }

protected:	// 変数
	int m_modelHandle;	// モデルハンドル
	float m_rad;		// 半径
	float m_scale;		// スケール
	VECTOR m_pos;		// 位置
	VECTOR m_angle;		// 回転
};

