#include "Gear.h"

#include "../../Common/CsvLoad.h"

#include <cassert>

namespace
{
	int kMaxCost = 30;		// 最大コスト数
	int kGearKindNum = 15;	// 装備品の種類の数
}

Gear::Gear()
{
	m_data.resize(kGearKindNum);

	for (int i = 0; i < m_data.size(); i++)
	{
		// 装備品情報のロード
		CsvLoad::GetInstance().GearDataLoad(m_data[i]);
	}
}

Gear::~Gear()
{
}

Gear::GearData Gear::GetGear(std::string gearName)
{
	for (int i = 0; i < m_data.size(); i++)
	{
		// 指定の装備品を見つけたらそれを返す
		if (m_data[i].name == gearName)
		{
			return m_data[i];
		}
	}

	// 指定した装備品がなければ止める
	assert(false);
}