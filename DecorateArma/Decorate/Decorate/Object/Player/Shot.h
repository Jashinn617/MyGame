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

private:	// 構造体

	struct Bullet
	{
		VECTOR pos;
		std::shared_ptr<Model> model;
	};

private:	// 関数

	void Attack(float rot);

private:
	float m_sinCount;	// 上下移動カウント
	float m_sinPosY;	// サイン計算に使うY座標

	VECTOR m_pos;		// 座標


	std::shared_ptr<Model> m_pModel;

};

