#include "Gear.h"

#include "../../Common/CsvLoad.h"

namespace
{
	int gearKindNum = 15;	// 装備品の種類の数
}

Gear::Gear()
{
	m_data.resize(gearKindNum);

	for (int i = 0; i < m_data.size(); i++)
	{
		// 装備品情報のロード
		CsvLoad::GetInstance().ItemDataLoad(m_data[i]);
	}
}

Gear::~Gear()
{
}

Gear::GearData Gear::GetGear(std::string gearName)
{
	return GearData();
}
