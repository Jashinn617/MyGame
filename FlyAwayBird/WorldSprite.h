#pragma once

/// <summary>
/// 2D�摜��3D��Ԃɕ\������N���X
/// </summary>
class WorldSprite
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="textureGraph">�摜�̃n���h��</param>
	/// <param name="chipPixelSizeW">�摜�̉��T�C�Y</param>
	/// <param name="chipPixelSizeH">�摜�̏c�T�C�Y</param>
	/// <param name="spriteNo">�}�b�v�`�b�v���A�؂���ꍇ�̔ԍ�(�؂���Ȃ��ꍇ�̓f�t�H���g��0�̂܂܂ŗǂ�)</param>
	void Initialize(int textureGraph, int chipPixelSizeW, int chipPixelSizeH, int spriteNo = 0);
	
	/// <summary>
	/// �T�C�Y�ƈʒu�ɉ�����4���_���̒��_�̈ʒu�𒲐�����
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="spriteSize">�T�C�Y</param>
	void SetTransform(const VECTOR& pos, float spriteSize);
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns></returns>
	const VECTOR& GetPos()const { return m_pos; }

private:
	int			m_textureHandle;	// �X�v���C�g���쐬���錳�e�N�X�`���̃O���t�B�b�N�n���h��
	VECTOR		m_pos;			// �`��ʒu
	VERTEX3D	m_vertex[4];		// ���_�o�b�t�@
	WORD		m_index[6];		// �C���f�b�N�X�o�b�t�@
};

