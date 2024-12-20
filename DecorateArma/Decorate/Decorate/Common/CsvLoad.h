﻿#pragma once

#include "../Object/CharacterBase.h"

#include "../Object/Player/Gear.h"

#include "../Utility/CharacterData.h"

using namespace CharacterData;

/// <summary>
/// CSVファイルデータを読み込むクラス
/// </summary>
class CsvLoad
{
public:	// 関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CsvLoad();

	/// <summary>
	/// 実態の取得
	/// </summary>
	/// <returns>実態</returns>
	static CsvLoad& GetInstance();

	/// <summary>
	/// アニメーション情報ロード
	/// </summary>
	/// <param name="data">アニメデータ</param>
	/// <param name="characterName">キャラクター名</param>
	void AnimLoad(CharacterBase::AnimData& data, const char* characterName);

	/// <summary>
	/// ステータス情報ロード
	/// </summary>
	/// <param name="data">ステータスデータ</param>
	/// <param name="characterName">キャラクター名</param>
	void StatusLoad(CharacterBase::StatusData& data, const char* characterName);

	/// <summary>
	/// 追加するステータス値
	/// </summary>
	/// <param name="data">ステータスデータ</param>
	/// <param name="characterName">キャラクター名</param>
	void AddStatusLoad(CharacterBase::StatusData& data, const char* characterName);

	/// <summary>
	/// 装備品のロード
	/// </summary>
	/// <param name="data">装備品データ</param>
	/// <param name="gearName">装備品名</param>
	void GearDataLoad(std::vector<Gear::GearData>& data);

	/// <summary>
	/// 装備中装備品のロード
	/// </summary>
	/// <param name="data">装備品データ</param>
	/// <param name="gearName">装備品名</param>
	void GearEquippedDataLoad(std::vector<Gear::GearData>& data);

	/// <summary>
	/// 装備品
	/// </summary>
	/// <param name="data">装備品データ</param>
	/// <param name="stageName">ステージ名</param>
	void ItemDropProbabilityDataLoad(std::vector<int>& data, const char* stageName);

private:	// 関数
	/// <summary>
	/// コンストラクタ
	/// シングルトンパターン
	/// </summary>
	CsvLoad();

	/// <summary>
	/// コピーコンストラクタ
	/// コピーを禁止する
	/// </summary>
	/// <param name="">実態</param>
	CsvLoad(const CsvLoad&) = delete;

	/// <summary>
	/// 代入を禁止する
	/// </summary>
	/// <param name="">実態</param>
	void operator=(const CsvLoad&) = delete;
};