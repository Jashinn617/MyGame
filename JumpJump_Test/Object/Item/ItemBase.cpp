#include "ItemBase.h"
#include <assert.h>

namespace
{
	constexpr float kScale = 0.05f;
}

ItemBase::ItemBase(int modelHandle):
	m_modelHandle(-1),
	m_psH(-1),
	m_vsH(-1),
	m_rad(4),
	m_scale(0),
	m_pos{0,0,0},
	m_angle(0),
	m_angleSpeed(0)
{
	// ���f���̓ǂݍ���
	m_modelHandle = MV1DuplicateModel(modelHandle);
	assert(m_modelHandle != -1);
	// �V�F�[�_�̃��[�h
	m_psH = LoadPixelShader("PixelTest.pso");
	assert(m_psH != -1);
	m_vsH = LoadVertexShader("VertexShader.vso");
	assert(m_vsH != -1);

	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}

ItemBase::~ItemBase()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void ItemBase::Draw()
{
	// �����蔻��̃f�o�b�O�\��
#ifdef _DEBUG
	DrawSphere3D(m_pos, m_rad, 32, 0xff0000, 0xff00000, false);
#endif // _DEBUG
	// �V�F�[�_��K�p����
	MV1SetUseOrigShader(true);
	SetUseVertexShader(m_vsH);
	SetUsePixelShader(m_psH);
	// ���f���̕`��
	MV1DrawModel(m_modelHandle);
	// �V�F�[�_�𖳌�������
	MV1SetUseOrigShader(false);
	SetUseVertexShader(-1);
	SetUsePixelShader(-1);
}

void ItemBase::UpdateAngle()
{
}
