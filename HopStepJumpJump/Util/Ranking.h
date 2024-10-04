#pragma once
#include "Game.h"
#include <string>
#include <vector>

/// <summary>
/// ランキング情報を更新する
/// </summary>
class Ranking
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ranking();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ranking();

	/// <summary>
	/// ランキングの作成
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	void CreateRanking(Game::StageKind stageKind);

	/// <summary>
	/// ランキングの更新
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	/// <param name="clearTime">クリアタイム</param>
	void UpdateRanking(Game::StageKind stageKind, int clearTime);

	/// <summary>
	/// ランキングの取得
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	/// <returns>ランキング</returns>
	std::vector<int> GetRanking(Game::StageKind stageKind);

private:
	/// <summary>
	/// Http通信でGet命令を送る
	/// </summary>
	/// <param name="domain">ドメイン名</param>
	/// <param name="url">URI名</param>
	/// <returns>データバッファ</returns>
	std::string HttpGet(const char* domain, const char* url);

private:	// 定数
	static const int kDataSize = 2560;	// データサイズ

private:	// 変数
	int m_netH;						// ネットワークハンドル
	int m_dataLength;						// 受信データ量保存用変数
	int m_lineCount;					// 表示する行数をカウントする
	char m_strBuf[kDataSize] = "";		// データバッファ

	std::vector<int> m_rankingList;		// クリアタイムを保存する
	std::string uri;
	std::string createRank;
	std::string getRank;

	IPDATA m_ip;							// 接続用ＩＰアドレスデータ
	size_t m_pos;						// 文字の長さを取得する


};

