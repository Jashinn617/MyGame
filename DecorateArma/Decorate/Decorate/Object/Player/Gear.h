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
	GearData GetGear(std::string gearName);

private: // 変数

	std::vector<GearData> m_data;	// 装備品情報
	 
};

