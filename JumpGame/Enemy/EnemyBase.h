#pragma once
#include "DxLib.h"

// 敵クラスのベース
class EnemyBase abstract
{
public:
	EnemyBase(int modelHandle);
	virtual ~EnemyBase();

	virtual void Update() abstract;	// 更新
	virtual void Draw();	// 描画

	// モデルハンドルの取得
	int GetModelHandle()const { return m_modelHandle; }

	// 
	const VECTOR& GetPos() const { return m_pos; }
	void SetPos(const VECTOR pos) { m_pos = pos; }
	void SetModelPos();

protected:
	int m_modelHandle;
	VECTOR m_pos;
};

