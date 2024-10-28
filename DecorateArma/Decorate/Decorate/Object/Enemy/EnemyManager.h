#pragma once
#include "../../Utility/Game.h"
#include "DxLib.h"

#include <string>
#include <vector>
#include <list>

class ObjectManager;
class ObjectBase;

class EnemyManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	/// <param name="pObjectManager">オブジェクトマネージャー</param>
	EnemyManager(Game::StageKind stageKind, ObjectManager* pObjectManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 敵の発生
	/// </summary>
	void Spawn();

private:	// 構造体
	/// <summary>
	/// 情報
	/// </summary>
	struct Data
	{
		ObjectBase* pEnemy = nullptr;	// オブジェクトベースポインタ
		int index = 0;					// 番号
		std::string kind{};				// 種類
	};

private:	// 関数
	/// <summary>
	/// Csvファイルのロード
	/// </summary>
	void CsvLoad();
	
	/// <summary>
	/// 敵の追加
	/// </summary>
	/// <param name="createNum">番号</param>
	/// <param name="enemyKind">種類</param>
	/// <param name="pos">座標</param>
	/// <param name="speed">移動速度</param>
	void Add(int createNum, std::string enemyKind, VECTOR pos, float moveSpeed);

	/// <summary>
	/// 特定の文字が検出されるまで文字をプッシュバックする
	/// </summary>
	/// <param name="input">特定の文字</param>
	/// <param name="delimiter">区切り文字(コンマ)</param>
	/// <returns>検出された文字列</returns>
	std::vector<std::string> Split(std::string& input, char delimiter);

private:
	int m_createNum;					// 出現番号
	const char* m_fileName;				// ファイル名
	std::list<Data*> m_pData;			// 情報
	std::string m_line;					// ファイル内の文字列
	ObjectManager* m_pObjectManager;	// オブジェクトマネージャーポインタ
};

