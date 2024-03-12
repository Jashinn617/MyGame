#include "GoalFlower.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Game.h"
#include "DxLib.h"

GoalFlower::GoalFlower():
	m_w(0),
	m_h(0),
	m_colorHandle(-1),
	m_monochoromeHandle(-1),
	m_isColor(false),
	m_x(0),
	m_y(0),
	m_decorationAngle(0),
	m_isColition(false)
{
	// ���W�̏�����
	m_pos = Vec2(0, 0);

	/*�O���t�B�b�N�̃��[�h*/
	m_colorHandle = LoadGraph(_T("data/Object/ColorFlower.png"));
	m_monochoromeHandle = LoadGraph(_T("data/Object/MonochromeFlower.png"));
}

GoalFlower::~GoalFlower()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_colorHandle);
	DeleteGraph(m_monochoromeHandle);
}

void GoalFlower::Init(float x, float y)
{
	// �����ʒu�̐ݒ�
	m_pos.x = x;
	m_pos.y = y;

	// �T�C�Y�̐ݒ�
	GetGraphSize(m_colorHandle, &m_w, &m_h);
}

void GoalFlower::Update()
{
	// �����蔻��̍X�V
	GetRect();
	PlayerCollision();

	// �Ԃ���
	m_decorationAngle += 0.05f;
}

void GoalFlower::Draw()
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	if (m_isColor)
	{
		DrawRotaGraph(static_cast<int>(x) + static_cast<int>((m_w * 0.5f)), static_cast<int>(y) + static_cast<int>((m_h * 0.5f)), 1.5, m_decorationAngle, m_colorHandle, true);
	}
	else
	{
		DrawRotaGraph(static_cast<int>(x) + static_cast<int>((m_w * 0.5f)), static_cast<int>(y) + static_cast<int>((m_h * 0.5f)), 1.5, m_decorationAngle, m_monochoromeHandle, true);
	}

#ifdef _DEBUG
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect GoalFlower::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float GoalFlower::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float GoalFlower::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float GoalFlower::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float GoalFlower::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void GoalFlower::PlayerCollision()
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

void GoalFlower::RePosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}
