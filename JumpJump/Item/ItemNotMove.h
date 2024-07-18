#pragma once
#include "ItemBase.h"

/// <summary>
/// 上下移動をしながら回転するアイテム
/// </summary>
class ItemNotMove : public ItemBase
{
public:		// 関数
	ItemNotMove(int modelHandle);
	virtual ~ItemNotMove();

	virtual void Init();
	virtual void Update();

private:	// 変数
	float m_angleX;			// X軸の角度
	float m_moveSinCount;	// 移動のカウント
	float m_posY;			// Y位置
};

