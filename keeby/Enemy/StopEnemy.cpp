#include "StopEnemy.h"
#include "../Player.h"
#include "../Attack/Vomit.h"
#include "../Attack/AirBullet.h"
#include "../Attack/Inhale.h"
#include "../Camera.h"
#include "../Game.h"
#include "DxLib.h"

#include <cmath>

namespace
{
	// �������܂�鑬�x
	constexpr float kInhaleSpeed = 3.5f;

	// �A�j���[�V�����X�s�[�h
	constexpr float kSinSpeed = 0.25f;
	// �A�j���[�V�����̐U��
	constexpr float kAnimationSize = 6.0f;
}


StopEnemy::StopEnemy() :
	m_w(0),
	m_h(0),
	m_isExist(false),
	m_isInhale(false),
	m_x(0),
	m_y(0),
	m_sinCount(0),
	m_animationHeight(0),
	m_isDamage(false),
	m_damageFrame(0)
{
	// �ʒu�̏�����
	m_pos = Vec2(0, 0);
	/*�O���t�B�b�N�̃��[�h*/
	m_handle = LoadGraph(_T("data/Enemy/StopEnemy.png"));
	m_damageEffectHandle = LoadGraph(_T("data/Effect/Delete.png"));
	/*SE�̃��[�h*/
	m_hitSeHandle = LoadSoundMem(_T("data/Sound/SE/Hit.wav"));
	
}

StopEnemy::~StopEnemy()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_handle);
	DeleteGraph(m_damageEffectHandle);
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_hitSeHandle);
}

void StopEnemy::Init(float x, float y)
{
	// �����ʒu�̐ݒ�
	m_pos.x = x;
	m_pos.y = y;

	// �T�C�Y�̐ݒ�
	GetGraphSize(m_handle, &m_w, &m_h);

	// ���X�^�[�g�p�̏�����
	m_damageFrame = 0;
	m_isDamage = false;
	m_isExist = true;
}

void StopEnemy::Update()
{
	// ���݂��Ȃ��G�l�~�[�̏����͂��Ȃ�
	if (!m_isExist)return;
	
	// �����蔻��̍X�V
	GetRect();
	PlayerCollision();
	InhaleCollision();
	VomitCollision();
	AirBulletCollision();

	// �A�j���[�V����
	if (!m_isInhale)
	{
		m_sinCount += kSinSpeed;
		m_animationHeight = sinf(m_sinCount) * kAnimationSize;
	}
	
	// ������Ƃ��̏���
	// �����G�t�F�N�g��\�����ď�����
	if (m_isDamage)
	{
		m_damageFrame++;

		if (m_damageFrame >= 30)
		{
			m_isExist = false;
		}
	}
}

void StopEnemy::Draw()
{
	// ���݂��Ȃ��G�l�~�[�͕`�悵�Ȃ�
	if (!m_isExist)return;

	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// �A�j���[�V����
	float posY = y + m_animationHeight;

	
	if (m_isDamage)// �����G�t�F�N�g
	{
		DrawGraph(static_cast<int>(x), static_cast<int>(posY), m_damageEffectHandle, true);
	}
	else if (!m_isDamage)// �ʏ�
	{
		DrawExtendGraph(static_cast<int>(x), static_cast<int>(posY), static_cast<int>(x) + m_w, static_cast<int>(y) + m_h, m_handle, true);
	}

#ifdef _DEBUG
	// �����蔻��̋�`
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect StopEnemy::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float StopEnemy::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float StopEnemy::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float StopEnemy::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float StopEnemy::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void StopEnemy::PlayerCollision()
{
	if (m_pPlayer->IsMiss())return;
	if (m_isDamage)return;
	// �v���C���[�ɓ��������ꍇ�́A�v���C���[�Ƀ_���[�W��^���������Ŏ�����������
	// �v���C���[�ɋz�����܂�Ă����Ԃ������ꍇ�̓v���C���[���ق��΂��Ԃɂ���
	if (m_colRect.isCol(m_pPlayer->GetColRect()))
	{
		if (m_isInhale)
		{
			m_pPlayer->OnGlup();
			m_isExist = false;
		}
		else
		{
			m_pPlayer->OnDamage();		
		}

		if (!m_pPlayer->IsDamege())
		{
			m_isDamage = true;
		}
	}

}

void StopEnemy::InhaleCollision()
{
	if (m_isDamage)return;
	if (m_colRect.isCol(m_pInhale->GetRect()) && m_pInhale->IsExsist())
	{
		// �G�̋z�����݂̏���
		Vec2 E = m_pos;
		Vec2 P = Vec2(m_pPlayer->GetX(), m_pPlayer->GetY());
		Vec2 EP = P.operator-=(E);
		Vec2 Direction = EP.GetNormalize();
		Vec2 Velocity = Direction.operator*=(kInhaleSpeed);

		E.operator+=(Velocity);

		m_pos = E;
		m_isInhale = true;
	}
	else
	{
		m_isInhale = false;
	}
}

void StopEnemy::VomitCollision()
{
	if (!m_pVomit->IsExsist())return;
	if (m_isDamage)return;
	if (m_colRect.isCol(m_pVomit->GetRect()))
	{
		// SE��炷
		PlaySoundMem(m_hitSeHandle, DX_PLAYTYPE_BACK, true);
		// ������
		m_isDamage = true;
		// �e������
		m_pVomit->FalseExist();
	}
}

void StopEnemy::AirBulletCollision()
{
	if (!m_pAirBullet->IsExsist())return;
	if (m_isDamage)return;
	if (m_colRect.isCol(m_pAirBullet->GetRect()))
	{
		// SE��炷
		PlaySoundMem(m_hitSeHandle, DX_PLAYTYPE_BACK, true);
		// ������
		m_isDamage = true;
		// �e������
		m_pAirBullet->FalseExist();
	}
}
