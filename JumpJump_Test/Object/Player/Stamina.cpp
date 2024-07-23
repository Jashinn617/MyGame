#include "Stamina.h"

namespace
{
	constexpr int kMaxStamina = 200;	// �X�^�~�i�̍ő��
	constexpr int kHealStamina = 2;		// �X�^�~�i���g���؂��Ă��Ȃ��ꍇ�̃X�^�~�i�̉񕜗�
	constexpr int kHealStaminaUseUp = 1;		// �X�^�~�i���g���؂����ꍇ�̃X�^�~�i�̉񕜗�
	constexpr int kUseStamina = 1;			// �X�^�~�i�̏����
	constexpr int kUseStaminaJump = 20;	// �W�����v���̃X�^�~�i�̏����
	constexpr double kMaxGauge = 15.0f;	// ���݂̃Q�[�W�ʂ��瑫���ő��
	constexpr double kChangeGaugeNum = 0.5f;	// �Q�[�W�̕ω���
	constexpr double kMaxPercent = 100.0f;	// �ő�p�[�Z���g
	constexpr float kStaminaGaugePosX = 80.0f;	// �X�^�~�i�Q�[�W�̍��WX
	constexpr float kStaminaGaugePosY = 120.0f;	// �X�^�~�i�Q�[�W�̍��WY
	
	/*�Q�[�W�̃n���h����*/
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