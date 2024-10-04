﻿#pragma once
#include "CharacterData.h"
#include "../Object/ObjectBase.h"
#include "../Object/CharacterBase.h"

#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace CharacterData;

namespace LoadData
{
	/// <summary>
	/// サウンドデータ
	/// </summary>
	struct SoundData
	{
		bool isBgm = false;		// BGMかSEか
		float volRate = 255;	// ボリューム調整
		int handle = -1;		// サウンドハンドル
	};

	/// <summary>
	/// エフェクトデータ
	/// </summary>
	struct EffectData
	{
		int resouceH = -1;			// エフェクトハンドル 
		int playingEffectH = -1;	// 実際にエフェクトを再セするときに使うハンドル
		float size = 0;				// エフェクトのサイズ
		float speed = 1;			// 再生スピード
	};
}

class CsvLoad
{
public:
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
	/// アニメーションのロード
	/// </summary>
	/// <param name="Data">アニメーション情報</param>
	/// <param name="charcterName">キャラクター名</param>
	void AnimLoad(CharacterBase::AnimData& Data, const char* charcterName);

	/// <summary>
	/// サウンドのロード
	/// </summary>
	/// <param name="Data">サウンド情報</param>
	void SoundLoad(std::unordered_map<std::string, LoadData::SoundData>& Data);

	/// <summary>
	/// エフェクトのロード
	/// </summary>
	/// <param name="Data">エフェクトデータ</param>
	void EffectLoad(std::unordered_map<std::string, LoadData::EffectData>& Data);

private:
	/// <summary>
	/// コンストラクタ
	/// シングルトンパターン
	/// </summary>
	CsvLoad();

	// コピーを禁止する
	// コピーコンストラクタ
	CsvLoad(const CsvLoad&) = delete;
	// 代入を禁止する
	void operator=(const CsvLoad&) = delete;
};

