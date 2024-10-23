#pragma once
#include "../CharacterBase.h"

/// <summary>
/// 敵キャラクターの基底クラス
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

};

