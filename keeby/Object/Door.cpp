#include "Door.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Game.h"
#include "DxLib.h"

#include <cassert>

Door::Door():
	m_w(0),
	m_h(0),
	m_handle(-1),
	m_x(0),
	m_y(0),
	m_decorationAngle(0),
	m_isColition(false)
{
	// ���W�̏�����
	m_pos = Vec2(0, 0);

	/*�O���t�B�b�N�̃��[�h*/
	m_handle = LoadGraph(_T("data/Object/Door.png"));
	m_decorationHandle = LoadGraph(_T("data/Object/ColorFlower.png"));
}

Door::~Door()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_handle);
	DeleteGraph(m_decorationHandle);
}

void Door::Init(float x, float y)
{
	// �����ʒu�̐ݒ�
	m_pos.x = x;
	m_pos.y = y;

	// �T�C�Y�̐ݒ�
	GetGraphSize(m_handle, &m_w, &m_h);
}

void Door::Update()
{
	// �����蔻��̍X�V
	GetRect();
	PlayerCollision();

	// �Ԃ���
	m_decorationAngle += 0.05f;
}

void Door::Draw()
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// �h�A�{�̂̕`��
	DrawGraph(static_cast<int>(x),static_cast<int>(y), m_handle, true);
	// �Ԃ̕`��
	DrawRotaGraph(static_cast<int>(x + (m_w * 0.5f)), static_cast<int>(y + (m_h * 0.5f)) - 64, 1.2, m_decorationAngle, m_decorationHandle, true);

#ifdef _DEBUG
	// �����蔻��̋�`
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect Door::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float Door::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float Door::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float Door::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float Door::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void Door::PlayerCollision()
{
	if (m_colRect.isCol(m_pPlayer->GetColRect()))
	{
		m_isColition = true;
	}
	else
	{
		m_isColition = false;
	}
}
