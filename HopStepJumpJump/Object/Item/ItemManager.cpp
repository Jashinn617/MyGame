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
	// �X�|�[���t�@�C����
	const char* const kSpownFile[static_cast<int>(Game::Stage::StageNum)] =
	{
		"Data/File/Item/TestItemSpown.csv",
		"Data/File/Item/Stage1ItemSpown.csv",
		"Data/File/Item/Stage2ItemSpown.csv",
		"Data/File/Item/TestItemSpown.csv"
	};
}

ItemManager::ItemManager(Game::Stage stage, ObjectManager* pObjectManager):
	m_isSpown(true),
	m_isClear(false),
	m_pObjectManager(pObjectManager)
{
	// ���x���ɂ���ďo������A�C�e����ς���
	m_pSpown = std::make_shared<SpownItem>(kSpownFile[static_cast<int>(stage)], m_pObjectManager);

	// �`���[�g���A�����͌ォ��A�C�e�����o��
	if (stage == Game::Stage::Tutorial)
	{
		m_isSpown = false;
	}

	m_pCountGetItem = std::make_shared<CountGetItem>(m_pSpown->GetItemNum());
}

ItemManager::~ItemManager()
{
	/*��������*/
}

void ItemManager::Init()
{
	m_pSpown->Spown();
}

void ItemManager::Update()
{
	/*��������*/
}

void ItemManager::Draw()
{
	m_pCountGetItem->Draw();
}

void ItemManager::AddGetNum()
{
	// �擾���̒ǉ�
	m_pCountGetItem->Add();

	// �S�Ď�����ꍇ
	if (m_pCountGetItem->IsCountMax())
	{
		// �N���A
		m_isClear = true;
	}

}
