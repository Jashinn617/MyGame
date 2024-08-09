#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

#include <memory>

class Input;

class Player;
class ObjectBase;
class Model;
class Circle;
class Time;

class EnemyBase :public CharacterBase
{
public:
	// 敵のタイプ
	enum class EnemyType
	{
		Bee,
		Crab,
		Ogre,
		Skull
	};

public:
	EnemyBase();
	EnemyBase(VECTOR pos);
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update(Input& input) override;

	virtual void Draw();
	virtual void Draw2D()override;

	/// <summary>
	/// ステージクリア処理
	/// </summary>
	void StageClear() override final;

	void OnDamage(VECTOR targetPos) override;

	/// <summary>
	/// ジャンプの終了処理
	/// </summary>
	virtual void EndJump();

	/// <summary>
	/// 存在するかどうか
	/// </summary>
	/// <returns></returns>
	bool IsExist()const { return m_info.isExist; }

	/// <summary>
	/// 敵からプレイヤーまでのベクトルの取得
	/// </summary>
	/// <returns></returns>
	VECTOR GetEnemyToPlayerVec()const { return m_enemyToPlayerVec; }

	/// <summary>
	/// 自身の当たり判定の情報
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType()const { return ColType::Enemy; }

	/// <summary>
	/// /エネミーの種類
	/// </summary>
	/// <returns></returns>
	virtual EnemyType GetEnemyType()const { return EnemyType::Bee; }	

protected:	// 関数
	/// <summary>
	/// 移動速度の初期化
	/// </summary>
	/// <param name="moveSpeed"></param>
	void InitMoveSpeed(float moveSpeed);

	/// <summary>
	/// 角度の更新
	/// </summary>
	virtual void AngleUpdate();

	/// <summary>
	/// 移動方向の更新
	/// </summary>
	virtual void MoveDirectionUpdate();

	/// <summary>
	/// 移動処理
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate();

	virtual void StateTransitionUpdate();		// 状態更新

	virtual bool TransitionMove();		// 移動状態に遷移するかどうか
	virtual bool TransitionKnockBack();	// ノックバック状態に遷移するかどうか
	virtual bool TransitionDead();		// 死亡状態に遷移するかどうか

	virtual void IdleStateUpdate();		// 待機状態の更新
	virtual void MoveStateUpdate();		// 移動状態の更新
	virtual void KnockBackStateUpdate();	// ノックバック状態の更新
	virtual void DeadStateUpdate();		// 死亡状態の更新


protected:	// 変数
	int m_createTime;		// 生成されてから立った時間
	float m_colHeight;	// 当たり判定の高さをモデルの中心にする
	VECTOR m_enemyToPlayerVec;	// 敵からプレイヤーまでのベクトル
	VECTOR m_moveDirectionVec;	// 移動方向ベクトル
	void (EnemyBase::* m_updateFunc)();	// メンバ関数ポインタ
	std::shared_ptr<Time> m_deadTime;	// 死んでからの時間
};
