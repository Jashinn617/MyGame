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
};

