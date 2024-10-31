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

void CsvLoad::AnimLoad(CharacterBase::AnimData& data, const char* characterName)
{
	// ファイル情報の読み込み
	std::ifstream ifs("Data/CsvFile/AnimNum.csv");
	std::string line;

	std::array<int8_t, 12> animData{};

	std::vector<std::string> strvec;

	while (getline(ifs, line))
	{
		// csvデータ１行を、','で複数の文字列に分割
		strvec = Split(line, ',');

		// strvec[0]	: キャラ名	string
		// strvec[1]	: 待機
		// strvec[2]	: 歩き
		// strvec[3]	: 走り
		// strvec[4]    : 攻撃1
		// strvec[5]    : 攻撃2
		// strvec[6]    : 攻撃3
		// strvec[7]    : 強攻撃
		// strvec[8]    : ダメージ
		// strvec[9]    : 死亡
		// strvec[10]	: ジャンプ時
		// strvec[11]	: ジャンプ中

		//参照したいキャラが見つかっていたら処理をやめる
		const char* str = strvec[0].c_str();
		if (strcmp(str, characterName) == 0)
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
	/*data.idle = animData[1];
	data.walk = animData[2];
	data.run = animData[3];
	data.jumpStart = animData[4];
	data.jumpIdle = animData[5];
	data.damage = animData[6];*/

	data.idle = animData[1];
	data.walk = animData[2];
	data.run = animData[3];
	data.attack1 = animData[4];
	data.attack2 = animData[5];
	data.attack3 = animData[6];
	data.hardAttack = animData[7];
	data.damage = animData[8];
	data.death = animData[9];
	data.jumpStart = animData[10];
	data.jumpIdle = animData[11];
}

void CsvLoad::StatusLoad(CharacterBase::StatusData& data, const char* characterName)
{
	// ファイル情報の読み込み
	std::ifstream ifs("Data/CsvFile/Status.csv");
	std::string line;

	std::array<int, 6> statusData{};

	std::vector<std::string>strvec;

	while (getline(ifs, line))
	{
		// csvデータ１行を、','で複数の文字列に分割
		strvec = Split(line, ',');

		// strvec[0]	: キャラ名	string
		// strvec[1]	: HP		int
		// strvec[2]	: MATK		int
		// strvec[3]	: SATK		int
		// strvec[4]	: DEF		int
		// strvec[5]	: SPD		float

		//参照したいキャラが見つかっていたら処理をやめる
		const char* str = strvec[0].c_str();
		if (strcmp(str, characterName) == 0) break;

		else
		{
			strvec.erase(strvec.begin(), strvec.end());
		}
	}

	// ステータス情報をステータスデータに入れる
	data.hp = stoi(strvec[1]);
	data.meleeAtk = stoi(strvec[2]);
	data.shotAtk = stoi(strvec[3]);
	data.def = stoi(strvec[4]);
	data.spd = stof(strvec[5]);
}