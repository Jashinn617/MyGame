#include "ObjectBase.h"

#include "Model.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;		// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;		// �ǉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;	// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kMove = 0.01f;				// �ړ��������𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyBorder = 0.4f;		// �ǃ|���S�������|���S�����𔻒f����ׂ̕ϐ�
	constexpr float kWallPolyHeight = 20.0f;	// �ǃ|���S���Ɣ��f���邽�߂̍����ϐ�
}

ObjectBase::ObjectBase():
	m_modelH(-1),
	m_objSize(0.0f),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_isDamage(false),
	m_pModel(nullptr),
	m_pObjectManager(nullptr),
	m_wallNum(0),
	m_floorNum(0),
	m_isMove(false),
	m_isPolygonHit(false),
	m_prevPos{0.0f,0.0f,0.0f},
	m_nextPos{0.0f,0.0f,0.0f},
	m_pPoly(nullptr)
{
	// �L�����N�^�[���̏�����
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.isExist = true;
}

ObjectBase::~ObjectBase()
{
	/*��������*/
}

void ObjectBase::End()
{
	/*�|�C���^�̉��*/
	*m_pWallPoly = nullptr;
	*m_pFloorPoly = nullptr;
	m_pPoly = nullptr;
}

void ObjectBase::ShaderMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader)
{
	// ���f���|�C���^�������ꍇ�͉������Ȃ�
	if (m_pModel == nullptr)return;

	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// �V�F�[�_�̐ݒ�

		// �`��
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// �V�F�[�_���g��Ȃ��ݒ�ɖ߂�

}

void ObjectBase::MoveCollFieldUpdate(ObjectBase* pField)
{
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
