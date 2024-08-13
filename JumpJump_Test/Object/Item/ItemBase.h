#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

class Player;
class ObjectBase;
class Model;
class Circle;
class Time;
class Input;

class ItemBase : public CharacterBase
{
public:
	ItemBase();
	ItemBase(VECTOR pos);
	virtual ~ItemBase();

	virtual void Init();
	virtual void Update(Input& input) override;

	virtual void Draw();
	virtual void Draw2D() override;

	// 存在するかどうか
	bool GetExist()const { return m_info.isExist; }

	// ゲットされたとき
	void OnGet();

	// 自身の当たり判定の情報
	virtual ColType GetColType()const { return ColType::Item; }

	// ステージクリア処理
	void StageClear() override final;

protected:
	// 移動速度の初期化
	void InitMoveSpeed(float moveSpeed);

	// 角度の更新
	virtual void AngleUpdate();
	// 移動方向の更新
	virtual void MoveDirectionUpdate();
	// 移動方向と角度を考慮した移動の更新
	VECTOR MoveUpdate();

	/*メンバ関数ポインタ*/
	// 状態更新
	virtual void StateTransitionUpdate();

	// 移動状態への変更
	virtual bool StateTransitionMove();
	// 志望状態に変更
	virtual bool StateTransitionDead();
	// 待機状態
	virtual void IdleStateUpdate();
	// 移動状態
	virtual void MoveStateUpdate();
	// 死亡状態
	virtual void DeadStateUpdate();


protected:	// 変数
	VECTOR m_moveDirectionVec;	// 移動方向ベクトル
	int m_createTime;		// 生成されてから立った時間
	void(ItemBase::* m_updateFunc)();	// メンバ関数ポインタ
	std::shared_ptr<Time> m_deadTime;	// 死んでからの時間
	float m_colHeight;	// 当たり判定の高さを中心にする変数



};