#pragma once
#include "DxLib.h"
#include <memory>

using namespace std;

class Input;

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
	void Update(Input& input);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const;
	/// <summary>
	/// モデルハンドルの取得
	/// </summary>
	/// <returns></returns>
	int GetModelHandle()const { return m_modelHandle; }
	/// <summary>
	/// 位置を取得する
	/// </summary>
	/// <returns></returns>
	const VECTOR& GetPos()const;
	/// <summary>
	/// 半径を取得する
	/// </summary>
	/// <returns></returns>
	const float GetRad()const { return m_rad; }

private:	// 変数
	VECTOR m_pos;		// 位置
	VECTOR m_move;		// 移動量
	VECTOR m_velocity;	// 移動力
	VECTOR m_dir;		// 回転方向

	int m_modelHandle;	// 3Dモデル

	float m_rad;		// 半径

	float m_jumpPower;	// ジャンプ力

	bool m_isJump;		// ジャンプ中かどうか
	int m_jumpSe;		// ジャンプ中のSE

private:	// 定数
	static constexpr float kGravity = 0.025f;	// 重力
	static constexpr float kJumpHeight = 0.5f;	// ジャンプ力
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;	// Y軸方向の向き
};

