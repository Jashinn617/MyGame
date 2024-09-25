#include "ShadowMapShader.h"
#include "../Util/Game.h"

#include <cassert>

namespace
{
	constexpr int kShadowMapSizeX = 15360;
	constexpr int kShadowMapSizeY = 8640;

	// �J�����̎���p
	constexpr float kShadowMapFov = 45.0f * DX_PI_F / 180.0f;
	constexpr float kNormalFov = 60.0f * DX_PI_F / 180.0f;
}

ShadowMapShader::ShadowMapShader()
{
	/*���_�V�F�[�_*/
	m_vertexShader1FrameH = LoadVertexShader("Data/Shader/Vertex/VertexShader3D.vso");
	assert(m_vertexShader1FrameH != -1);
	m_vertexShader4FrameH = LoadVertexShader("Data/Shader/Vertex/VertexShader3D4Frame.vso");
	assert(m_vertexShader4FrameH != -1);
	m_vertexShader8FrameH = LoadVertexShader("Data/Shader/Vertex/VertexShader3D8Frame.vso");
	assert(m_vertexShader8FrameH != -1);
	m_vertexShaderNormal4FrameH = LoadVertexShader("Data/Shader/Vertex/VertexShader3DNormal4Frame.vso");
	assert(m_vertexShaderNormal4FrameH != -1);
	m_vertexShaderNormal8FrameH = LoadVertexShader("Data/Shader/Vertex/VertexShader3DNormal8Frame.vso");
	assert(m_vertexShaderNormal8FrameH != -1);
	m_vertexShaderShadowMapFieldH = LoadVertexShader("Data/Shader/Vertex/VertexShaderShadowMap.vso");
	assert(m_vertexShaderShadowMapFieldH != -1);
	/*�s�N�Z���V�F�[�_*/
	m_pixelShaderH = LoadPixelShader("Data/Shader/Pixel/PixelShaderShadowMap.pso");
	assert(m_pixelShaderH != -1);
	m_pixelShaderFieldH = LoadPixelShader("Data/Shader/Pixel/ToonPixelShaderField.pso");
	assert(m_pixelShaderFieldH != -1);

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
	// �A�h���X�̎擾
	m_pCbufferCameraPos = static_cast<VECTOR*>(GetBufferShaderConstantBuffer(m_cbufferCameraPosH));

	// �r���[�v���W�F�N�V�����s��̒萔�o�b�t�@�̍쐬
	m_cbufferViewProjectionMatH = CreateShaderConstantBuffer(sizeof(MATRIX));
	assert(m_cbufferViewProjectionMatH != -1);
	// �A�h���X�̎擾
	m_viewProjectionMat = static_cast<MATRIX*>(GetBufferShaderConstantBuffer(m_cbufferViewProjectionMatH));

	// �V���h�E�}�b�v�̍쐬
	m_shadowMap = MakeScreen(kShadowMapSizeX, kShadowMapSizeY);
	assert(m_shadowMap != -1);
}

ShadowMapShader::~ShadowMapShader()
{
	// �V�F�[�_�̃f���[�g
	DeleteShader(m_vertexShader1FrameH);
	DeleteShader(m_vertexShader4FrameH);
	DeleteShader(m_vertexShader8FrameH);
	DeleteShader(m_vertexShaderNormal4FrameH);
	DeleteShader(m_vertexShaderNormal8FrameH);

	DeleteShader(m_pixelShaderH);
	DeleteShader(m_pixelShaderFieldH);
	DeleteShader(m_shadowMap);

	DeleteShaderConstantBuffer(m_cbufferLightDirH);
	DeleteShaderConstantBuffer(m_cbufferCameraTargetPosH);
	DeleteShaderConstantBuffer(m_cbufferCameraPosH);
	DeleteShaderConstantBuffer(m_cbufferViewProjectionMatH);
}

void ShadowMapShader::WriteStart(VECTOR targetPos)
{
	// �V���h�E�}�b�v�ւ̏������݂̊J�n
	SetDrawScreen(m_shadowMap);
	ClearDrawScreen();
	DrawBox(0, 0, kShadowMapSizeX, kShadowMapSizeY, 0xffffff, true);

	// �V���h�E�}�b�v�̃J�����̈ʒu�ƌ�����ݒ肷��
	SetCameraPositionAndTargetAndUpVec(GetLightPosition(), targetPos, VGet(1, 0, 0));

	// �V���h�E�}�b�v�������ݎ��̃J�����̎���p
	// ClearDrawScreen�������Ƃ��ɃN���A�������̂��Đݒ肵�Ă���
	SetupCamera_Perspective(kShadowMapFov);
}

