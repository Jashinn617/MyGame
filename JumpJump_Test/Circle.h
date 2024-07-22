#pragma once
#include "DxLib.h"

#include <math.h>
#include <memory>

class Circle
{
public:
	Circle(const VECTOR& center, float radius, float height);

	virtual ~Circle();

	// �f�o�b�O�\��
	void DebugDraw();

	// �Փ˔���
	bool IsCollide(const std::shared_ptr<Circle> that)const;

	const VECTOR& GetCenter() const { return *m_center; }

	float GetRadius()const { return m_radius; }

private:
	const VECTOR* m_center;	// ���S���W
	const float m_radius;	// ���a
	const float m_height;	// ����	
};

