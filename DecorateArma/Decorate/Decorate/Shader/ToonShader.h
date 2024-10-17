#pragma once

#include "DxLib.h"

/// <summary>
/// �g�D�[���V�F�[�_��ݒ肷��N���X
/// </summary>
class ToonShader
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ToonShader();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ToonShader();

	/// <summary>
	/// �V�F�[�_�̐ݒ�
	/// </summary>
	/// <param name="vertexH">���_�V�F�[�_�n���h��</param>
	void SetShader(int vertexH);

	/// <summary>
	/// �t�B�[���h�V�F�[�_�̐ݒ�
	/// </summary>
	/// <param name="vertexH">���_�V�F�[�_�n���h��</param>
	void SetShaderField(int vertexH);

	/// <summary>
	/// �V�F�[�_���g��Ȃ��ݒ肷��
	/// </summary>
	void ShaderEnd();

private:
	/*�s�N�Z���V�F�[�_*/
	int m_pixelShaderH;				// �s�N�Z���V�F�[�_�̃n���h��
	int m_pixelShaderFieldH;		// �s�N�Z���V�F�[�_�̃t�B�[���h�ɓK�p����n���h��

	/*�萔�o�b�t�@�̃n���h��*/
	int m_cbufferLightDirH;				// ���C�g�̌���
	int m_cbufferCameraTargetPosH;		// �J�����̃^�[�Q�b�g�̈ʒu
	int m_cbufferCameraPosH;			// �J�����̈ʒu

	/*�萔�o�b�t�@�������邽�߂̃A�h���X�̃R�s�[*/
	VECTOR* m_pCbufferLightDir;				// ���C�g�̌���
	VECTOR* m_pCbuffferCameraTargetPos;		// �J�����̃^�[�Q�b�g�̈ʒu
	VECTOR* m_pCbufferCameraPos;			// �J�����̈ʒu
};