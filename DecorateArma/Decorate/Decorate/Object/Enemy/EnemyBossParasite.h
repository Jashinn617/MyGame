#pragma once
#include "EnemyBossBase.h"

/// <summary>
/// ボス1
/// 寄生モンスター
/// </summary>
class EnemyBossParasite : public EnemyBossBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期座標</param>
	EnemyBossParasite(VECTOR pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyBossParasite();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override final;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダポインタ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	/// <summary>
	/// 2D描画
	/// </summary>
	void Draw2D() override final;

	/// <summary>
	/// 敵の種類の取得
	/// </summary>
	/// <returns>種類</returns>
	virtual EnemyType GetEnemyType() const { return EnemyType::Boss; }
};