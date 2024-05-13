#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"
#include "Player.h"
#include "Util/Game.h"
#include "Util/HandleManager.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem(shared_ptr<Player> pPlayer):
	m_pos{0,0,0},
	m_modelHandle(-1),
	m_w(0),
	m_h(0),
	m_isExist(true),
	m_sinCount(0),
	m_sinPosY(0),
	m_pPlayer(pPlayer)
{
	/*��������*/
}

RecoveredItem::~RecoveredItem()
{
	/*��������*/
}

void RecoveredItem::Init(float x, float z, HandleManager& handle)
{
	
	/*SE�̉��ʒ���*/
	ChangeVolumeSoundMem(kSeVolume,handle.GetSound("itemChatchSE"));
	m_modelHandle = MV1DuplicateModel(handle.GetModel("item"));

	int rand = GetRand(1);
	if (rand == 0)
	{
		m_pos = VGet(x, kDownPosY, z);
	}
	else if (rand == 1)
	{
		m_pos = VGet(x, kUpPosY, z);
	}
}

void RecoveredItem::Update(HandleManager& handle)
{
	if (!m_isExist) return;

	// ���f���̃X�P�[����ݒ肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f,0.0f, 0.0f));

	// �����蔻��
	CollisionToPlayer(m_pPlayer->GetPos(), m_pPlayer->GetRadius(),handle);
	// �ړ�
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;

	MV1SetPosition(m_modelHandle, m_pos);
}

void RecoveredItem::Draw(HandleManager& handle)
{
	if (!m_isExist) return;

	MV1DrawModel(m_modelHandle);
	

	// �����蔻��̕\��
#ifdef _DEBUG
	VECTOR pos = m_pos;
	pos.y -= 0.1f;
	DrawSphere3D(pos, kRadius, 32, 0xff0000, 0xff0000, false);
#endif // _DEBUG
}

void RecoveredItem::CollisionToPlayer(VECTOR pPos, float pRad, HandleManager& handle)
{
	// �v���C���[�ƃA�C�e���̔��a�̍��v
	float rad = kRadius + pRad;
	// �v���C���[�ƃA�C�e���̋����̌v�Z
	VECTOR dirVec = VSub(m_pos, pPos);
	float dir = VSize(dirVec);
	
	// �v���C���[�Ɠ������Ă��邩�ǂ���
	if (dir < rad)
	{
#ifdef _DEBUG
		printfDx("��������");
#endif // _DEBUG
		PlaySoundMem(handle.GetSound("itemChatchSE"), DX_PLAYTYPE_BACK);
		m_isExist = false;
	}
}
