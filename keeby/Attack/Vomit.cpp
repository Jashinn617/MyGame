#include "Vomit.h"
#include "DxLib.h"
#include "../Game.h"
#include "../Camera.h"
#include "../Player.h"

Vomit::Vomit() :
	m_bulletHandle(-1),
	m_w(0),
	m_h(0),
	m_speed(10),
	m_pos(0.0f, 0.0f),
	m_isExist(false)
{
	/*�O���t�B�b�N�̃��[�h*/
	m_bulletHandle = LoadGraph("data/Object/MonochromeFlower.png");

	// �O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(m_bulletHandle, &m_w, &m_h);
}

Vomit::~Vomit()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_bulletHandle);
}

void Vomit::Init()
{
	
}

void Vomit::Draw()
{
	// ���݂��Ȃ��ƕ`�悵�Ȃ�
	if (!m_isExist)return;

	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	if (m_pPlayer->GetDir() == m_pPlayer->GetDirLeft())
	{
		DrawTurnGraph(static_cast<int>(x), static_cast<int>(y), m_bulletHandle, true);
	}
	else if (m_pPlayer->GetDir() == m_pPlayer->GetDirRight())
	{
		DrawGraph(static_cast<int>(x), static_cast<int>(y), m_bulletHandle, true);
	}
#ifdef _DEBUG
	DrawBox(static_cast<int>(GetLeft()),static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0x00ff00, false);
#endif
}

void Vomit::Update()
{
	if (!m_isExist)return;

	m_pos.x -= m_speed;

	// �����蔻��̍X�V
	GetRect();

	 //����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	 //�X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	 //��ʊO�ɏo���ꍇ�͑��݂�����
	if (x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
	if (x < 0)
	{
		m_isExist = false;
	}
}

Rect Vomit::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float Vomit::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float Vomit::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float Vomit::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float Vomit::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void Vomit::PutBulletLeft()
{
	m_isExist = true;
	m_pos.x = m_pPlayer->GetLeft() - m_w;
	m_pos.y = m_pPlayer->GetBottom();
}

void Vomit::PutBulletRight()
{
	m_isExist = true;
	m_pos.x = m_pPlayer->GetLeft() + m_w;
	m_pos.y = m_pPlayer->GetBottom();
}