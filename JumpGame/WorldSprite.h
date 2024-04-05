#pragma once
#include "DxLib.h"

/// <summary>
/// 3D���W��ԂɃX�v���C�g��\������d�g��(�s�{�b�g�͒��S�Œ�A�摜��graph�͊O�ŊǗ�)
/// </summary>
class WorldSprite
{
public:

	WorldSprite();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="textureGraph">�e�N�X�`���̉摜�n���h��</param>
	/// <param name="chipPixelSize">�X�v���C�g��1�`�b�v�̃s�N�Z���T�C�Y</param>
	/// <param name="spriteNo">�X�v���C�g�ԍ�</param>
	void Init(int textureGraph, int chipPixelSize, int spriteNo);
	/// <summary>
	/// �T�C�Y�ƃ|�W�V�����ɉ�����4���_���̒��_�ʒu�𒲐�
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
	/// <param name="spriteSize">�z�u���郏�[���h�X�v���C�g�̃T�C�Y</param>
	void SetTransform(const VECTOR& pos, float spriteSize);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	const VECTOR& GetPos()const { return m_pos; }

private:
	int m_textureGraph;		// �X�v���C�g���쐬���錳�e�N�X�`���̃O���t�B�b�N�n���h��
	VECTOR m_pos;				// �`��|�W�V����
	VERTEX3D m_vertex[4];		// ���_�o�b�t�@
	WORD m_index[6];			// �C���f�b�N�X�o�b�t�@
};

