#include "SpownItem.h"

#include "ItemBase.h"
#include "ItemStop.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"

#include <assert.h>

namespace
{
	constexpr float kHeightPos = 30.0f;	// 高さ調整
}

SpownItem::SpownItem(const char* csvFileName, ObjectManager* pObjectManager) :
	m_createNum(0),
	m_fileName(csvFileName),
	m_pObjectManager(pObjectManager)
{
	// アイテムの生成
	Create();
}

SpownItem::~SpownItem()
{
	// アイテム情報ポインタの解放
	std::list<Data*>::iterator it = m_pData.begin();
	while (it != m_pData.end())
	{
		auto obj = (*it);

		delete obj;
		obj = nullptr;
		it = m_pData.erase(it);
	}
}

void SpownItem::Init()
{
	/*処理無し*/
}

void SpownItem::Spown()
{
	// 出現
	Appearance();
}

bool SpownItem::IsExist()
{
	// アイテムのデータがなかった場合
	if (m_pData.size() == 0) return false;

	// アイテムの全データを調べる
	for (auto& data : m_pData)
	{
		// アイテムが存在していた場合
		if (data->pItem->GetInfo().isExist)
		{
			// 存在フラグをtrueにする
			return true;
		}
	}

	// ここまで来ていたら存在しない
	return false;
}

void SpownItem::Create()
{
	// ファイル名
	std::ifstream ifs(m_fileName);

	while (getline(ifs, m_line))
	{
		// csvデータの1行を','で複数の文字列に分割する
		std::vector<std::string> strvec = Split(m_line, ',');

		// strvec[0]	: 出現番号			int
		// strvec[1]	: アイテムの種類	string
		// strvec[2]	: アイテムのX座標	float
		// strvec[3]	: アイテムのY座標	float
		// strvec[4]	: アイテムのZ座標	float

		// 読み取ったデータを座標に変換する
		VECTOR pos = VGet(stof(strvec[2]), stof(strvec[3]), stof(strvec[4]));

		// 高さ調整
		pos.y += kHeightPos;

		// アイテムの追加
		Add(stoi(strvec[0]), strvec[1], pos);
	}
}

void SpownItem::Appearance()
{
	for (auto& data : m_pData)
	{
		// オブジェクトの追加
		m_pObjectManager->AddObject(data->pItem);
		// 初期化
		data->pItem->Init();
	}
}

void SpownItem::Add(int createNum, std::string itemKind, VECTOR pos)
{
	// モデルファイルパス
	const char* const modelFile = "Data/Model/Item/Key.mv1";
	// モデルハンドルの取得
	int modelH = MV1LoadModel(modelFile);
	// 取得に失敗したら止める
	assert(modelH != -1);

	// itemKindと同じ種類のアイテムの追加
	if (itemKind == "Stop")		// 動かないアイテム
	{
		m_pData.push_back(new Data);
		m_pData.back()->pItem = new ItemStop(pos);
	}
	else
	{
		// 合うアイテムが無かった場合は何もしない
		return;
	}

	// モデルハンドルの設定
	m_pData.back()->pItem->SetModelHandle(modelH);
	// アイテム番号の設定
	m_pData.back()->index = createNum;
	// 種類の設定
	m_pData.back()->kind = itemKind;
}

std::vector<std::string> SpownItem::Split(std::string& input, char delimiter)
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
