#pragma once
#include "DxLib.h"

#include <memory>

class DamageShader
{
public:
	DamageShader();
	virtual ~DamageShader();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	void DrawFirst(int shaderType);

	void UseShader();

	void DrawEnd();

	bool GetUseShader()const { return m_isUseShader; }

private:
	int m_vertexShader4FrameH;		// ���_�V�F�[�_4�t���[���̃n���h��	
	int m_vertexShader8FrameH;		// ���_�V�F�[�_8�t���[���̃n���h��
	int m_pixelShaderH;				// �s�N�Z���V�F�[�_�̃n���h��
	int m_graphH;					// �摜�n���h��

	/*�萔�o�b�t�@�̃n���h��*/
	int m_cbufferTimeH;					// �^�C��
	int m_cbufferLightDirH;				// ���C�g�̌���
	int m_cbufferCameraTargetPosH;		// �J�����̃^�[�Q�b�g�̈ʒu
	int m_cbufferCameraPosH;			// �J�����̈ʒu

	/*�萔�o�b�t�@�������邽�߂̃A�h���X�̃R�s�[*/
	float* m_cbufferTime;					// �^�C��
	VECTOR* m_pCbufferLightDir;				// ���C�g�̌���
	VECTOR* m_pCbuffferCameraTargetPos;		// �J�����̃^�[�Q�b�g�̈ʒu
	VECTOR* m_pCbufferCameraPos;			// �J�����̈ʒu

	float m_colDensity;		// �F�̔Z��

	bool m_isUseShader;		// �V�F�[�_���g�����ǂ���
};

