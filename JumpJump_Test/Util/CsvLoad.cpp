#include "CsvLoad.h"
#include "EffekseerForDXLib.h"

#include <vector>
#include<array>
#include <string>
#include<cassert>

//特定の文字が検出されるまで文字をプッシュバックする
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
	static CsvLoad instance;

	return instance;
}

void CsvLoad::AnimLoad(CharacterBase::AnimData& Data, const char* charcterName)
{
	// ファイル情報の読み込み
	std::ifstream ifs("Data/File/AnimNum.csv");
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
		// strvec[3]	: ジャンプ時モーション
		// strvec[4]	: ジャンプ中モーション
		// strvec[5]	: 走りモーション
		// strvec[6]	: ノックバックモーション

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
	Data.idle = animData[1];
	Data.walk = animData[2];
	Data.jumpStart = animData[3];
	Data.jumpIdle = animData[4];
	Data.run = animData[5];
	Data.knockBack = animData[6];
}