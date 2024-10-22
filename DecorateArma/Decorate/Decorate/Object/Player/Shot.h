#pragma once

#include "DxLib.h"

#include <memory>

class Model;

/// <summary>
/// プレイヤーに追従する遠距離攻撃武器
/// </summary>
class Shot
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Shot();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Shot();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="playerPos">プレイヤー座標</param>
	/// <param name="playerRot">プレイヤー向き</param>
	void Update(const VECTOR& playerPos, float playerRot);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	VECTOR m_pos;	// 座標


	std::shared_ptr<Model> m_pModel;

};

