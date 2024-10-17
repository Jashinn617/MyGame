#include "CsvLoad.h"

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// <summary>
/// 区切り文字が検出されるまで文字をプッシュバックする
/// </summary>
/// <param name="input">抜き出す文字</param>
/// <param name="delimiter">区切り文字</param>
/// <returns>検出されるまでの文字列</returns>
std::vector<std::string> Split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

CsvLoad::CsvLoad()
{
	/*処理無し*/
}

CsvLoad::~CsvLoad()
{
	/*処理無し*/
}

CsvLoad& CsvLoad::GetInstance()
{
	// 唯一の実態
	static CsvLoad instance;

	return instance;
}

void CsvLoad::AnimLoad(CharacterBase::AnimData& data, const char* charcterName)
{
	// ファイル情報の読み込み
	std::ifstream ifs("Data/CsvFile/AnimNum.csv");
	std::string line;

	std::array<int8_t, 7> animData{};

	std::vector<std::string> strvec;

	while (getline(ifs, line))
	{
		// csvデータ１行を、','で複数の文字列に分割
		strvec = Split(line, ',');

		// strvec[0]	: キャラ名	string
		// strvec[1]	: 待機モーション
		// strvec[2]	: 歩きモーション
		// strvec[3]	: 走りモーション
		// strvec[4]	: ジャンプ時モーション
		// strvec[5]	: ジャンプ中モーション
		// strvec[6]	: ダメージモーション

		//参照したいキャラが見つかっていたら処理をやめる
		const char* str = strvec[0].c_str();
		if (strcmp(str, charcterName) == 0)
		{
			for (int i = 0; i < animData.size(); i++)
			{
				//キャラクター名情報はいらないので省く
				if (i == 0)continue;
				int animNum = stoi(strvec[i]);
				animData[i] = static_cast<int8_t>(animNum);
			}
			break;
		}
		else
		{
			strvec.erase(strvec.begin(), strvec.end());
		}
	}

	//外部ファイルから持ってきたステータス情報をステータスデータに入れる
	data.idle = animData[1];
	data.walk = animData[2];
	data.run = animData[3];
	data.jumpStart = animData[4];
	data.jumpIdle = animData[5];
	data.damage = animData[6];
}

