#include "SpownItem.h"

#include "ItemBase.h"
#include "ItemStop.h"
#include "ItemRotate.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"

#include <assert.h>

namespace
{
	constexpr float kHeightPos = 30.0f;	// ��������
	constexpr int kFirstCreateNum = 1;	// �ŏ��̏o���ԍ�
}

SpownItem::SpownItem(const char* fileName, ObjectManager* pObjectManager) :
	m_createNum(kFirstCreateNum),
	m_fileName(fileName),
	m_pObjectManager(pObjectManager)
{
	// �A�C�e���̐���
	Create();
}

SpownItem::~SpownItem()
{
	std::list<Data*>::iterator it = m_pData.begin();
	while (it != m_pData.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pData.erase(it);
	}
}

void SpownItem::Init()
{
	/*��������*/
}

void SpownItem::Spown()
{
	Appearance();
}

bool SpownItem::IsExist()
{
	// �A�C�e���̃f�[�^���Ȃ������ꍇ
	if (m_pData.size() == 0) return false;

	// �A�C�e���̑S�f�[�^�𒲂ׂ�
	for (auto& data : m_pData)
	{
		// �A�C�e�������݂��Ă����ꍇ
		if (data->pItem->GetInfo().isExist)
		{
			return true;
		}
	}

	return false;
}

void SpownItem::Create()
{
	// �t�@�C����
	std::ifstream ifs(m_fileName);

	while (getline(ifs, m_line))
	{
		// csv�f�[�^��1�s��','�ŕ����̕�����ɕ�������
		std::vector<std::string> strvec = Split(m_line, ',');

		// strvec[0]	: �o���ԍ�			int
		// strvec[1]	: �A�C�e���̎��	string
		// strvec[2]	: �A�C�e����X���W	float
		// strvec[3]	: �A�C�e����Y���W	float
		// strvec[4]	: �A�C�e����Z���W	float

		// �ǂݎ�����f�[�^�����W�ɕϊ�����
		VECTOR pos = VGet(stof(strvec[2]), stof(strvec[3]), stof(strvec[4]));

		// ��������
		pos.y += kHeightPos;

		// �f�[�^�ɍ����G�̒ǉ�
		Add(stoi(strvec[0]), strvec[1], pos);
	}
}

void SpownItem::Appearance()
{
	for (auto& data : m_pData)
	{
		m_pObjectManager->AddObject(data->pItem);
		data->pItem->Init();
	}
}

void SpownItem::Add(int createNum, std::string itemName, VECTOR pos)
{
	// ���f���t�@�C����
	const char* const modelFile = "Data/Model/Item/Key.mv1";
	// ���f���n���h���̎擾
	int modelH = MV1LoadModel(modelFile);
	assert(modelH != -1);
	// itemName�ɍ����G�̒ǉ�
	if (itemName == "Stop")
	{
		m_pData.push_back(new Data);
		m_pData.back()->pItem = new ItemStop(pos);
	}
	else
	{
		return;
	}

	m_pData.back()->pItem->SetModelHandle(modelH);
	m_pData.back()->index = createNum;
	m_pData.back()->name = itemName;
}

std::vector<std::string> SpownItem::Split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string filed;
	std::vector<std::string> result;

	while (getline(stream, filed, delimiter))
	{
		result.push_back(filed);
	}

	return result;
}
