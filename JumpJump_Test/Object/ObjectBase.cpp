#include "ObjectBase.h"
#include "Model.h"
#include "ObjectManager.h"
#include "../Util/Time.h"
#include "Player.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;	// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;	// �ǉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;		// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kMove = 0.01f;			// �ړ��������𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyBorder = 0.4f;	// �ǃ|���S�������|���S�����𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyHeight = 5.0f;	// �ǃ|���S���Ɣ��f���邽�߂̍����ϐ�
	constexpr int kExistTimeCount = 10;		// ����ł���̎���
	constexpr float kHeadHeight = 40.0f;	// ���̍���
}


ObjectBase::ObjectBase():
	m_objSize(0.0f),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_modelH(-1),
	m_isMove(false),
	m_isHit(false),
	m_wallNum(0),
	m_floorNum(0),
	m_hitDim{},
	m_pWallPoly{},
	m_pFloorPoly{},
	m_pPoly(nullptr),
	m_lineRes{},
	m_oldPos{0,0,0},
	m_nextPos{0,0,0},
	m_pExistCountTime(std::make_shared<Time>(kExistTimeCount))
{
	m_info.pos = VGet(0.0f, 0.0f, 0.0f);
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.isExist = true;
}

ObjectBase::~ObjectBase()
{
}

bool ObjectBase::IsExistCount()
{
	// �K�莞�Ԃ��߂����瑶�݂�����
	if (m_pExistCountTime->Update())
	{
		return true;
	}
	return false;
}

void ObjectBase::End()
{
	*m_pWallPoly = nullptr;
	*m_pFloorPoly = nullptr;
	m_pPoly = nullptr;
}

void ObjectBase::MoveCollFieldUpdate(ObjectBase* pField)
{
	// �ړ��O�̍��W��ۑ����Ă���
	m_oldPos = m_info.pos;
	// �ړ���̍��W���v�Z����
	m_nextPos = VAdd(m_oldPos, GetInfo().vec);

	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// �ړ��������l�����Ă��猟�o����
	m_hitDim = MV1CollCheck_Sphere(pField->GetModel()->GetModelHandle(), -1, GetInfo().pos,
		dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius() + VSize(GetInfo().vec);
}

void ObjectBase::CheckWallAndFloor()
{
	

}

void ObjectBase::FixPosWithWall()
{
}

void ObjectBase::FixPosWithWallInternal()
{
}

void ObjectBase::FixPosWithFloor()
{
}
