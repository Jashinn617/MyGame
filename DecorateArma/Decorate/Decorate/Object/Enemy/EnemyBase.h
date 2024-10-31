#pragma once
#include "../CharacterBase.h"

/// <summary>
/// 敵キャラクター基底クラス
/// </summary>
class EnemyBase : public CharacterBase
{
public:	// 列挙型
	/// <summary>
	/// 攻撃タイプ
	/// </summary>
	enum class AttackType
	{
		Melee,		// 近距離
		Shot,		// 遠距離
		Mulch,		// 両方
	};

	/// <summary>
	/// 敵タイプ
	/// </summary>
	enum class EnemyType
	{
		Normal,		// 雑魚敵
		Boss,		// ボス敵
	};

public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBase();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	EnemyBase(VECTOR pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダポインタ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override;

	/// <summary>
	/// 2D描画
	/// </summary>
	virtual void Draw2D()override;

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="targetPos">攻撃を当てた相手の座標</param>
	/// <param name="damagePoint">ダメージ量</param>
	void OnDamage(VECTOR targetPos, int damagePoint) override final;

	/// <summary>
	/// 死亡処理
	/// </summary>
	void OnDead();

	/// <summary>
/// 索敵範囲に入っているかどうかを調べる
/// </summary>
/// <param name="pPlayer">プレイヤーポインタ</param>
	void IsSearchRange(CharacterBase* pPlayer);

	/// <summary>
	/// 存在するかどうか
	/// </summary>
	/// <returns>存在フラグ</returns>
	bool IsExist()const { return m_characterInfo.isExist; }

	/// <summary>
	/// 敵からプレイヤーまでのベクトルの取得
	/// </summary>
	/// <returns>プレイヤーまでのベクトル</returns>
	VECTOR GetEnemyToPlayerVec()const { return m_enemyToPlayer; }

	/// <summary>
	/// 自身の当たり判定情報の取得
	/// </summary>
	/// <returns>当たり判定情報</returns>
	virtual ColType GetColType()const { return ColType::Enemy; }

	/// <summary>
	/// 敵の種類の取得
	/// </summary>
	/// <returns>敵の種類</returns>
	virtual EnemyType GetEnemyType()const { return EnemyType::Normal; }

protected:	// 関数
	/// <summary>
	/// 角度更新
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// 移動方向更新
	/// </summary>
	virtual void UpdateMoveDirection();

	/// <summary>
	/// 移動更新
	/// </summary>
	/// <returns>移動値</returns>
	virtual VECTOR UpdateMove();

protected:	// 状態遷移関数
	/// <summary>
	/// ステイト更新
	/// </summary>
	virtual void UpdateStateTransition();

	/// <summary>
	/// 死亡状態に変更する条件があっているかどうか返す
	/// </summary>
	/// <returns>条件があっているかどうか</returns>
	virtual bool StateTransitionDead();

protected:	// メンバ関数
	/// <summary>
	/// 待機更新
	/// </summary>
	virtual void UpdateIdleState();
	/// <summary>
	/// 移動更新
	/// </summary>
	virtual void UpdateMoveState();
	/// <summary>
	/// 死亡更新
	/// </summary>
	virtual void UpdateDeadState();

protected:	// 変数
	bool m_isFinding;								// プレイヤー発見状態かどうか
	VECTOR m_moveDirection;							// 移動方向ベクトル
	VECTOR m_enemyToPlayer;							// 敵からプレイヤーまでのベクトル
	AttackType m_attackType;						// 攻撃タイプ
	std::shared_ptr<CollisionShape> m_pSearchRange;	// 索敵範囲
	void(EnemyBase::* m_updateFunc)();				// メンバ関数ポインタ
};