#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>

class ItemBase;

class ItemManager
{
public:
	ItemManager(int itemNum);
	~ItemManager();

	void CreateItem();
	void DestroyItem();

	void Init();
	void Update();
	void Draw();

private:	// �ϐ�
	int m_keyModelHandle;	// �J�M��3D���f��

	std::vector<VECTOR> m_pos;
	std::vector<float> m_angleSpeed;
	std::vector<float> m_radius;

	std::vector<std::shared_ptr<ItemBase>> m_pItem;
};

