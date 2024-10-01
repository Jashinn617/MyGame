#include "ItemStop.h"

#include "../Circle.h"
#include "../Model.h"

#include "../../Shader/ToonShader.h"

#include <math.h>

namespace
{
	constexpr float kAngleZ = 270.0f * DX_PI_F / 180.0f;	// Z���̊p�x
	constexpr float kMoveSinSpeed = 0.03f;	// �㉺�ړ��̑��x
	constexpr float kMoveSwing = 0.1f;		// �㉺�ړ��̈ړ���
	constexpr float kAngleSpeed = 0.05f;		// ��]�X�s�[�h
	constexpr float kModelScalse = 0.21f;	// ���f���X�P�[��
	constexpr float kItemSize = 13;			// �T�C�Y
	constexpr float kHeight = -10.0f;		// ����
}

ItemStop::ItemStop(VECTOR pos):
	m_angleX(0),
	m_moveSinCount(0)
{
	m_info.pos = pos;
	// �T�C�Y
	m_objSize = kItemSize;
	m_pCircle = std::make_shared<Circle>(m_info.pos, kItemSize, kHeight);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);

	m_moveSpeed = kMoveSinSpeed;

	InitMoveSpeed(m_statusData.spd);
	m_moveData.rotSpeed = kAngleSpeed;
}

ItemStop::~ItemStop()
{
	/*��������*/
}

void ItemStop::Init()
{
	m_pModel = std::make_shared<Model>(m_modelH);
	m_pModel->SetScale(VGet(kModelScalse, kModelScalse, kModelScalse));
	m_pModel->SetRot(m_info.rot);
	m_pModel->SetPos(m_info.pos);
}
//
//void ItemStop::Draw(std::shared_ptr<ToonShader> pToonShader)
//{
//	m_pModel->Draw();
//
//	/*for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
//	{
//		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);
//
//		pToonShader->SetShader(shaderType);
//		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
//	}
//	pToonShader->ShaderEnd();*/
//
//	m_pCircle->DebugDraw();
//}

void ItemStop::MoveDirectionUpdate()
{
	// �㉺�ړ�
	m_moveSinCount += kMoveSinSpeed;
	m_moveDirectionVec.y = sinf(m_moveSinCount) * kMoveSwing;	
}

VECTOR ItemStop::MoveUpdate()
{
	if (m_moveSpeed == 0.0f) return VGet(0.0f, 0.0f, 0.0f);

	// �ړ������̍X�V
	MoveDirectionUpdate();
	// �p�x�X�V
	AngleUpdate();

	return m_moveDirectionVec;
}

void ItemStop::AngleUpdate()
{
	// ���̏�ŉ�]����
	m_angleX += kAngleSpeed;
	m_pModel->SetRot(VGet(m_angleX, 0.0f, kAngleZ));
}
