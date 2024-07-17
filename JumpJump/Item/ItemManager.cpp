#include "DxLib.h"
#include "ItemManager.h"
#include "ItemNotMove.h"

ItemManager::ItemManager(int itemNum):
	m_keyModelHandle(-1)
{
	// モデルのロード
	m_keyModelHandle = MV1LoadModel("Data/Model/Item/Key.mv1");

	m_pItem.resize(1);
	m_pItem[0] = std::make_shared<ItemNotMove>(m_keyModelHandle);
}

ItemManager::~ItemManager()
{
}

void ItemManager::CreateItem()
{
	m_pItem[0]->SetPos(VGet(10, 50, 10));
}

void ItemManager::DestroyItem()
{
	// モデルのデリート
	MV1DeleteModel(m_keyModelHandle);
}

void ItemManager::Init()
{
	for (auto& item : m_pItem)
	{
		if (item != nullptr)
		{
			item->Init();
		}
	}
}

void ItemManager::Update()
{
	for (auto& item : m_pItem)
	{
		if (item != nullptr)
		{
			item->Update();
		}
	}
}

void ItemManager::Draw()
{
	for (auto& item : m_pItem)
	{
		if (item != nullptr)
		{
			item->Draw();
		}
	}
}