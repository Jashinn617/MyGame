#pragma once
#include "DxLib.h"
#include "../Util/Vec2.h"

class ImageBase
{
public:

	ImageBase();
	virtual ~ImageBase();

	virtual void Update() abstract;
	virtual void Draw() abstract;

	virtual void SetUp();

	void SetUp(const char* fileName, Vec2 center);

protected:
	int m_H;			// �����n���h��
	Vec2 m_center;		// ���S
	bool m_isDisplay;	// �摜��\�������邩�ǂ���
};

