#pragma once
#include "DxLib.h"

#include "../CharacterBase.h"

#include "../../Utility/CharacterData.h"

class PlayerState;
class Shot;
class Camera;
class Time;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public CharacterBase
{
public:		// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override final{/*処理無し*/ }

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override final;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダポインタ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	/// <summary>
	/// 2D画像描画
	/// </summary>
	void Draw2D() override final;

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="targetPos">攻撃を当てた相手の座標</param>
	/// <param name="damagePoint">ダメージ量</param>
	void OnDamage(VECTOR targetPos, int damagePoint) override final;

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void OnAttack() override final;

	/// <summary>
	/// ジャンプ状態の終了
	/// </summary>
	void EndJump() override final;

	/// <summary>
	/// ジャンプ力の設定
	/// </summary>
	/// <param name="jumpPower">ジャンプ力</param>
	void SetJumpPower(float jumpPower) { m_jumpPower = jumpPower; }

	/// <summary>
	/// 当たり判定の種類の取得
	/// </summary>
	/// <returns>当たり判定の種類</returns>
	ColType GetColType()const override final { return ColType::Player; }

	/// <summary>
	/// カメラ取得
	/// </summary>
	/// <returns>カメラポインタ</returns>
	const std::shared_ptr<Camera> GetCamera()const { return m_pCamera; }

	/// <summary>
	/// ショット取得
	/// </summary>
	/// <returns>ショットポインタ</returns>
	const std::shared_ptr<Shot> GetShot()const { return m_pShot; }

	/// <summary>
	/// ステイトごとの初期化
	/// </summary>
	void InitState();

private:	// 関数

	/// <summary>
	/// 角度更新
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// 移動方向更新
	/// </summary>
	void UpdateMoveDirection();

	/// <summary>
	/// カメラ更新
	/// </summary>
	void UpdateCamera();

	/// <summary>
	/// 移動処理
	/// </summary>
	/// <returns>移動値</returns>
	VECTOR Move();

	/// <summary>
	/// ステイトごとの更新
	/// </summary>
	void UpdateState();

	/// <summary>
	/// 攻撃更新
	/// </summary>
	void UpdateAttack();

private:	// 変数
	int m_attackCount;			// 連続で攻撃した回数

	bool m_isAttack;			// 攻撃中かどうか
	bool m_isNextAttack;		// 次の攻撃が実行されるかどうか
	bool m_isLockOn;			// ロックオン状態かどうか

	VECTOR m_moveDirection;

	std::shared_ptr<PlayerState> m_pState;		// ステイトポインタ
	std::shared_ptr<Camera> m_pCamera;			// カメラポインタ
	std::shared_ptr<Shot> m_pShot;				// ショット

	std::shared_ptr<Time> m_pAttackStanTime;	// 攻撃硬直時間
};