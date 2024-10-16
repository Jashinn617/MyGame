#pragma once
#include "DxLib.h"

#include <memory>

/// <summary>
/// 当たり判定用の球
/// </summary>
class Sphere
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <param name="radius">半径</param>
	/// <param name="height">高さ</param>
	Sphere(const VECTOR& center, float radius, float height);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Sphere();

	/// <summary>
	/// 当たり判定のデバッグ表示
	/// </summary>
	/// <param name="color">球の色</param>
	void DebugDraw(unsigned int color);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="target">相手の当たり判定の球</param>
	/// <returns>当たっているかどうか</returns>
	bool IsCollide(const std::shared_ptr<Sphere> target) const;

	/// <summary>
	/// 球の中心座標の取得
	/// </summary>
	/// <returns>円の中心</returns>
	const VECTOR& GetCenter() const { return *m_center; }

	/// <summary>
	/// 半径の取得
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius()const { return m_radius; }

private:	// 変数
	const float m_radius;	// 半径
	const float m_height;	// 高さ
	const VECTOR* m_center;	// 中心座標
};

