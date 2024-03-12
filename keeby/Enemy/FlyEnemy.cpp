#include "FlyEnemy.h"
#include "../Player.h"
#include "../Attack/Vomit.h"
#include "../Attack/AirBullet.h"
#include "../Attack/Inhale.h"
#include "../Camera.h"
#include "../Game.h"
#include "DxLib.h"

namespace
{
	// �z�����܂�鑬�x
	constexpr float kInhaleSpeed = 3.5f;

	// �A�j���[�V�����X�s�[�h
	constexpr float kSinSpeed = 0.15f;
	// �A�j���[�V�����̐U��
	constexpr float kAnimationSize = 70.0f;
}

FlyEnemy::FlyEnemy():
	m_w(0),
	m_h(0),
	m_handle(-1),
	m_onInhaleHandle(-1),
	m_dir(kDirLeft),
	m_isExist(false),
	m_isInhale(false),
	m_walkAnimFrame(0),
	m_walkFrame(0),
	m_speed(2),
	m_x(0),
	m_y(0),
	m_sinCount(0),
	m_animationHeight(0),
	m_walkCycle(0),
	m_isDamage(false),
	m_damageFrame(0)
{
	// �ʒu�̏�����
	m_pos = Vec2(0, 0);
	/*�O���t�B�b�N�̃��[�h*/
	m_handle = LoadGraph(_T("data/Enemy/FlyEnemy.png"));
	m_onInhaleHandle = LoadGraph(_T("data/Enemy/DamageFlyEnemy.png"));
	m_damageEffectHandle = LoadGraph(_T("data/Effect/Delete.png"));
	/*SE�̃��[�h*/
	m_hitSeHandle = LoadSoundMem(_T("data/Sound/SE/Hit.wav"));
}

FlyEnemy::~FlyEnemy()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_handle);
	DeleteGraph(m_onInhaleHandle);
	DeleteGraph(m_damageEffectHandle);
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_hitSeHandle);
}

void FlyEnemy::Init(float x, float y, int cycle)
{
	// �����ʒu�̐ݒ�
	m_pos.x = x;
	m_pos.y = y + 7;

	// �܂�Ԃ��t���[���̐ݒ�
	m_walkCycle = cycle;
	m_walkFrame = 0;
	if (m_dir == kDirRight)
	{
		m_speed *= -1;
		m_dir = kDirLeft;
	}

	// �T�C�Y�ݒ�
	m_w = 64;
	m_h = 64;
	
	// ���X�^�[�g�p�̏�����
	m_damageFrame = 0;
	m_isDamage = false;
	m_isExist = true;
}

void FlyEnemy::Update()
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
	m_sinCount += kSinSpeed;
	m_animationHeight = sinf(m_sinCount) * kAnimationSize;

	

	// �ʏ�̏���
	if (!m_isInhale)// �������܂�Ă��Ȃ���
	{
		if (!m_isDamage)// �_���[�W���󂯂Ă��Ȃ�
		{
			// �ړ�
			m_pos.x += m_speed;
			m_walkFrame++;

			// �܂�Ԃ����ɔ��΂ɂ���
			if (m_walkFrame >= m_walkCycle)
			{
				m_speed *= -1;
				m_walkFrame = 0;
				if (m_dir == kDirLeft)
				{
					m_dir = kDirRight;
				}
				else if (m_dir == kDirRight)
				{
					m_dir = kDirLeft;
				}
			}
		}
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

void FlyEnemy::Draw()
{
	// ���݂��Ȃ��G�l�~�[�͕`�悵�Ȃ�
	if (!m_isExist)return;

	// ����������������W�ɕϊ�����
	int x = static_cast<int>(m_pos.x - m_w * 0.5f);
	int y = static_cast<int>(m_pos.y - m_h);
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// �A�j���[�V����
	int posY = y + static_cast<int>(m_animationHeight);

	// �����G�t�F�N�g
	if (m_isDamage)
	{
		DrawGraph(x, posY, m_damageEffectHandle, true);
	}
	else if (!m_isDamage)
	{
		if (m_isInhale)// �������܂ꒆ
		{
			if (m_dir == kDirLeft)
			{
				DrawGraph(x, posY, m_onInhaleHandle, true);
			}
			else if (m_dir == kDirRight)
			{
				DrawTurnGraph(x, posY, m_onInhaleHandle, true);
			}
		}
		else if (!m_isInhale)// �ʏ�
		{
			if (m_dir == kDirLeft)
			{
				DrawTurnGraph(x, posY, m_handle, true);		
			}
			else if (m_dir == kDirRight)
			{
				DrawGraph(x, posY, m_handle, true);
			}
		}
	}

#ifdef _DEBUG
	// �����蔻��̋�`
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect FlyEnemy::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float FlyEnemy::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �A�j���[�V�����ɒǏ]������
	float posY = y + m_animationHeight;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	posY -= m_pCamera->GetScrollY();

	return x;
}

float FlyEnemy::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �A�j���[�V�����ɒǏ]������
	float posY = y + m_animationHeight;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	posY -= m_pCamera->GetScrollY();

	return x + m_w;
}

float FlyEnemy::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �A�j���[�V�����ɒǏ]������
	float posY = y + m_animationHeight;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	posY -= m_pCamera->GetScrollY();

	return posY + 10;
}

float FlyEnemy::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �A�j���[�V�����ɒǏ]������
	float posY = y + m_animationHeight;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	posY -= m_pCamera->GetScrollY();

	return posY + static_cast<float>(m_h);
}

void FlyEnemy::PlayerCollision()
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

void FlyEnemy::InhaleCollision()
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

void FlyEnemy::VomitCollision()
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

void FlyEnemy::AirBulletCollision()
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
