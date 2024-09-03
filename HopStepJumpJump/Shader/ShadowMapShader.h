#pragma once
#include "DxLib.h"

class ShadowMapShader
{
public:
	ShadowMapShader();
	~ShadowMapShader();

	// �V���h�E�}�b�v�ւ̏������݂̊J�n
	void WriteStart(VECTOR targetPos);

	/// <summary>
	/// �V���h�E�}�b�v�̃J�������猩���^�[�Q�b�g��ݒ肷��
	/// </summary>
	/// <param name="targetPos"></param>
	void SetShadowMapCameraTarget(VECTOR targetPos);

	void SetShader(int shaderType);
	void SetShaderField(VECTOR targetPos);

	/// <summary>
	/// �V���h�E�}�b�v�ւ̏������݂��I���
	/// </summary>
	void WriteEnd();

private:	// �֐�
	/// <summary>
	/// �r���[�v���W�F�N�V�����s�����邽�߂̊֐�
	/// </summary>
	/// <param name="targetPos"></param>
	/// <returns></returns>
	MATRIX ViewProjectionMatrix(VECTOR targetPos);

private:	// �ϐ�
	/*���_�V�F�[�_*/
	int m_vertexShader1FrameH;				//���_�V�F�[�_�[1�t���[���n���h��
	int m_vertexShader4FrameH;				//���_�V�F�[�_�[4�t���[���n���h��
	int m_vertexShader8FrameH;				//���_�V�F�[�_�[8�t���[���n���h��
	int m_vertexShaderNormal4FrameH;		//���_�V�F�[�_�[4�t���[���@���}�b�v����n���h��
	int m_vertexShaderNormal8FrameH;		//���_�V�F�[�_�[8�t���[���@���}�b�v����n���h��
	/*�s�N�Z���V�F�[�_*/
	int m_vertexShaderShadowMapFieldH;		// ���_�V�F�[�_�̃V���h�E�}�b�v���t�B�[���h�ɓ\��t���邽�߂̒��_�V�F�[�_
	int m_pixelShaderH;						// �s�N�Z���V�F�[�_�̃n���h��
	int m_pixelShaderFieldH;				// �s�N�Z���V�F�[�_�̃t�B�[���h�ɓK�p����n���h��

	/*�萔�o�b�t�@�̃n���h��*/
	int m_cbufferLightDirH;				// ���C�g�̌���
	int m_cbufferCameraTargetPosH;		// �J�����̃^�[�Q�b�g�̈ʒu
	int m_cbufferCameraPosH;			// �J�����̈ʒu
	int m_cbufferViewProjectionMatH;	// �r���[�v���W�F�N�V�����s��

	/*�萔�o�b�t�@�������邽�߂̃A�h���X�̃R�s�[*/
	VECTOR* m_pCbufferLightDir;				// ���C�g�̌���
	VECTOR* m_pCbuffferCameraTargetPos;		// �J�����̃^�[�Q�b�g�̈ʒu
	VECTOR* m_pCbufferCameraPos;			// �J�����̈ʒu

	/// <summary>
	/// �r���[�v���W�F�N�V�����s��
	/// �V���h�E�}�b�v�e�N�X�`�����t�B�[���h���f����
	///	�\��t����ۂɍ��W�̕ϊ����s�����߂ɕK�v�ȍs��
	/// </summary>
	MATRIX* m_viewProjectionMat;
	int m_shadowMap;	// �V���h�E�}�b�v�p�̕ϐ�
};

