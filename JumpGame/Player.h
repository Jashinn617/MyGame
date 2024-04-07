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

	const VECTOR& GetPos()const;
	const VECTOR& GetDir()const { return m_dir; }
	const float GetRad()const { return m_rad; }

private:
	// 位置
	VECTOR m_pos;
	// 移動量
	VECTOR m_move;

	// 移動力
	VECTOR m_velocity;
	// 回転方向
	VECTOR m_dir;
	// 3Dモデル
	int m_modelHandle;
	// 半径
	float m_rad;
	// ジャンプ力
	float m_jumpPower;
	// ジャンプ中かどうか
	bool m_isJump;

private:	// 定数
	static constexpr float kGravity = 0.025f;	// 重力
	static constexpr float kJumpHeight = 0.5f;	// ジャンプ力
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;	// Y軸方向の向き


};

