#pragma once
#include "DxLib.h"
#include <memory>

using namespace std;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const;

	/// <summary>
	/// モデルハンドルの取得
	/// </summary>
	/// <returns></returns>
	int GetModelHandle()const { return m_modelHandle; }

	const VECTOR& GetPos()const { return m_pos; }
	const VECTOR& GetDir()const { return m_dir; }

private:
	// 位置
	VECTOR m_pos;
	// 移動力
	VECTOR m_velocity;
	// 回転方向
	VECTOR m_dir;
	// 3Dモデル
	int m_modelHandle;

};

