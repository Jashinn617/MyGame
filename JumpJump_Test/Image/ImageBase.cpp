#include "ImageBase.h"

ImageBase::ImageBase():
	m_H(-1),
	m_center{0,0},
	m_isDisplay(true)
{
	/*��������*/
}

ImageBase::~ImageBase()
{
	DeleteGraph(m_H);
}

void ImageBase::SetUp()
{
	/*��������*/
}

void ImageBase::SetUp(const char* fileName, Vec2 center)
{
	m_H = LoadGraph(fileName);
	m_center = center;
}
