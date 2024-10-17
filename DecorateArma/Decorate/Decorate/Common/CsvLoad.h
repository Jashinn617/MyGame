#pragma once

#include "../Object/CharacterBase.h"

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

	void AnimLoad(CharacterBase::AnimData& data, const char* charcterName);

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