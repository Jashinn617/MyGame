#pragma once
#include "DxLib.h"

#include <memory>

class Model;

class SkyDome
{
public:
	SkyDome();
	virtual ~SkyDome();

	void Update(VECTOR pos);
	void Draw();

private:
	float m_rot;	// ��]��
	std::shared_ptr<Model> m_pModel;	// ���f���|�C���^
};

