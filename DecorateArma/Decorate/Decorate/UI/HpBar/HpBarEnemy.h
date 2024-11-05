#pragma once
#include "HpBarBase.h"
/// <summary>
/// 敵のHPバー
/// </summary>
class HpBarEnemy : public HpBarBase
{
public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="hp">HP</param>
	/// <param name="pos">敵座標</param>
	HpBarEnemy(const int& hp, const VECTOR& pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~HpBarEnemy();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:	// 変数
	int m_hpH;				// 通常時HPバー画像ハンドル
	int m_hpDecreaseH;		// 減少時HPバー画像ハンドル
	int m_hpEmptyH;			// 減少後HPバー画像ハンドル
	int m_graphSizeX;		// 画像Xサイズ
	int m_graphSizeY;		// 画像Yサイズ
	int m_decreaseHp;		// 体力減少
	float m_hpLenght;		// 体力分の画像の長さ
	const VECTOR* m_pos;	// 敵座標
};

