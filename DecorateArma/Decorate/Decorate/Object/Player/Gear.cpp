#include "Gear.h"

#include "../../Common/CsvLoad.h"

#include <iostream>
#include <fstream>
#include <cassert>

#include <random>
#include <Windows.h>

namespace
{
	const char* kCsvFileName = "Data/CsvFile/Gear.csv";					// 保存するファイル名(装備前装備品)
	const char* kEquippedCsvFileName = "Data/CsvFile/EquippedGear.csv";	// 保存するファイル名(装備後装備品)

	constexpr int kItemDropProbability = 50;	// アイテムを手に入れる確率
	constexpr int kMaxProbability = 100;		// 確率最大値
}

Gear::Gear():
	m_nowDropProbability(0),
	m_prevDropProbability(0)
{
	// 装備品情報のロード
	CsvLoad::GetInstance().GearDataLoad(m_data);
	// 装備品情報のロード
	CsvLoad::GetInstance().GearEquippedDataLoad(m_equippedData);
	// ドロップ確率のロード
	CsvLoad::GetInstance().ItemDropProbabilityDataLoad(m_probability, "Test");
}

Gear::~Gear()
{
}

void Gear::Draw()
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
			return;
		}
	}
}

void Gear::RemoveGear(int gearNum)
{
	// 装備前装備品のデータを一つ増やす
	// 外す装備品と同じ装備品を探す
	for (int i = 0; i < m_data.size(); i++)
	{
		// 指定の装備品を見つけたら装備品数を増やして
		// 装備中の装備品を消す
		if (m_data[i].name == m_equippedData[gearNum].name)
		{
			m_data[i].num++;
			m_equippedData.erase(m_equippedData.begin() + gearNum);

			// 見つけたら終わる
			return;
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
	csvFile << "アイテム名,HP上昇値,MATK上昇値,SATK上昇値,DEF上昇値,コスト,所持数,装備番号\n";
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
			<< data.number << "\n";
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
	csvEquippedFile << "アイテム名,HP上昇値,MATK上昇値,SATK上昇値,DEF上昇値,コスト,所持数,装備番号\n";
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
			<< data.number << "\n";
	}
	// ファイルを閉じる
	csvEquippedFile.close();
}

int Gear::GetAddHp()
{
	int ans = 0;

	for (auto& data : m_equippedData)
	{
		// 全てのHPを足す
		ans += data.upHp;
	}

	return ans;
}

int Gear::GetAddMAtk()
{
	int ans = 0;

	for (auto& data : m_equippedData)
	{
		// 全ての近接攻撃力を足す
		ans += data.upMAttack;
	}

	return ans;
}

int Gear::GetAddSAtk()
{
	int ans = 0;

	for (auto& data : m_equippedData)
	{
		// 全ての遠距離攻撃力を足す
		ans += data.upSAttack;
	}

	return ans;
}

int Gear::GetAddDef()
{
	int ans = 0;

	for (auto& data : m_equippedData)
	{
		// 全ての防御力を足す
		ans += data.upDef;
	}

	return ans;
}

void Gear::ObtainItemOnStage()
{
	// アイテムを落としたかどうかを調べる
	std::random_device rd;
	std::mt19937 mt(rd());
	// 範囲
	std::uniform_real_distribution<float> urd(0, kMaxProbability);
	float probability = urd(mt);
	// 出た数が確率より大きかったら何もせずに返る
	if (probability > kItemDropProbability) return;

	// 確率を出す
	int rand = urd(mt);
	// 確率初期化
	m_prevDropProbability = -1;
	m_nowDropProbability = m_probability[0];

	for (int i = 0; i <= m_probability.size(); i++)
	{
		/*その確率の範囲内にいるかどうかを調べる*/
		if (m_prevDropProbability < rand >= m_nowDropProbability)
		{
			// 範囲内に入っていたら所持アイテムに加えて処理を返す
			m_dorpData.push_back(m_data[i]);

			// 画面右上に何を手に入れたかを描画するようにする

			return;
		}
		// 違う場合は次の範囲を設定する
		m_prevDropProbability = m_nowDropProbability;
		m_nowDropProbability += m_probability[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) + 1];
	}
}