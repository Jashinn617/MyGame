#pragma once

#include "DxLib.h"

class ToonShader
{
public:
	ToonShader();
	virtual ~ToonShader();

	void Update();
	void SetShader(int shaderType);
	void SetShaderField(int shaderType);
	void ShaderEnd();

private:
	int m_vertexShader4FrameH;		// ���_�V�F�[�_4�t���[���̃n���h��	
	int m_vertexShader8FrameH;		// ���_�V�F�[�_8�t���[���̃n���h��
	int m_pixelShaderH;				// �s�N�Z���V�F�[�_�̃n���h��
	int m_pixelShaderFieldH;		// �s�N�Z���V�F�[�_�̃t�B�[���h�ɓK�p����n���h��
	int m_graphH;
	/*�萔�o�b�t�@�̃n���h��*/
	int m_cbufferLightDirH;				// ���C�g�̌���
	int m_cbufferCameraTargetPosH;		// �J�����̃^�[�Q�b�g�̈ʒu
	int m_cbufferCameraPosH;			// �J�����̈ʒu

	/*�萔�o�b�t�@�������邽�߂̃A�h���X�̃R�s�[*/
	VECTOR* m_pCbufferLightDir;				// ���C�g�̌���
	VECTOR* m_pCbuffferCameraTargetPos;		// �J�����̃^�[�Q�b�g�̈ʒu
	VECTOR* m_pCbufferCameraPos;			// �J�����̈ʒu
};

