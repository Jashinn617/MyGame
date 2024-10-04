#pragma once

#include <memory>
#include <vector>

class ObjectBase;

class Collision
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collision();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Collision();

	/// <summary>
	/// 当たり判定処理
	/// </summary>
	/// <param name="my">自身</param>
	/// <param name="target">相手</param>
	void Update(ObjectBase* my, ObjectBase* target);
};

