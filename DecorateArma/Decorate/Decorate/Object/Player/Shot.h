﻿#pragma once

#include "DxLib.h"

#include <memory>
#include <vector>

class Model;
class Time;
class CollisionShape;
class CharacterBase;
class Player;

/// <summary>
/// プレイヤーに追従する遠距離攻撃武器
/// </summary>
class Shot
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Shot(Player* pPlayer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Shot();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="playerPos">プレイヤー座標</param>
	/// <param name="playerRot">プレイヤー向き</param>
	void Update(const VECTOR& playerPos, float playerRot);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	/// <param name="pEnemy">敵ポインタ</param>
	void OnAttack(CharacterBase* pEnemy);

	/// <summary>
	/// カメラ角度行列の取得
	/// </summary>
	/// <param name="rotMtx">カメラ角度行列</param>
	void SetCameraRot(MATRIX rotMtx) { m_cameraRotMtx = rotMtx; }

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

private:	// 関数
	/// <summary>
	/// 弾更新
	/// </summary>
	void UpdateBullet();

	/// <summary>
	/// 弾生成
	/// </summary>
	void MakeBullet();

private:
	float m_sinCount;								// 上下移動カウント
	float m_sinPosY;								// サイン計算に使うY座標
	VECTOR m_pos;									// 座標
	MATRIX m_cameraRotMtx;							// カメラの角度行列
	std::vector<Bullet> m_bullet;					// 弾構造体
	Player* m_pPlayer;								// プレイヤーポインタ
	std::shared_ptr<Model> m_pModel;				// 武器本体モデルポインタ
	std::shared_ptr<Time> m_pBulletIntervalTime;	// 次の球が発射されるまでの時間
};

