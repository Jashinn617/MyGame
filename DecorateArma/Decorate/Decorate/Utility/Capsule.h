#pragma once
#include "DxLib.h"

#include <memory>

/// <summary>
/// 当たり判定用のカプセル
/// </summary>
class Capsule
{
public:	// 構造体
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="topPos">判定始点</param>
	/// <param name="bottomPos">判定終点</param>
	/// <param name="radius">半径</param>
	Capsule(const VECTOR& topPos, const VECTOR& bottomPos, float radius);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Capsule();

	/// <summary>
	/// 当たり判定のデバッグ表示
	/// </summary>
	/// <param name="color">カプセルの色</param>
	void DebugDraw(unsigned int color);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="target">相手の当たり判定のカプセル</param>
	/// <returns>当たっているかどうか</returns>
	bool IsCollide(const std::shared_ptr<Capsule> target) const;

	

	const VECTOR& GetTopPos()const { return *topPos; }

	const VECTOR& GetBottomPos()const { return *bottomPos; }

	/// <summary>
	/// 半径の取得
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius()const { return m_radius; }


private:
	const float m_radius;			// 半径
	const VECTOR* topPos;			// 判定始点
	const VECTOR* bottomPos;		// 判定終点
};