#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"
#include "Player.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem(shared_ptr<Player> pPlayer):
	m_pos{0,0,0},
	m_handle(-1),
	m_w(0),
	m_h(0),
	m_isExist(true),
	m_sinCount(0),
	m_sinPosY(0),
	m_pPlayer(pPlayer),
	m_pSprite(nullptr)
{
	/*��������*/
}

RecoveredItem::~RecoveredItem()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_handle);
}

void RecoveredItem::Init(float x, float z)
{
	//�摜�̃��[�h
	m_handle = LoadGraph("Data/Img/Cake.png");
	assert(m_handle != -1);
	// �摜�T�C�Y�̎擾
	GetGraphSize(m_handle, &m_w, &m_h);

	int rand = GetRand(1);
	if (rand == 0)
	{
		m_pos = VGet(x, kDownPosY, z);
	}
	else if (rand == 1)
	{
		m_pos = VGet(x, kUpPosY, z);
	}


	//�|�C���^�̐���
	m_pSprite = make_shared<WorldSprite>();
	// �X�v���C�g�̐���
	m_pSprite->Initialize(m_handle, m_w, m_h);
}

void RecoveredItem::Update()
{
	if (!m_isExist) return;
	// �����蔻��
	CollisionToPlayer(m_pPlayer->GetPos(), m_pPlayer->GetRadius());
	// �ړ�
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;
	// �ʒu�A�T�C�Y�̐ݒ�
	m_pSprite->SetTransform(m_pos, kSize);


}

void RecoveredItem::Draw()
{
	if (!m_isExist) return;
	m_pSprite->Draw();

	// �����蔻��̕\��
#ifdef _DEBUG
	VECTOR pos = m_pos;
	pos.y -= 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0xff0000, 0xff0000, false);
#endif // _DEBUG
}

void RecoveredItem::CollisionToPlayer(VECTOR pVec, float pRad)
{
	// �v���C���[�ƃA�C�e���̔��a�̍��v
	float rad = kRadius + pRad;
	// �v���C���[�ƃA�C�e���̋����̌v�Z
	VECTOR dirVec = VSub(m_pos, pVec);
	float dir = VSize(dirVec);
	
	// �v���C���[�Ɠ������Ă��邩�ǂ���
	if (dir < rad)
	{
#ifdef _DEBUG
		printfDx("��������");
#endif // _DEBUG
		m_isExist = false;
	}
}
