#pragma once
#include "EnemyBase.h"


/// <summary>
/// ボス敵の基底クラス
/// </summary>
class EnemyBossBase : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBossBase() {/*処理無し*/ };

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyBossBase() {/*処理無し*/ };

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override {/*処理無し*/ };

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override {/*処理無し*/ };

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダポインタ</param>
	void Draw(std::shared_ptr<ToonShader> pToonShader) override {/*処理無し*/ };

	/// <summary>
	/// 2D描画
	/// </summary>
	void Draw2D() override {/*処理無し*/ };

	/// <summary>
	/// 敵の種類の取得(ボス)
	/// </summary>
	/// <returns>種類</returns>
	virtual EnemyType GetEnemyType() const { return EnemyType::Boss; }
};