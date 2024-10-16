#pragma once

/// <summary>
/// ���_�V�F�[�_�̃��[�h���s���N���X
/// </summary>
class VertexShader
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	VertexShader();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~VertexShader();
	
	/// <summary>
	/// ���_�V�F�[�_�n���h����ݒ肷��
	/// </summary>
	/// <param name="vertexShaderType">���_�^�C�v</param>
	/// <returns>���_�V�F�[�_�n���h��</returns>
	int SetVertexShaderH(int vertexShaderType);

private:	// �ϐ�
	/*���_�V�F�[�_*/
	int m_vertexShader1FrameH;				//���_�V�F�[�_�[1�t���[���n���h��
	int m_vertexShader4FrameH;				//���_�V�F�[�_�[4�t���[���n���h��
	int m_vertexShader8FrameH;				//���_�V�F�[�_�[8�t���[���n���h��
	int m_vertexShaderNormal4FrameH;		//���_�V�F�[�_�[4�t���[���@���}�b�v����n���h��
	int m_vertexShaderNormal8FrameH;		//���_�V�F�[�_�[8�t���[���@���}�b�v����n���h��
};