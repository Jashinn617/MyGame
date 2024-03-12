#include "Inhale.h"
#include "DxLib.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Player.h"

namespace
{
	// �A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,0 };
	// 1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 3;
	// �P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// �O���t�B�b�N�T�C�Y
	constexpr int kWidth = 130;
	constexpr int kHeight = 95;

}

Inhale::Inhale() :
	m_pos(0.0f, 0.0f),
	m_w(kWidth),
	m_h(kHeight),
	m_isExist(false),
	m_animFrame(0)
{
	/*�O���t�B�b�N�̃��[�h*/
	m_inhaleHandle = LoadGraph("data/Player/AInhale.png");	
}

Inhale::~Inhale()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_inhaleHandle);
}

void Inhale::Init()
{

}

void Inhale::Draw()
{
	// ���݂��Ȃ��ƕ`�悵�Ȃ�
	if (!m_isExist)return;

	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// �A�j���[�V����
	int animFrame = m_animFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_pPlayer->GetDir();


	DrawRectGraph(static_cast<int>(x),static_cast<int>(y), srcX, srcY, kWidth, kHeight, m_inhaleHandle, true);

#ifdef _DEBUG
	DrawBox(static_cast<int>(GetLeft()),static_cast<int>(GetTop()),static_cast<int>(GetRight()),static_cast<int>(GetBottom()), 0x00ff00, false);
#endif
}

void Inhale::Update()
{
	if (!m_isExist)return;

	// �����蔻��̍X�V
	GetRect();

	// �A�j���[�V����
	if (m_isExist)
	{
		m_animFrame++;
		if (m_animFrame >= kAnimFrameCycle)
		{
			m_animFrame = 0;
		}
	}
}

Rect Inhale::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float Inhale::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float Inhale::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float Inhale::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float Inhale::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void Inhale::PutBulletLeft()
{
	m_isExist = true;
	m_pos.x = m_pPlayer->GetLeft() - (m_w * 0.5f);
	m_pos.y = m_pPlayer->GetBottom();
}

void Inhale::PutBulletRight()
{
	m_isExist = true;
	m_pos.x = m_pPlayer->GetLeft() + m_w;
	m_pos.y = m_pPlayer->GetBottom();
}

void Inhale::FalseExist()
{
	m_isExist = false;
	m_animFrame = 0;
}