#include "DxLib.h"
#include "RecoveredItem.h"
#include "WorldSprite.h"
#include "Player.h"
#include "Util/Game.h"

#include <cassert>
#include <cmath>

RecoveredItem::RecoveredItem(shared_ptr<Player> pPlayer):
	m_pos{0,0,0},
	m_modelHandle(-1),
	m_chatchSeHandle(-1),
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
	/*���f���̃f���[�g*/
	MV1DeleteModel(m_modelHandle);
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_chatchSeHandle);
}

void RecoveredItem::Init(float x, float z)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/Heart.mv1");
	assert(m_modelHandle != -1);
	/*SE�̃��[�h*/
	m_chatchSeHandle = LoadSoundMem("Data/Sound/SE/ItemChatchSE.mp3");
	assert(m_chatchSeHandle != -1);
	/*SE�̉��ʒ���*/
	ChangeVolumeSoundMem(kSeVolume, m_chatchSeHandle);

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

void RecoveredItem::Update()
{
	if (!m_isExist) return;

	// ���f���̃X�P�[����ݒ肷��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f,0.0f, 0.0f));

	// �����蔻��
	CollisionToPlayer(m_pPlayer->GetPos(), m_pPlayer->GetRadius());
	// �ړ�
	m_sinCount += kSinSpeed;
	m_sinPosY = sinf(m_sinCount) * kMoveSwing;
	m_pos.y += m_sinPosY;

	MV1SetPosition(m_modelHandle, m_pos);


}

void RecoveredItem::Draw()
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
		PlaySoundMem(m_chatchSeHandle, DX_PLAYTYPE_BACK);
		m_isExist = false;
	}
}
