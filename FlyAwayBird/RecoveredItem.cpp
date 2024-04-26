#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem():
	m_pos{0,0,0},
	m_handle(-1),
	m_w(0),
	m_h(0),
	m_sinCount(0),
	m_sinPosY(0),
	m_pSprite(nullptr)
{
	/*��������*/
}

RecoveredItem::~RecoveredItem()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_handle);
}

void RecoveredItem::Init()
{
	//�摜�̃��[�h
	m_handle = LoadGraph("Data/Img/Cake.png");
	assert(m_handle != -1);
	// �摜�T�C�Y�̎擾
	GetGraphSize(m_handle, &m_w, &m_h);

	m_pos.y = kDownPosY;

	//�|�C���^�̐���
	m_pSprite = make_shared<WorldSprite>();
	// �X�v���C�g�̐���
	m_pSprite->Initialize(m_handle, m_w, m_h);
}

void RecoveredItem::Update()
{
	// �ړ�
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;
	// �ʒu�A�T�C�Y�̐ݒ�
	m_pSprite->SetTransform(m_pos, kSize);

}

void RecoveredItem::Draw()
{
	m_pSprite->Draw();

	// �����蔻��̕\��
#ifdef _DEBUG
	VECTOR pos = m_pos;
	pos.y -= 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0xff0000, 0xff0000, false);
#endif // _DEBUG
}
