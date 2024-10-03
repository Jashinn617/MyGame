#pragma once
#include "DxLib.h"

#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

class ObjectBase;
class ObjectManager;

class SpownItem
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="fileName">csvファイル名</param>
	/// <param name="pObjectManager">オブジェクトマネージャー</param>
	SpownItem(const char* csvFileName, ObjectManager* pObjectManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SpownItem();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 出現
	/// </summary>
	void Spown();

	/// <summary>
	/// 存在しているかどうか
	/// </summary>
	/// <returns>存在フラグ</returns>
	bool IsExist();

	/// <summary>
	/// アイテム数の取得
	/// </summary>
	/// <returns>アイテム数</returns>
	int GetItemNum()const { return static_cast<int>(m_pData.size()); }

private:	// 構造体
	struct Data
	{
		ObjectBase* pItem = nullptr;	// オブジェクトベースポインタ
		int index = 0;					// アイテム番号
		std::string kind{};				// 種類
	};

private:	// 関数

	/// <summary>
	/// アイテムの生成
	/// </summary>
	void Create();

	/// <summary>
	/// アイテムの出現
	/// </summary>
	void Appearance();

	/// <summary>
	/// アイテムの追加
	/// </summary>
	/// <param name="createNum">アイテム番号</param>
	/// <param name="itenKind">アイテムの種類</param>
	/// <param name="pos">初期座標</param>
	void Add(int createNum, std::string itemKind, VECTOR pos);

	/// <summary>
	/// 特定の文字が検出されるまで文字をプッシュバックする
	/// </summary>
	/// <param name="input"></param>
	/// <param name="delimiter"></param>
	/// <returns></returns>
	std::vector<std::string> Split(std::string& input, char delimiter);

private:
	int m_createNum;					// 出現番号
	const char* m_fileName;				// ファイル名
	std::list<Data*> m_pData;			// アイテム情報
	std::string m_line;					// ファイル内の文字列
	ObjectManager* m_pObjectManager;	// オブジェクトマネージャーポインタ
};

