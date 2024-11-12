#pragma once

#include <string>
#include <vector>

/// <summary>
/// 装備品
/// </summary>
class Gear
{
public:	// 構造体
	/// <summary>
	/// 装備品情報
	/// </summary>
	struct GearData
	{
		std::string name;	// アイテム名
		int upHp;			// 体力の上昇値
		int upMAttack;		// 近接攻撃力の上昇値
		int upSAttack;		// 遠距離攻撃力の上昇値
		int upDef;			// 防御力の上昇値
		int cost;			// コスト
		int num;			// 所持数
		int number;			// UI画像パス
	};

public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Gear();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gear();

	/// <summary>
	/// 指定した装備品を取得する
	/// </summary>
	/// <param name="gearName">装備品名</param>
	/// <returns>指定の装備品</returns>
	GearData GetGearNum(std::string gearName);

	/// <summary>
	/// 指定した装備品を取得する
	/// </summary>
	/// <param name="gearNum">装備品番号</param>
	/// <returns>指定の装備品</returns>
	GearData GetGearNum(int gearNum);

	/// <summary>
	/// 指定した装備品の数を減らす
	/// </summary>
	/// <param name="gearNum">装備品番号</param>
	void DecreaseGear(int gearNum);

	/// <summary>
	/// 装備品アイテムの追加
	/// </summary>
	/// <param name="gearName">アイテム名</param>
	void AddEquippedGear(std::string gearName);

	/// <summary>
	/// CSVファイルに装備品のデータを書き込む
	/// </summary>
	void SaveGear();

	/// <summary>
	/// 装備中装備データの取得
	/// </summary>
	/// <returns>装備中装備データ</returns>
	std::vector<GearData> GetEquippedGear() { return m_equippedData; }

	/// <summary>
	/// 指定した装備中装備品を取得する
	/// </summary>
	/// <param name="gearNum">装備品番号</param>
	/// <returns>指定の装備品</returns>
	GearData GetEquippedNum(int gearNum) { return m_equippedData[gearNum]; }

private: // 変数
	std::vector<GearData> m_data;			// 装備品情報
	std::vector<GearData> m_equippedData;	// 装備中装備品情報
	 
};

