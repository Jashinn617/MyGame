#include "SpownEnemy.h"

#include "EnemyBase.h"
#include "EnemyBee.h"
#include "EnemySkull.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"

#include <assert.h>

namespace
{
	constexpr float kHeightPos = 10.0f;	// 高さ調整
}

SpownEnemy::SpownEnemy(const char* csvFileName, ObjectManager* pObjectManager):
	m_createNum(0),
	m_fileName(csvFileName),
	m_pObjectManager(pObjectManager)
{
	// アイテムの生成
	Create();
}

SpownEnemy::~SpownEnemy()
{
	// 敵情報ポインタの解放
	std::list<Data*>::iterator it = m_pData.begin();
	while (it != m_pData.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pData.erase(it);
	}
}

void SpownEnemy::Init()
{
	/*処理無し*/
}

void SpownEnemy::Spown()
{
	// 出現
	Appearance();
}

bool SpownEnemy::IsExist()
{
	// アイテムのデータがなかった場合
	if (m_pData.size() == 0) return false;

	// アイテムの全データを調べる
	for (auto& data : m_pData)
	{
		// アイテムが存在していた場合
		if (data->pEnemy->GetInfo().isExist)
		{
			// 存在フラグをtrueにする
			return true;
		}
	}

	// ここまで来ていたら存在しない
	return false;
}

void SpownEnemy::Create()
{
	// ファイル名
	std::ifstream ifs(m_fileName);

	while (getline(ifs, m_line))
	{
		// csvデータの1行を','で複数の文字列に分割する
		std::vector<std::string> strvec = Split(m_line, ',');

		// strvec[0]	: 出現番号				int
		// strvec[1]	: アイテムの種類		string
		// strvec[2]	: アイテムのX座標		float
		// strvec[3]	: アイテムのY座標		float
		// strvec[4]	: アイテムのZ座標		float
		// strvec[5]	: 移動方向ベクトルX		float
		// strvec[6]	: 移動方向ベクトルY		float
		// strvec[7]	: 移動方向ベクトルZ		float
		// strvec[8]	: 反転するまでの時間	int
		// strvec[9]	: 移動速度				float


		/*読み取ったデータを変換する*/
		// 座標
		VECTOR pos = VGet(stof(strvec[2]), stof(strvec[3]), stof(strvec[4]));
		// 移動方向
		VECTOR direction = VGet(stof(strvec[5]), stof(strvec[6]), stof(strvec[7]));
		// 反転までの時間
		int turnTime = static_cast<int>(stof(strvec[8]));
		// 移動速度
		float speed = stof(strvec[9]);

		// 高さ調整
		pos.y += kHeightPos;

		// 敵の追加
		Add(stoi(strvec[0]), strvec[1], pos, direction, turnTime, speed);
	}
}

void SpownEnemy::Appearance()
{
	for (auto& data : m_pData)
	{
		// オブジェクトの追加
		m_pObjectManager->AddObject(data->pEnemy);
		// 初期化
		data->pEnemy->Init();
	}
}

void SpownEnemy::Add(int createNum, std::string enemyKind, VECTOR pos, VECTOR direction, int turnTime, float speed)
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
	if (enemyKind == "Bee")		// ハチ
	{
		m_pData.push_back(new Data);
		m_pData.back()->pEnemy = new EnemyBee(pos, direction, turnTime, speed);
	}
	else if (enemyKind == "Skull")	// ガイコツ
	{
		m_pData.push_back(new Data);
		m_pData.back()->pEnemy = new EnemySkull(pos, speed);
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

std::vector<std::string> SpownEnemy::Split(std::string& input, char delimiter)
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
