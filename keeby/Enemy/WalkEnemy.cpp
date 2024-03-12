#include "WalkEnemy.h"
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
	// �L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2, 1};
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 12;
	// �A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

WalkEnemy::WalkEnemy() :
	m_w(0),
	m_h(0),
	m_handle(-1),
	m_damageHandle(-1),
	m_dir(kDirLeft),
	m_isExist(false),
	m_isInhale(false),
	m_walkAnimFrame(0),
	m_walkFrame(0),
	m_speed(2),
	m_x(0),
	m_y(0),
	m_walkCycle(0),
	m_isDamage(false),
	m_damageFrame(0)
{
	// �ʒu�̏�����
	m_pos = Vec2(0, 0);
	/*�O���t�B�b�N�̃��[�h*/
	m_handle = LoadGraph(_T("data/Enemy/WalkEnemy.png"));
	m_damageHandle = LoadGraph(_T("data/Enemy/DamageEnemy.png"));
	m_damageEffectHandle = LoadGraph(_T("data/Effect/Delete.png"));
	/*SE�̃��[�h*/
	m_hitSeHandle = LoadSoundMem(_T("data/Sound/SE/Hit.wav"));
}

WalkEnemy::~WalkEnemy()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_handle);
	DeleteGraph(m_damageHandle);
	DeleteGraph(m_damageEffectHandle);
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_hitSeHandle);
}

void WalkEnemy::Init(float x, float y, int cycle)
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
	m_w = 68;
	m_h = 72;

	// ���X�^�[�g�p�̏�����
	m_damageFrame = 0;
	m_isDamage = false;
	m_isExist = true;
}

void WalkEnemy::Update()
{
	// ���݂��Ȃ��G�l�~�[�̏����͂��Ȃ�
	if (!m_isExist)return;

	// �����蔻��̍X�V
	GetRect();
	PlayerCollision();
	InhaleCollision();
	VomitCollision();
	AirBulletCollision();


	if (!m_isInhale)// �������܂�Ă��Ȃ��Ƃ�
	{
		// �����̃A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}

		if (!m_isDamage)// �_���[�W���󂯂Ă��Ȃ�
		{
			// �ړ�
			m_pos.x += m_speed;
			m_walkFrame++;
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
	if (m_isDamage)
	{
		m_damageFrame++;

		if (m_damageFrame >= 30)
		{
			m_isExist = false;
		}

	}


}

void WalkEnemy::Draw()
{
	// ���݂��Ȃ��G�l�~�[�͕`�悵�Ȃ�
	if (!m_isExist)return;

	// ����������������W�ɕϊ�����
	int x = static_cast<int>(m_pos.x - m_w * 0.5f);
	int y = static_cast<int>(m_pos.y - m_h);

	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// �A�j���[�V����
	int animFrame = m_walkAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * m_w;
	int srcY = m_h * m_dir;	

	
	if (m_isDamage)// �_���[�W���󂯂���
	{
		DrawGraph(x, y, m_damageEffectHandle, true);
	}
	else if (!m_isDamage)
	{
		if (m_isInhale)// �z�����܂�Ă���Ƃ�
		{
			if (m_dir == kDirLeft)
			{
				DrawGraph(x, y, m_damageHandle, true);
			}
			else if (m_dir == kDirRight)
			{
				DrawTurnGraph(x, y, m_damageHandle, true);
			}
		}
		else if (!m_isInhale)// �ʏ펞
		{
			DrawRectGraph(x, y, srcX, srcY, m_w, m_h, m_handle, true);
		}
	}

#ifdef _DEBUG
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect WalkEnemy::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float WalkEnemy::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();

	return x;
}

float WalkEnemy::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();

	return x + m_w;
}

float WalkEnemy::GetTop() const
{
	// ����������������W�ɕϊ�����
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	y -= m_pCamera->GetScrollY();

	return y;
}

float WalkEnemy::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void WalkEnemy::PlayerCollision()
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

void WalkEnemy::InhaleCollision()
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

void WalkEnemy::VomitCollision()
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

void WalkEnemy::AirBulletCollision()
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
