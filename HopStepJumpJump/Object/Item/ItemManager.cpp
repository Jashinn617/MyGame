#include "ItemManager.h"
#include "ItemBase.h"
#include "SpownItem.h"
#include "CountGetItem.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

namespace
{
	// アイテムデータcsvファイルパス
	const char* const kCsvDataFile[static_cast<int>(Game::Stage::StageNum)] =
	{
		"Data/File/Item/TestItemSpown.csv",
		"Data/File/Item/Stage1ItemSpown.csv",
		"Data/File/Item/Stage2ItemSpown.csv",
		"Data/File/Item/TestItemSpown.csv"
	};
}

ItemManager::ItemManager(Game::Stage stageKind, ObjectManager* pObjectManager):
	m_isSpown(true),
	m_isClear(false),
	m_pObjectManager(pObjectManager)
{
	// ステージによって出現するアイテムを変える
	m_pSpown = std::make_shared<SpownItem>(kCsvDataFile[static_cast<int>(stageKind)], m_pObjectManager);

	// アイテムの取得数ポインタの設定
	m_pCountGetItem = std::make_shared<CountGetItem>(m_pSpown->GetItemNum());
}

ItemManager::~ItemManager()
{
	/*処理無し*/
}

void ItemManager::Init()
{
	// 出現
	m_pSpown->Spown();
}

void ItemManager::Update()
{
	/*処理無し*/
}

void ItemManager::Draw()
{
	// 描画
	m_pCountGetItem->Draw();
}

void ItemManager::AddGetNum()
{
	// 取得数の追加
	m_pCountGetItem->Add();

	// 全て取った場合
	if (m_pCountGetItem->IsCountMax())
	{
		// クリア
		m_isClear = true;
	}
}
