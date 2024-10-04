#pragma once
#include "DxLib.h"

#include <math.h>
#include <memory>

class Circle
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="center">中心</param>
	/// <param name="radius">半径</param>
	/// <param name="height">高さ</param>
	Circle(const VECTOR& center, float radius, float height);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Circle();

	/// <summary>
	/// 当たり判定のデバッグ表示
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="that">自身</param>
	/// <returns>当たっているかどうか</returns>
	bool IsCollide(const std::shared_ptr<Circle> that)const;

	/// <summary>
	/// 球の中心の取得
	/// </summary>
	/// <returns>球の中心</returns>
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

