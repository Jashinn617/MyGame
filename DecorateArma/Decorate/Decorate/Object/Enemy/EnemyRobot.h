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
	virtual ~EnemyRobot();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override final;

private:	// 関数
	/// <summary>
	/// 角度更新
	/// (モデルの前後が逆のため、反転した向きを出している)
	/// </summary>
	void UpdateAngle() override final;
};

