#include "Image.h"

Image::Image()
{
	/*��������*/
}

Image::~Image()
{
	// �摜�̃f���[�g
	DeleteGraph(m_H);
}

void Image::Update()
{
	/*��������*/
}

void Image::Draw()
{
	// �摜�̕\��
	DrawRotaGraphF(m_center.x, m_center.y, 1.0f, 0.0f, m_H, true);
}
