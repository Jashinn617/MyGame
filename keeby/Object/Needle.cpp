#include "Needle.h"
#include "../Player.h"
#include "../Camera.h"
#include "../Game.h"
#include "DxLib.h"

Needle::Needle():
	m_w(0),
	m_h(0),
	m_handle(-1),
	m_x(0),
	m_y(0),
	m_angle(0)
{
	// �ʒu�̏�����
	m_pos = Vec2(0, 0);
	/*�O���t�B�b�N�̃��[�h*/
	m_handle = LoadGraph(_T("data/Object/Needle.png"));
}

Needle::~Needle()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_handle);
}

void Needle::Init(float x, float y, float angle)
{
	// �����ʒu�̐ݒ�
	m_pos.x = x;
	m_pos.y = y;

	// �p�x�̐ݒ�
	m_angle = angle;

	// �T�C�Y�̐ݒ�
	GetGraphSize(m_handle, &m_w, &m_h);
}

void Needle::Update()
{
	// �����蔻��̍X�V
	GetRect();
	PlayerCollision();

}

void Needle::Draw()
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	DrawRotaGraph(static_cast<int>(x) + static_cast<int>((m_w * 0.5f)), static_cast<int>(y) + static_cast<int>((m_h * 0.5f)), 1.0, m_angle, m_handle, true);

#ifdef _DEBUG
	// �����蔻��̋�`
	DrawBox(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetRight()), static_cast<int>(GetBottom()), 0xff0000, false);
#endif
}

Rect Needle::GetRect()
{
	m_colRect.top = GetTop();
	m_colRect.left = GetLeft();
	m_colRect.bottom = GetBottom();
	m_colRect.right = GetRight();

	return m_colRect;
}

float Needle::GetLeft() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x;
}

float Needle::GetRight() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return x + m_w;
}

float Needle::GetTop() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y;
}

float Needle::GetBottom() const
{
	// ����������������W�ɕϊ�����
	float x = m_pos.x - m_w * 0.5f;
	float y = m_pos.y - m_h;
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	return y + m_h;
}

void Needle::PlayerCollision()
{
	// �v���C���[�ɓ��������ꍇ�́A�v���C���[�Ƀ_���[�W��^����
	if (m_colRect.isCol(m_pPlayer->GetColRect()))
	{
		m_pPlayer->OnDamage();
	}
}

