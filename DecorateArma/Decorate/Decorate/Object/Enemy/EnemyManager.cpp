#include "EnemyManager.h"

#include "EnemyBase.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"

#include <fstream>
#include <sstream>
#include <cassert>

namespace
{
	const char* const kCsvDataFile[static_cast<int>(Game::StageKind::StageNum)] =
	{
		"",
		""
	};
}

EnemyManager::EnemyManager(Game::StageKind stageKind, ObjectManager* pObjectManager):
	m_createNum(0),
	m_fileName(kCsvDataFile[static_cast<int>(stageKind)]),
	m_pObjectManager(pObjectManager)
{
	// 敵の生成
	CsvLoad();
}

EnemyManager::~EnemyManager()
{
	// 情報ポインタの解放
	std::list<Data*>::iterator it = m_pData.begin();
	while (it!=m_pData.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pData.erase(it);
	}
}

void EnemyManager::Init()
{
	// 出現
	Spawn();
}

void EnemyManager::Spawn()
{
	for (auto& data : m_pData)
	{
		// オブジェクトの追加
		m_pObjectManager->AddObject(data->pEnemy);
		// 初期化
		data->pEnemy->Init();
	}
}

void EnemyManager::CsvLoad()
{
	// ファイル名
	std::ifstream ifs(m_fileName);

	while (getline(ifs, m_line))
	{
		// csvデータの1行を','で複数の文字列の分割する
		std::vector<std::string> strvec = Split(m_line, ',');

		// strvec[0]		：出現番号		int
		// strvec[1]		：種類			string
		// strvec[2]		：X座標			float
		// strvec[3]		：Y座標			float
		// strvec[4]		：Z座標			float
		// strvec[5]		：移動速度		float

		/*読み取ったデータを変換する*/
		// 座標
		VECTOR pos = VGet(stof(strvec[2]), stof(strvec[3]), stof(strvec[4]));
		// 移動速度
		float speed = stof(strvec[5]);

		// 高さ調整

		// 追加
		Add(stoi(strvec[0]), strvec[1], pos, speed);
	}
}

void EnemyManager::Add(int createNum, std::string enemyKind, VECTOR pos, float moveSpeed)
{
	// モデルファイルパス
	std::string enemyModelFile = "Data/Model/Enemy/" + enemyKind + ".mv1";
	// モデルファイル名
	const char* const modelFile = enemyModelFile.c_str();
	// モデルハンドルの取得
	int modelH = MV1LoadModel(modelFile);
	// 取得に失敗したら止める
	assert(modelH != -1);

	// enemyKindと同じ種類の敵の追加
	if (enemyKind == "")
	{
		
	}
	else if (enemyKind == "")
	{

	}
	else
	{
		// 合う敵がいなかった場合は何もしない
		return;
	}

	// モデルハンドルの設定	
	m_pData.back()->pEnemy->SetModelHandle(modelH);
	// 敵番号の設定
	m_pData.back()->index = createNum;
	// 種類の設定
	m_pData.back()->kind = enemyKind;
}

std::vector<std::string> EnemyManager::Split(std::string& input, char delimiter)
{
	std::istringstream stream(input);	// 文字列ストリーム
	std::string filed;					// 一時格納用文字列
	std::vector<std::string> result;	// 分割結果

	// 文字列を区切り文字(コンマ)で分割する
	while (getline(stream, filed, delimiter))
	{
		// 分割した文字の追加
		result.push_back(filed);
	}

	return result;
}
