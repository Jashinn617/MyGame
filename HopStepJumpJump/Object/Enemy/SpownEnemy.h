#pragma once
#include "DxLib.h"

#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

class ObjectBase;
class ObjectManager;

class SpownEnemy
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="fileName">csvファイル名</param>
	/// <param name="pObjectManager">オブジェクトマネージャー</param>
	SpownEnemy(const char* csvFileName, ObjectManager* pObjectManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SpownEnemy();

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
	/// エネミー数の取得
	/// </summary>
	/// <returns>エネミー数</returns>
	int GetEnemyNum()const { return static_cast<int>(m_pData.size()); }

private:	// 構造体
	struct Data
	{
		ObjectBase* pEnemy = nullptr;	// オブジェクトベースポインタ
		int index = 0;					// エネミー番号
		std::string kind{};				// 種類
	};

private:	// 関数
	/// <summary>
	/// 敵の生成
	/// </summary>
	void Create();

	/// <summary>
	/// 敵の出現
	/// </summary>
	void Appearance();

	/// <summary>
	/// 敵の追加
	/// </summary>
	/// <param name="createNum">敵番号</param>
	/// <param name="enemyKind">敵の種類</param>
	/// <param name="pos">初期座標</param>
	/// <param name="direction">初期移動方向</param>
	/// <param name="turnTime">反転までの時間</param>
	/// <param name="speed">移動速度</param>
	void Add(int createNum, std::string enemyKind, VECTOR pos, VECTOR direction, int turnTime, float speed);

	/// <summary>
	/// 特定の文字が検出されるまで文字をプッシュバックする
	/// </summary>
	/// <param name="input">特定の文字</param>
	/// <param name="delimiter">区切り文字(コンマ)</param>
	/// <returns>検出された文字</returns>
	std::vector<std::string> Split(std::string& input, char delimiter);

private:	// 変数
	int m_createNum;					// 出現番号
	const char* m_fileName;				// ファイル名
	std::list<Data*> m_pData;			// 敵情報
	std::string m_line;					// ファイル内の文字列
	ObjectManager* m_pObjectManager;	// オブジェクトマネージャーポインタ
};

