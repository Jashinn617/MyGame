#include "ItemNotMove.h"

ItemNotMove::ItemNotMove(int modelHandle):
	ItemBase(modelHandle)
{
}

ItemNotMove::~ItemNotMove()
{
}

void ItemNotMove::Init()
{
	MV1SetPosition(m_modelHandle, m_pos);
}

void ItemNotMove::Update()
{
}
