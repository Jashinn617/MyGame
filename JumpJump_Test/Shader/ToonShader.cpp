#include "ToonShader.h"
#include "../Util/Game.h"

#include <cassert>
#include <array>


ToonShader::ToonShader()
{
	m_vertexShader4FrameH = LoadVertexShader("MV1VertexShader4Frame.vso");
	assert(m_vertexShader4FrameH != -1);
	m_vertexShader8FrameH = LoadVertexShader("MV1VertexShader8Frame.vso");
	assert(m_vertexShader8FrameH != -1);
	m_pixelShaderH = LoadPixelShader("ToonShader.pso");
	assert(m_pixelShaderH != -1);
	m_pixelShaderFieldH = LoadPixelShader("ToonFieldShader.pso");
	assert(m_pixelShaderFieldH != -1);
	m_graphH = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	assert(m_graphH != -1);

	/*���C�g�̒萔�o�b�t�@�̍쐬*/
	m_cbufferLightDirH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferLightDirH != -1);
	// �A�h���X�̎擾
	m_pCbufferLightDir = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferLightDirH));

	/*�J�����̃^�[�Q�b�g�̈ʒu�̒萔�o�b�t�@�̍쐬*/
	m_cbufferCameraTargetPosH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferCameraTargetPosH != -1);
	// �A�h���X�̎擾
	m_pCbuffferCameraTargetPos = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferCameraTargetPosH));

	/*�J�����̈ʒu�̒萔�o�b�t�@�̍쐬*/
	m_cbufferCameraPosH = CreateShaderConstantBuffer(sizeof(float) * 4);
	assert(m_cbufferCameraPosH != -1);
	m_pCbufferCameraPos = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferCameraPosH));
}

ToonShader::~ToonShader()
{
	// �V�F�[�_�̃f���[�g
	DeleteShader(m_vertexShader4FrameH);
	DeleteShader(m_vertexShader8FrameH);
	DeleteShader(m_pixelShaderH);
	DeleteShader(m_pixelShaderFieldH);
	DeleteShader(m_graphH);
	DeleteShaderConstantBuffer(m_cbufferLightDirH);
	DeleteShaderConstantBuffer(m_cbufferCameraTargetPosH);
	DeleteShaderConstantBuffer(m_cbufferCameraPosH);
}

void ToonShader::Update()
{
	/*��������*/
}

void ToonShader::SetShader(int shaderType)
{
	// ���C�g�̌����̎擾
	m_pCbufferLightDir[0] = GetLightDirection();
	// �J�����̃^�[�Q�b�g�̈ʒu�̎擾
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();
	// �J�����̈ʒu�̎擾
	m_pCbufferCameraPos[0] = GetCameraPosition();

	/*�������񂾒l��GPU�ɔ��f����*/
	// ���C�g�̌���
	UpdateShaderConstantBuffer(m_cbufferLightDirH);
	SetShaderConstantBuffer(m_cbufferLightDirH, DX_SHADERTYPE_PIXEL, 0);
	// �J�����̃^�[�Q�b�g�̈ʒu
	UpdateShaderConstantBuffer(m_cbufferCameraTargetPosH);
	SetShaderConstantBuffer(m_cbufferCameraTargetPosH, DX_SHADERTYPE_PIXEL, 1);
	// �J�����̈ʒu
	UpdateShaderConstantBuffer(m_cbufferCameraPosH);
	SetShaderConstantBuffer(m_cbufferCameraPosH, DX_SHADERTYPE_PIXEL, 2);

	// �V�F�[�_��K�p����
	MV1SetUseOrigShader(true);

	// ���f���̒��_�^�C�v�ɂ���ēK��������V�F�[�_��ς���
	if (shaderType == DX_MV1_VERTEX_TYPE_4FRAME)
	{
		SetUseVertexShader(m_vertexShader4FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_8FRAME)
	{
		SetUseVertexShader(m_vertexShader8FrameH);
	}
	else
	{
		MV1SetUseOrigShader(false);
	}

	// �s�N�Z���V�F�[�_�̃Z�b�g
	SetUsePixelShader(m_pixelShaderH);
}

void ToonShader::SetShaderField(int shaderType)
{
	// ���C�g�̌����̎擾
	m_pCbufferLightDir[0] = GetLightDirection();
	// �J�����̃^�[�Q�b�g�̈ʒu�̎擾
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();
	// �J�����̈ʒu�̎擾
	m_pCbufferCameraPos[0] = GetCameraPosition();

	/*�������񂾒l��GPU�ɔ��f����*/
	// ���C�g�̌���
	UpdateShaderConstantBuffer(m_cbufferLightDirH);
	SetShaderConstantBuffer(m_cbufferLightDirH, DX_SHADERTYPE_PIXEL, 0);
	// �J�����̃^�[�Q�b�g�̈ʒu
	UpdateShaderConstantBuffer(m_cbufferCameraTargetPosH);
	SetShaderConstantBuffer(m_cbufferCameraTargetPosH, DX_SHADERTYPE_PIXEL, 1);
	// �J�����̈ʒu
	UpdateShaderConstantBuffer(m_cbufferCameraPosH);
	SetShaderConstantBuffer(m_cbufferCameraPosH, DX_SHADERTYPE_PIXEL, 2);

	// �V�F�[�_��K�p����
	MV1SetUseOrigShader(true);
	// ���f���̒��_�^�C�v�ɂ���ēK��������V�F�[�_��ς���
	if (shaderType == DX_MV1_VERTEX_TYPE_4FRAME)
	{
		SetUseVertexShader(m_vertexShader4FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_8FRAME)
	{
		SetUseVertexShader(m_vertexShader8FrameH);
	}
	else
	{
		MV1SetUseOrigShader(false);
	}

	// �s�N�Z���V�F�[�_�̃Z�b�g
	SetUsePixelShader(m_pixelShaderFieldH);
}

void ToonShader::ShaderEnd()
{
	/*�V�F�[�_���g��Ȃ�*/
	MV1SetUseOrigShader(false);
}
