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

		int handle = -1;	// サウンドハンドル
	};
}

class CsvLoad
{
public:
	~CsvLoad();

	static CsvLoad& GetInstance();

	void AnimLoad(CharacterBase::AnimData& Data, const char* charcterName);

	void SoundLoad(std::unordered_map<std::string, LoadData::SoundData>& Data);

private:
	/// <summary>
	/// シングルトンパターン
	/// </summary>
	CsvLoad();

	// コピーを禁止する
	// コピーコンストラクタ
	CsvLoad(const CsvLoad&) = delete;
	// 代入を禁止する
	void operator=(const CsvLoad&) = delete;
};

