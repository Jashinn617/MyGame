#pragma once
#include "EnemyBase.h"

#include <memory>

class EnemySkull : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期座標</param>
	/// <param name="speed">移動速度</param>
	EnemySkull(VECTOR pos, float speed);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemySkull();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override final;

	/// <summary>
	/// 移動方向更新
	/// </summary>
	void MoveDirectionUpdate() override final;

	/// <summary>
	/// 移動更新
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate() override final;
};

