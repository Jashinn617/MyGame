#pragma once
#include "HpBarBase.h"
/// <summary>
/// プレイヤーのHPバー
/// </summary>
class HpBarPlayer : public HpBarBase
{
public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="hp">体力</param>
	HpBarPlayer(const int& hp);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HpBarPlayer();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 体力回復時の処理
	/// </summary>
	void OnCureHp();
};

