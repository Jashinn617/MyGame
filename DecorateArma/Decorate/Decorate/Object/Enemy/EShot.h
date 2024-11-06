#pragma once

#include "DxLib.h"

#include <memory>
#include <vector>

class Model;
class Time;
class CollisionShape;
class CharacterBase;

/// <summary>
/// 敵の弾
/// </summary>
class EShot
{
public:		// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="atkPoint">攻撃力</param>
	EShot(int atkPoint);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EShot();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="targetPos">ターゲット座標</param>
	/// <param name="isAttack">攻撃中かどうか</param>
	void Update(VECTOR targetPos, bool isAttack);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	/// <param name="pPlayer">プレイヤーポインタ</param>
	void OnAttack(CharacterBase* pPlayer);

private:	// 関数
	/// <summary>
	/// 弾生成
	/// </summary>
	/// <param name="targetPos">ターゲット座標</param>
	/// <param name="isAttack">攻撃中かどうか</param>
	void Make(VECTOR targetPos, bool isAttack);

private:	// 構造体
	/// <summary>
	/// 弾情報
	/// </summary>
	struct Bullet
	{
		bool isExist;								// 存在フラグ
		VECTOR pos;									// 座標
		VECTOR direction;							// 進む方向
		std::shared_ptr<Time> vanishTime;			// 消えるまでの時間
		std::shared_ptr<CollisionShape> coll;		// 当たり判定
		std::shared_ptr<Model> model;				// モデル
	};

private:	// 変数
	int m_atkPoint;									// 攻撃力
	VECTOR m_pos;									// 座標
	std::vector<Bullet> m_bullet;					// 弾構造体
	std::shared_ptr<Time> m_pBulletIntervalTime;	// 次の球が発射されるまでの時間
};