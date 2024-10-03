#pragma once
#include "ItemBase.h"

#include <memory>

class ItemStop : public ItemBase
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">初期座標</param>
	ItemStop(VECTOR pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemStop();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init()override final;

	/// <summary>
	/// 移動方向更新
	/// </summary>
	void MoveDirectionUpdate() override final;

	/// <summary>
	/// 移動更新
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate() override final;

private:
	/// <summary>
	/// 角度更新
	/// </summary>
	virtual void AngleUpdate();

private:
	float m_angleX;			// X角度
	float m_moveSinCount;	// 移動カウント
};

