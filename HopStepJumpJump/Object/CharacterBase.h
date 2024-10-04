#pragma once
#include "ObjectBase.h"

class Circle;

class CharacterBase : public ObjectBase
{
public:

	/// <summary>
	/// ステータス情報
	/// </summary>
	struct StatusData
	{
		float spd = 5.0f;	// スピード
	};

	/// <summary>
	/// 移動用ステータス情報
	/// </summary>
	struct MoveStatusData
	{
		float walkSpeed = 0;	// 歩きスピード
		float runSpeed = 0;		// 走りスピード
		float acceleration = 0;	// 加速度
		float rotSpeed = 0;		// 回転スピード
	};

	/// <summary>
	/// アニメーション情報
	/// </summary>
	struct AnimData
	{
		int8_t idle = 0;		// 待機
		int8_t walk = 0;		// 歩き
		int8_t jumpStart = 0;	// ジャンプ時
		int8_t jumpIdle = 0;	// ジャンプ中
		int8_t run = 0;			// 走り
		int8_t knockBack = 0;	// ノックバック
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
	virtual void Init() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) = 0;

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="targetPos">攻撃を当てた相手の座標</param>
	virtual void OnDamage(VECTOR targetPos) {};

	/// <summary>
	/// キャラクター同士の当たり判定を考慮した移動更新
	/// </summary>
	/// <param name="pTarget">ターゲットポインタ/param>
	void MoveCollCharacterUpdate(CharacterBase* pTarget);

	/// <summary>
	/// プレイヤーの攻撃が敵に当たった
	/// </summary>
	/// <param name="pEnemy">敵ポインタ</param>
	void AttackPlayerCollEnemy(CharacterBase* pEnemy);

	/// <summary>
	/// 敵の攻撃がプレイヤーに当たった
	/// </summary>
	/// <param name="pPlayer">プレイヤーポインタ</param>
	void AttackEnemyCollPlayer(CharacterBase* pPlayer);

	/// <summary>
	/// プレイヤーがアイテムに当たった
	/// </summary>
	/// <param name="pItem">アイテムポインタ</param>
	void PlayerToItem(CharacterBase* pItem);

	/// <summary>
	/// ジャンプ状態の終了処理
	/// </summary>
	virtual void EndJump();

	/// <summary>
	/// 地面に当たっているときの処理
	/// </summary>
	void HitGroundUpdate();

	/// <summary>
	/// 重力による落下処理
	/// </summary>
	void GravityUpdate();

	/// <summary>
	/// 円の当たり判定ポインタの取得
	/// </summary>
	/// <returns>当たり判定ポインタ</returns>
	const std::shared_ptr<Circle> GetCircle()const { return m_pCircle; }

	/// <summary>
	/// 角度の取得
	/// </summary>
	/// <returns>角度</returns>
	float GetAngle() const { return m_angle; }

	/// <summary>
	/// ダメージを受けたかどうか
	/// </summary>
	/// <returns>ダメージを受けたか</returns>
	bool IsDamage()const { return m_isDamage; }

	/// <summary>
	/// 攻撃を受けてない状態に戻す
	/// </summary>
	void OffDamageFlag() { m_isDamage = false; }

	/// <summary>
	/// ジャンプ状態かどうか
	/// </summary>
	/// <returns>ジャンプ状態か</returns>
	bool IsJump()const { return m_isJump; }

	/// <summary>
	/// ジャンプ力を返す
	/// </summary>
	/// <returns>ジャンプ力</returns>
	float GetJumpPower()const { return m_jumpPower; }

	/// <summary>
	/// 死んだかどうか
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool IsDead()const { return m_isDead; }

protected:	// 関数

	/// <summary>
	/// 角度を滑らかに変化させる関数
	/// </summary>
	/// <param name="nowAngle">現在の角度</param>
	/// <param name="nextAngle">目標角度</param>
	void SmoothAngle(float& nowAngle, float nextAngle);

protected:	// 変数
	float m_jumpPower;					// ジャンプ力
	bool m_isJump;						// ジャンプ中かどうか
	bool m_isDead;						// 死んだかどうか
	std::shared_ptr<Circle> m_pCircle;	// 当たり判定の円のポインタ

	StatusData m_statusData{};			// ステータス情報
	MoveStatusData m_moveData{};			// 移動情報
	AnimData m_animData{};				// アニメーション情報
};

