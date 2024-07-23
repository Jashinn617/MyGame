#include "Stamina.h"

namespace
{
	constexpr int kMaxStamina = 200;	// スタミナの最大量
	constexpr int kHealStamina = 2;		// スタミナを使い切っていない場合のスタミナの回復量
	constexpr int kHealStaminaUseUp = 1;		// スタミナを使い切った場合のスタミナの回復量
	constexpr int kUseStamina = 1;			// スタミナの消費量
	constexpr int kUseStaminaJump = 20;	// ジャンプ時のスタミナの消費量
	constexpr double kMaxGauge = 15.0f;	// 現在のゲージ量から足す最大量
	constexpr double kChangeGaugeNum = 0.5f;	// ゲージの変化量
	constexpr double kMaxPercent = 100.0f;	// 最大パーセント
	constexpr float kStaminaGaugePosX = 80.0f;	// スタミナゲージの座標X
	constexpr float kStaminaGaugePosY = 120.0f;	// スタミナゲージの座標Y
	
	/*ゲージのハンドル名*/
	std::array<const char*, 3>kFineName =
	{
		"",
		"",
		"",
	};
}

Stamina::Stamina():
	m_stamina(kMaxStamina),
	m_isUseUp(false),
	m_percent(kMaxPercent),
	m_percentGauge(0.0f)
{
}

Stamina::~Stamina()
{
}

void Stamina::Update(bool useStamina)
{
}

void Stamina::Draw(VECTOR pos)
{
}