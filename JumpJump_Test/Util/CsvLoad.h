#pragma once
#include "CharacterData.h"
#include "../Object/ObjectBase.h"
#include "../Object/CharacterBase.h"

#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace CharacterData;

namespace LoadData
{
	// サウンドデータ
	struct SoundData
	{
		// 固定データ
		bool isBgm = false;		// BGMかSEか
		float volRate = 255;	// ボリューム調整
	};
}

class CsvLoad
{
public:
	~CsvLoad();

	static CsvLoad& GetInstance();

	void AnimLoad(CharacterBase::AnimData& Data, const char* charcterName);

private:
	/// <summary>
	/// シングルトンパターン
	/// </summary>
	CsvLoad();

	/// <summary>
	/// コピーコンストラクタ
	/// </summary>
	/// <param name=""></param>
	CsvLoad(const CsvLoad&) = delete;
	// 代入も禁止する
	void operator=(const CsvLoad&) = delete;
};

