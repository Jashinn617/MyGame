#pragma once
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

	std::vector<std::shared_ptr<ItemBase>> m_pItem;
};

