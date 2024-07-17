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

private:	// •Ï”
	int m_keyModelHandle;	// ƒJƒM‚Ì3Dƒ‚ƒfƒ‹

	std::vector<std::shared_ptr<ItemBase>> m_pItem;
};

