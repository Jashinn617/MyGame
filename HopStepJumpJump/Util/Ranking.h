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
	Ranking();
	~Ranking();
	void CreateRanking(Game::Stage stageKind);			  // ランキング作成
	void UpdateRanking(Game::Stage stageKind, int clearTime); // ランキング更新
	std::vector<int> GetRanking(Game::Stage stageKind);						  // ランキング取得

private:
	std::string HttpGet(const char* domain, const char* url); // Http通信でGet命令を送る

private:
	std::string uri;
	std::string createRank;
	std::string getRank;

	// ネットワーク用の変数
	static const int kDataSize = 2560;	// データサイズ
	char StrBuf[kDataSize] = "";		// データバッファ
	IPDATA Ip;							// 接続用ＩＰアドレスデータ
	int NetHandle;						// ネットワークハンドル
	int DataLength;						// 受信データ量保存用変数
	size_t m_pos;						// 文字の長さを取得する
	int m_lineCount;					// 表示する行数をカウントする
	std::vector<int> m_rankingList;		// クリアタイムを保存する


};

