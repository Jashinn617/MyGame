#pragma once
#include "ObjectBase.h"

class Circle;

/// <summary>
/// オブジェクトの中でもキャラクターの基底クラス
/// </summary>
class CharacterBase : public ObjectBase
{
public:	// 構造体

	/// <summary>
	/// ステータス情報
	/// </summary>
	struct StatusData
	{
		float spd = 0.0f;	// 速度
	};

	/// <summary>
	/// 移動用ステータス情報
	/// </summary>
	struct MoveStatusData
	{
		float walkSpeed = 0.0f;		// 歩き速度
		float runSpeed = 0.0f;		// 走り速度
		float acceleration = 0.0f;	// 加速度
		float rotSpeed = 0.0f;		// 回転速度
	};

	/// <summary>
	/// アニメーション情報
	/// </summary>
	struct AnimData
	{
		int8_t idle = 0;		// 待機
		int8_t walk = 0;		// 歩き
		int8_t run = 0;			// 走り
		int8_t jumpStart = 0;	// ジャンプ始め
		int8_t jumpIdle = 0;	// ジャンプ中
		int8_t Damage = 0;		// ダメージ
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CharacterBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override = 0;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダポインタ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader)override = 0;



protected:	// 関数
	/// <summary>
	/// 角度を滑らかに変化させる関数
	/// </summary>
	/// <param name="nowAngle">現在の角度</param>
	/// <param name="nextAngle">目標角度</param>
	void SmoothAngle(float& nowAngle, float nextAngle);

protected:	// 変数
	bool m_isDead;						// 死んだかどうか
	std::shared_ptr<Circle> m_pCircle;	// 当たり判定用の円のポインタ

	StatusData m_statusData{};			// ステータス情報
	MoveStatusData m_moveData{};		// 移動情報
	AnimData m_animData{};				// アニメーション情報
};