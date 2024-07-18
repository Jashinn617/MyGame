#include "ItemManager.h"
#include "ItemBase.h"
#include "ItemNotMove.h"
#include "ItemRotationMove.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>


ItemManager::ItemManager(int itemNum):
	m_keyModelHandle(-1)
{
	// モデルのロード
	m_keyModelHandle = MV1LoadModel("Data/Model/Item/Key.mv1");
	assert(m_keyModelHandle != -1);

	// アイテムのポインタの設定
	m_pItem.resize(itemNum);
	for (int i = 0; i < m_pItem.size(); i++)
	{
		if (i <= 1)
		{
			m_pItem[i] = std::make_shared<ItemNotMove>(m_keyModelHandle);
		}
		else
		{
			m_pItem[i] = std::make_shared<ItemRotationMove>(m_keyModelHandle);
		}		
	}
}

ItemManager::~ItemManager()
{
	/*処理無し*/
}

void ItemManager::CreateItem()
{
	// ファイルの読み込み
	std::ifstream file;
	file.open("Data/File/Item/ItemTest.csv");
	assert(file.is_open());

	// 読み取り元
	std::string path;
	while (std::getline(file,path))
	{
		std::istringstream istream(path);
		std::string line;
		VECTOR pos = VGet(0.0f, 0.0f, 0.0f);
		float angleSpeed = 0.0f;
		float radius = 0.0f;

		if (std::getline(istream, line, ',') &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.x) &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.y) &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.z) &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &angleSpeed) &&
			std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &radius))
		{
			// 位置をm_posに入れる
			m_pos.push_back(pos);
			// 回転速度を入れる
			m_angleSpeed.push_back(angleSpeed);
			// 円を描く半径を決める
			m_radius.push_back(radius);
		}
	}
	file.close();

	// 変数の代入
	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i]->SetPos(m_pos[i]);
		m_pItem[i]->SetAngleSpeed(m_angleSpeed[i]);
		m_pItem[i]->SetRadius(m_radius[i]);
	}
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