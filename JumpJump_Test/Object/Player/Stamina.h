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
	/// �X�^�~�i���g���؂������ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetStaminaUseUp()const { return m_isUseUp; }

	/// <summary>
	/// �X�^�~�i�̎c�ʂ̎擾
	/// </summary>
	/// <returns></returns>
	int GetStamina()const { return m_stamina; }

	/// <summary>
	/// �W�����v�������Ƃ�
	/// </summary>
	void JumpUpdate();

private:
	int m_stamina;	// �X�^�~�i��
	bool m_isUseUp;	// �X�^�~�i���g���؂������ǂ���
	double m_percent;	// �X�^�~�i�̎c��%
	double m_percentGauge;	// �X�^�~�i�Q�[�W�p�ϐ�
	//std::array<int, 3> m_staminaGugeH;
};

