#include "EnemyBase.h"
#include <assert.h>

namespace
{
	constexpr float kScale = 0.05f;		// �X�P�[��
}


EnemyBase::EnemyBase(int modelHandle):
	m_modelHandle(-1),
	m_rad(4),
	m_scale(1),
	m_pos{0,0,0},
	m_angle{0,0,0}
{
	// ���f���̓ǂݍ���
	m_modelHandle = MV1DuplicateModel(modelHandle);
	assert(m_modelHandle != -1);
	// �V�F�[�_�̃��[�h
	m_psHs.push_back(LoadPixelShader("MV1PixelShader.pso"));
	assert(m_psHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader4Frame.vso"));
	assert(m_vsHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader8Frame.vso"));
	assert(m_vsHs.back() != -1);

	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// ���f���̃g���C�A���O�����X�g���ɑΉ�����V�F�[�_��ݒ肷��
	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		switch (MV1GetTriangleListVertexType(m_modelHandle,i))
		{
		case DX_MV1_VERTEX_TYPE_4FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(0);
		case DX_MV1_VERTEX_TYPE_8FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(1);
		default:
			m_pixelShaderNumbers.push_back(-1);
			m_vertexShaderNumbers.push_back(-1);
			break;
		}
	}
}

EnemyBase::~EnemyBase()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void EnemyBase::Draw()
{
	// �����蔻��̃f�o�b�O�\��
#ifdef _DEBUG
	VECTOR pos = VAdd(MV1GetPosition(m_modelHandle), VGet(0, m_rad, 0));
	VECTOR overheadPos = VAdd(pos, VGet(0, 2, 0));

	DrawSphere3D(pos, m_rad, 32, 0xff0000, 0xff00000, false);
	DrawSphere3D(overheadPos, 3, 32, 0x0000ff, 0xff000ff, false);
#endif // _DEBUG

	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		if (m_vertexShaderNumbers[i] && m_pixelShaderNumbers[i] == -1)
		{
			MV1SetUseOrigShader(false);
			SetUseVertexShader(-1);
			SetUsePixelShader(-1);
		}
		else
		{
			MV1SetUseOrigShader(true);
			SetUseVertexShader(m_vsHs[m_vertexShaderNumbers[i]]);
			SetUsePixelShader(m_psHs[m_pixelShaderNumbers[i]]);
		}
		MV1DrawTriangleList(m_modelHandle, i);
	}
}

void EnemyBase::AdjustmentModelPos() const
{
	// ���f���̈ʒu�ݒ�
	MV1SetPosition(m_modelHandle, m_pos);
}
