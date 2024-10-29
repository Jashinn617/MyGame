#pragma once
#include "EnemyBase.h"

/// <summary>
/// ロボット
/// </summary>
class EnemyRobot : public EnemyBase
{
public:		// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期座標</param>
	EnemyRobot(VECTOR pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyRobot();

	void Init() override final;
};

