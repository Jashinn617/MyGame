#pragma once
#include "ObjectBase.h"

class CollisionShape;
class CharacterBase;

/// <summary>
/// 回復アイテム
/// </summary>
class RecoveryItem : public ObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	RecoveryItem(VECTOR pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~RecoveryItem();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override final;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override final;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダポインタ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	/// <summary>
	/// 自身の当たり判定情報の取得
	/// </summary>
	/// <returns></returns>
	virtual ColType GetColType() const override final { return ColType::Item; }

	/// <summary>
	/// ゲットされたとき
	/// </summary>
	/// <param name="pPlayer">プレイヤーポインタ</param>
	void OnGet(CharacterBase* pPlayer);

	/// <summary>
	/// プレイヤーに近付く
	/// </summary>
	/// <param name="pPlayer">プレイヤーポインタ</param>
	void OnApproach(CharacterBase* pPlayer);

private:

	std::shared_ptr<CollisionShape> m_pColl;			// 当たり判定ポインタ
	std::shared_ptr<CollisionShape> m_pApproachColl;	// プレイヤーに近付くようになる当たり判定
};

