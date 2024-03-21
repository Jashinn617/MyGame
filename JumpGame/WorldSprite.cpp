#include "WorldSprite.h"

void WorldSprite::Init(int textureGraph, int chipPixelSize, int spriteNo)
{
	this->m_textureGraph = textureGraph;

	// ���������ɌŒ肵�Ă��邪�A�ύX��������Ύ����Ŋ֐���ǉ�����K�v������
	// 4���_����UV�f�[�^��ݒ肷��
	int texW, texH;
	GetGraphTextureSize(textureGraph, &texW, &texH);
	int chipNum = texW / chipPixelSize;
	int chipNoX = spriteNo % chipNum;
	int chipNoY = spriteNo / chipNum;
	float oneChipUVRate = 1.0f / static_cast<float>(chipNum);	// �e�N�X�`���S����1.0�Ƃ�������chip��ɑ΂���UV�̃T�C�Y
	m_vertex[0].u = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[0].v = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[1].u = (chipNoX + 1.0f) * oneChipUVRate;
	m_vertex[1].v = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[2].u = (chipNoX + 0.0f) * oneChipUVRate;
	m_vertex[2].v = (chipNoX + 1.0f) * oneChipUVRate;
	m_vertex[3].u = (chipNoX + 1.0f) * oneChipUVRate;
	m_vertex[3].v = (chipNoX + 1.0f) * oneChipUVRate;

	// �f�B�t���[�Y�A�X�؃L�����͏��������ɌŒ�
	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].dif = GetColorU8(255, 255, 255, 255);
		m_vertex[i].spc = GetColorU8(0, 0, 0, 0);
		m_vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);	//	��]���T�|�[�g���Ȃ��̂Ńm�[�}�����Œ�

		// �⏕�e�N�X�`�����T�|�[�g���Ȃ��̂�UV�Œ�
		m_vertex[i].sv = 0.0f;
		m_vertex[i].sv = 0.0f;
	}

	// 2�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
	m_index[0] = 0;
	m_index[1] = 1;
	m_index[2] = 2;
	m_index[3] = 3;
	m_index[4] = 2;
	m_index[5] = 1;
}

void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
	this->m_pos = pos;
	// �s�{�b�g���S�Őݒ�
	m_vertex[0].pos = VScale(VGet(-1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	m_vertex[0].pos = VScale(VGet(1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	m_vertex[0].pos = VScale(VGet(-1.0f, -1.0f, 0.0f), spriteSize * 0.5f);
	m_vertex[0].pos = VScale(VGet(1.0f, -1.0f, 0.0f), spriteSize * 0.5f);

	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].pos = VAdd(m_vertex[i].pos, pos);
	}
}

void WorldSprite::Draw()
{
	// 2�|���S���̕`��
	DrawPolygonIndexed3D(m_vertex, 4, m_index, 2, m_textureGraph, false);
}
