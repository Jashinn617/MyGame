#pragma once
#include "ItemBase.h"

#include <memory>

class ItemStop : public ItemBase
{
public:
	ItemStop(VECTOR pos);
	~ItemStop();

	void Init()override final;

	//void Draw(std::shared_ptr<ToonShader> pToonShader)override final;

	void MoveDirectionUpdate() override final;

	VECTOR MoveUpdate() override final;

private:
	// �p�x�̍X�V
	virtual void AngleUpdate();

private:
	float m_angleX;		// X�p�x
	float m_moveSinCount;	// �ړ��J�E���g
};

