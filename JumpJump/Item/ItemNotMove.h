#pragma once
#include "ItemBase.h"
class ItemNotMove : public ItemBase
{
public:
	ItemNotMove(int modelHandle);
	virtual ~ItemNotMove();

	virtual void Init();
	virtual void Update();

private:
};

