#pragma once
#include "ItemBase.h"

/// <summary>
/// 円を書くように移動するアイテム
/// </summary>
class ItemRotationMove : public ItemBase
{
public:		// 関数
	ItemRotationMove(int modelHandle);
	virtual ~ItemRotationMove();

	virtual void Init();
	virtual void Update();

private:	// 変数
	float m_centerX;	// 円の中心のX位置
	float m_centerZ;	// 円の中心のZ位置
};

