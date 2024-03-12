#include "RecoveryItem.h"
#include "../Player.h"
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


RecoveryItem::RecoveryItem():
	m_w(0),
	m_h(0),
	m_isExist(false),
	m_isInhale(false),
	m_x(0),
	m_y(0),
	m_sinCount(0),
	m_animationHeight(0)
{
	// �ʒu�̏�����
	m_pos = Vec2(0, 0);
	/*�O���t�B�b�N�̃��[�h*/
	m_handle = LoadGraph(_T("data/Object/RecoveryItem.png"));
	/*SE�̃��[�h*/
	m_hitSeHandle = LoadSoundMem(_T("data/Sound/SE/Recovery.wav"));
}

RecoveryItem::~RecoveryItem()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_handle);
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_hitSeHandle);
}

void RecoveryItem::Init(float x, float y)
{
	// �����ʒu�̐ݒ�
	m_pos.x = x;
	m_pos.y = y;

	// �T�C�Y�̐ݒ�
	GetGraphSize(m_handle, &m_w, &m_h);

	// ���X�^�[�g�p�̏�����
	m_isExist = true;
}

void RecoveryItem::Update()
{
	// ���݂��Ȃ��G�l�~�[�̏����͂��Ȃ�
	if (!m_isExist)return;

	// �����蔻��̍X�V
	GetRect();
	PlayerCollision();
	InhaleCollision();

	// �A�j���[�V����
	m_sinCount += kSinSpeed;
	m_animationHeight = sinf(m_sinCount) * kAnimationSize;	
}

void RecoveryItem::Draw()
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

	DrawExtendGraph(static_cast<int>(x), static_cast<int>(posY), static_cast<int>(x) + m_w, static_cast<int>(y) + m_h, m_handle, true);

#ifdef _DEBUG
	// �����蔻��̋�`
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect RecoveryItem::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float RecoveryItem::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float RecoveryItem::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float RecoveryItem::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float RecoveryItem::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void RecoveryItem::PlayerCollision()
{
	// �v���C���[�ɓ��������ꍇ�́A�v���C���[���񕜂���
	if (m_colRect.isCol(m_pPlayer->GetColRect()))
	{
		PlaySoundMem(m_hitSeHandle, DX_PLAYTYPE_BACK, true);
		m_pPlayer->RecoveryHp2();
		m_isExist = false;
	}

}

void RecoveryItem::InhaleCollision()
{
	if (!m_pInhale->IsExsist())return;
	if (m_colRect.isCol(m_pInhale->GetRect()))
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
