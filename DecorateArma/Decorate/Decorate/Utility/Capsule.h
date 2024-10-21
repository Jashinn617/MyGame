#pragma once
#include "DxLib.h"

#include <memory>

/// <summary>
/// 当たり判定用のカプセル
/// </summary>
class Capsule
{
private:	// 構造体
	/// <summary>
	/// 当たり判定用情報
	/// </summary>
	struct CollInfo
	{
		VECTOR topPos;			// 判定始点
		VECTOR bottomPos;		// 判定終点
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="topPos">判定始点</param>
	/// <param name="bottomPos">判定終点</param>
	/// <param name="radius">半径</param>
	Capsule(const VECTOR topPos, const VECTOR bottomPos, float radius);

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

	/// <summary>
	/// カプセルの当たり判定用情報の取得
	/// </summary>
	/// <returns>当たり判定用情報</returns>
	const CollInfo& GetCollInfo()const { return m_collInfo; }

	/// <summary>
	/// 半径の取得
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius()const { return m_radius; }


private:
	float m_radius;				// 半径
	CollInfo m_collInfo;		// 当たり判定用情報
};