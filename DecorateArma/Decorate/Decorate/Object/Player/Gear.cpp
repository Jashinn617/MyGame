#include "Gear.h"

#include "../../Common/CsvLoad.h"

#include <iostream>
#include <fstream>
#include <cassert>

namespace
{
	constexpr int kMaxCost = 30;		// 最大コスト数
	constexpr int kGearKindNum = 15;	// 装備品の種類の数

	// 装備品名
	const char* kGearName[kGearKindNum] =
	{
		"HPUpS",
		"HpUpM",
		"HpUpL",
		"MATKUpS",
		"MATKUpM",
		"MATKUpL",
		"SATKUpS",
		"SATKUpM",
		"SATKUpL",
		"DEFUpS",
		"DEFUpM",
		"DEFUpL",
		"AllUpS",
		"AllUpM",
		"AllUpL",
	};

	
	const char* kCsvFileName = "Data/CsvFile/Gear.csv";					// 保存するファイル名(装備前装備品)
	const char* kEquippedCsvFileName = "Data/CsvFile/EquippedGear.csv";	// 保存するファイル名(装備後装備品)

}

Gear::Gear()
{
	m_data.resize(kGearKindNum);

	for (int i = 0; i < m_data.size(); i++)
	{
		// 装備品情報のロード
		CsvLoad::GetInstance().GearDataLoad(m_data[i], kGearName[i]);
	}

	for (int i = 0; i < m_equippedData.size(); i++)
	{
		// 装備品情報のロード
		CsvLoad::GetInstance().GearEquippedDataLoad(m_equippedData[i], kGearName[i]);
	}
}

Gear::~Gear()
{
}

Gear::GearData Gear::GetGearNum(std::string gearName)
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

Gear::GearData Gear::GetGearNum(int gearNum)
{
	//for (int i = 0; i < m_data.size(); i++)
	//{
	//	// 指定の装備品を見つけたらそれを返す
	//	if (i == gearNum)
	//	{
	//		return m_data[i];
	//	}
	//}

	return m_data[gearNum];

	// 指定した装備品がなければ止める
	assert(false);
}

void Gear::DecreaseGear(int gearNum)
{
	m_data[gearNum].num--;
}

void Gear::AddEquippedGear(std::string gearName)
{
	// 指定の装備品を探す
	for (int i = 0; i < m_data.size(); i++)
	{
		// 指定の装備品を見つけたら装備品にそれを入れる
		if (m_data[i].name == gearName)
		{
			m_equippedData.push_back(m_data[i]);
		}
	}
}

void Gear::SaveGear()
{
	/*装備品ファイル*/
	// ファイルを上書きモードで開く
	std::ofstream csvFile(kCsvFileName);
	// ファイルが無かったらエラーメッセージを出す
	if (!csvFile)
	{
		std::cerr << "ファイルを開けませんでした：" << kCsvFileName << std::endl;
	}
	// 一行目に数値の種類を書き込む
	csvFile << "アイテム名,HP上昇値,MATK上昇値,SATK上昇値,DEF上昇値,コスト,所持数\n";
	// 二行目以降にデータを書き込む
	for (const auto& data : m_data)
	{
		csvFile << data.name << ","
			<< data.upHp << ","
			<< data.upMAttack << ","
			<< data.upSAttack << ","
			<< data.upDef << ","
			<< data.cost << ","
			<< data.num << ","
			<< data.path << "\n";
	}
	// ファイルを閉じる
	csvFile.close();

	/*装備中装備品ファイル*/
	// ファイルを上書きモードで開く
	std::ofstream csvEquippedFile(kEquippedCsvFileName);
	// ファイルが無かったらエラーメッセージを出す
	if (!csvEquippedFile)
	{
		std::cerr << "ファイルを開けませんでした：" << kEquippedCsvFileName << std::endl;
	}
	// 一行目に数値の種類を書き込む
	csvEquippedFile << "アイテム名,HP上昇値,MATK上昇値,SATK上昇値,DEF上昇値,コスト,所持数\n";
	// 二行目以降にデータを書き込む
	for (const auto& data : m_equippedData)
	{
		csvEquippedFile << data.name << ","
			<< data.upHp << ","
			<< data.upMAttack << ","
			<< data.upSAttack << ","
			<< data.upDef << ","
			<< data.cost << ","
			<< data.num << ","
			<< data.path << "\n";
	}
	// ファイルを閉じる
	csvEquippedFile.close();
}
