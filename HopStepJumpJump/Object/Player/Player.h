#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

#include <array>
#include <memory>
#include <vector>

class Camera;
class Time;
class PlayerState;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public CharacterBase
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
	/// 初期化
	/// </summary>
	void Init() override final {/*処理無し*/ };

	/// <summary>
	/// 更新」
	/// </summary>
	void Update() override final;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	/// <summary>
	/// 2D画像描画
	/// </summary>
	void Draw2D() override final;

	/// <summary>
	/// ステージクリア時の処理
	/// </summary>
	void StageClear() override final;

	/// <summary>
	/// ステージ終了時の処理
	/// </summary>
	void StageEnd() override final;

	/// <summary>
	/// 攻撃を受けた
	/// </summary>
	/// <param name="targetPos">攻撃してきた敵の位置</param>
	void OnDamage(VECTOR targetPos) override final;

	/// <summary>
	/// 攻撃をした
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
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const VECTOR& GetPos()const { return m_info.pos; }

	/// <summary>
	/// 当たり判定の種類の取得
	/// </summary>
	/// <returns>当たり判定の種類</returns>
	ColType GetColType()const { return ColType::Player; }

	/// <summary>
	/// カメラの取得
	/// </summary>
	/// <returns>カメラポインタ</returns>
	const std::shared_ptr<Camera> GetCamera() const { return m_pCamera; }

private:	// 関数
	/// <summary>
	/// 角度の更新
	/// </summary>
	void AngleUpdate();

	/// <summary>
	/// 移動方向の更新
	/// </summary>
	void MoveDirectionUpdate();

	/// <summary>
	/// 移動
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate();

private:	// メンバ関数

	/*各状態の初期化*/
	void IdleInit() {/*処理無し*/ };
	void WalkInit() {/*処理無し*/ };
	void DashInit() {/*処理無し*/ };
	void JumpInit();
	void KnockBackInit() {/*処理無し*/ };
	void StageClearInit() {/*処理無し*/ };

	/*各状態の更新*/
	void IdleUpdate();
	void WalkUpdate();
	void DashUpdate();
	void JumpUpdate();
	void KnockBackUpdate();
	void StageClearUpdate();

private:	// 変数
	float m_walkSpeed;							// 移動速度
	float m_dashSpeed;							// ダッシュ時の速度
	float m_acc;								// 加速度
	bool m_isStageClear;						// ステージをクリアしたかどうか
	VECTOR m_moveDirectVec;						// 移動方向ベクトル
	VECTOR m_cameraToPlayerVec;					// プレイヤーからカメラまでの距離
	std::shared_ptr<PlayerState> m_pState;		// 状態のポインタ
	std::shared_ptr<Camera> m_pCamera;			// カメラポインタの取得
	std::shared_ptr<Time> m_pInvincibleTime;	// 攻撃を食らった後の無敵時間
};