void ShadowMapShader::SetShadowMapCameraTarget(VECTOR targetPos)
{
	// �J�������W�̎擾
	m_pCbufferCameraPos[0] = targetPos;
}

void ShadowMapShader::SetShader(int shaderType)
{
	// ���C�g�̌����̎擾
	m_pCbufferLightDir[0] = GetLightDirection();
	// �J�����̃^�[�Q�b�g�̈ʒu�̎擾
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();

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
	// �V�F�[�_��K�p����
	MV1SetUseOrigShader(true);

	//���f���̃^�C�v�ɂ���ēK��������V�F�[�_�[��ς���
	if (shaderType == DX_MV1_VERTEX_TYPE_1FRAME)
	{
		SetUseVertexShader(m_vertexShader1FrameH);

	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_4FRAME)
	{
		SetUseVertexShader(m_vertexShader4FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_8FRAME)
	{
		SetUseVertexShader(m_vertexShader8FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_NMAP_1FRAME)
	{
		SetUseVertexShader(m_vertexShader1FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_NMAP_4FRAME)
	{
		SetUseVertexShader(m_vertexShaderNormal4FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_NMAP_8FRAME)
	{
		SetUseVertexShader(m_vertexShaderNormal8FrameH);
	}
	else if (shaderType == DX_MV1_VERTEX_TYPE_NMAP_FREE_FRAME)
	{
		SetUseVertexShader(m_vertexShader1FrameH);
	}
	else
	{
		MV1SetUseOrigShader(false);
	}

	// �s�N�Z���V�F�[�_�̃Z�b�g
	SetUsePixelShader(m_pixelShaderH);
}

void ShadowMapShader::SetShaderField(VECTOR targetPos)
{
	// �r���[�v���W�F�N�V�����s��̎擾
	*m_viewProjectionMat = ViewProjectionMatrix(targetPos);

	// ���C�g�̌����̎擾
	m_pCbufferLightDir[0] = GetLightDirection();
	// �J�����̃^�[�Q�b�g�̈ʒu�̎擾
	m_pCbuffferCameraTargetPos[0] = GetCameraTarget();
	// �J�����̈ʒu�̎擾
	m_pCbufferCameraPos[0] = GetCameraPosition();
	
	SetUseTextureToShader(1, m_shadowMap);	

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
	// �r���[�v���W�F�N�V�����s��
	UpdateShaderConstantBuffer(m_cbufferViewProjectionMatH);
	SetShaderConstantBuffer(m_cbufferViewProjectionMatH, DX_SHADERTYPE_VERTEX, 4);

	// �V�F�[�_�̓K�p
	MV1SetUseOrigShader(true);
	// ���_�V�F�[�_�̐ݒ�
	SetUseVertexShader(m_vertexShaderShadowMapFieldH);
	// �s�N�Z���V�F�[�_�̐ݒ�
	SetUsePixelShader(m_pixelShaderFieldH);
}

void ShadowMapShader::WriteEnd()
{
	// �V���h�E�}�b�v�ւ̏������݂��I���
	SetDrawScreen(DX_SCREEN_BACK);
	MV1SetUseOrigShader(false);
	// �ʏ펞�̃J�����̎���p
	SetupCamera_Perspective(kNormalFov);
}

MATRIX ShadowMapShader::ViewProjectionMatrix(VECTOR targetPos)
{
	// �r���[�s��
	MATRIX viewMat = GetCameraViewportMatrix();

	VECTOR cameraPos = GetLightPosition();
	VECTOR cameraTargetPos = targetPos;
	VECTOR UpVec = VGet(1, 0, 0);

	// �r���[�s��̌v�Z
	CreateLookAtMatrix(&viewMat, &cameraPos, &cameraTargetPos, &UpVec);
	// �ˉe�s��̍쐬
	MATRIX mat;

	// �ˉe�s��̌v�Z
	CreatePerspectiveFovMatrix(&mat, kShadowMapFov, GetCameraNear(), GetCameraFar(), 9.0f / 16.0f);

	// �r���[�v���W�F�N�V�����s��̍쐬
	MATRIX viewProjectionMat = MMult(viewMat, mat);

	return viewProjectionMat;
}
