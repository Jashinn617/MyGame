#pragma once
#include "DxLib.h"

#include "../CharacterBase.h"

#include "../../Utility/CharacterData.h"

class Camera;
class PlayerState;

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
	/// <param name="targetPos">相手の座標</param>
	void OnDamage(VECTOR targetPos) override final;

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
	/// 移動処理
	/// </summary>
	/// <returns>移動値</returns>
	VECTOR Move();

	/// <summary>
	/// ステイトごとの初期化
	/// </summary>
	void InitState();

	/// <summary>
	/// ステイトごとの更新
	/// </summary>
	void UpdateState();

private:	// 変数
	std::shared_ptr<PlayerState> m_pState;	// ステイトポインタ
	std::shared_ptr<Camera> m_pCamera;		// カメラポインタ
};