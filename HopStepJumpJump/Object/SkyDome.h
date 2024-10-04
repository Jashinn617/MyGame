#pragma once
#include "DxLib.h"

#include <memory>

class Model;

class SkyDome
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SkyDome();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SkyDome();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="pos">座標</param>
	void Update(VECTOR pos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	float m_rot;						// 回転率
	std::shared_ptr<Model> m_pModel;	// モデルポインタ
};

