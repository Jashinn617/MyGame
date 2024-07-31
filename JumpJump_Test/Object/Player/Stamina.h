#pragma once
#include "DxLib.h"
#include <array>

class Stamina
{
public:
	Stamina();
	virtual ~Stamina();

	void Update(bool useStamina);

	void Draw(VECTOR pos);

	/// <summary>
	/// スタミナを使い切ったかどうか
	/// </summary>
	/// <returns></returns>
	bool GetStaminaUseUp()const { return m_isUseUp; }

	/// <summary>
	/// スタミナの残量の取得
	/// </summary>
	/// <returns></returns>
	int GetStamina()const { return m_stamina; }

	/// <summary>
	/// ジャンプをしたとき
	/// </summary>
	void JumpUpdate();

private:
	int m_stamina;	// スタミナ量
	bool m_isUseUp;	// スタミナを使い切ったかどうか
	double m_percent;	// スタミナの残り%
	double m_percentGauge;	// スタミナゲージ用変数
	//std::array<int, 3> m_staminaGugeH;
};

