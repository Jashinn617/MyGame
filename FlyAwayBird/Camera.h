#pragma once
#include "DxLib.h"

class Player;

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="player">プレイヤーへの参照</param>
	void Update(const Player& player);

	/// <summary>
	/// 位置の取得
	/// </summary>
	/// <returns>現在位置</returns>
	const VECTOR GetPos()const { return m_pos; }

private:	// 変数
	VECTOR m_pos;	// 位置
};

