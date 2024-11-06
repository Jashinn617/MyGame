#pragma once
#include "DxLib.h"

/// <summary>
/// HPバーの基底クラス
/// </summary>
class HpBarBase
{
public:	// 関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~HpBarBase() {/*処理無し*/ };

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

protected:	// 変数
	const int* m_hp = 0;	// 体力
	int m_maxHp = 0;		// 最大体力
};

