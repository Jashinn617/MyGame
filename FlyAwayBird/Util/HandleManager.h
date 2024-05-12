#pragma once
#include <unordered_map>
#include <string>

using namespace std;

// <ハンドル名,ハンドル>
using HandleTable_t = unordered_map<string, int>;

/// <summary>
/// 各ハンドルの管理をするクラス
/// </summary>
class HandleManager
{
public:
	HandleManager();
	~HandleManager();

	int GetModel(const char* command)const;
	int GetImg(const char* command)const;
	int GetSound(const char* command)const;
	int GetFont(const char* command)const;

private:	// 関数
	void LoadModel();
	void LoadImg();
	void LoadSound();
	void LoadFont();

	void DeleteModel();
	void DeleteImg();
	void DeleteSound();
	void DeleteFont();

private:// 変数
	/*ハンドル名とハンドルをペアにしたテーブル*/
	HandleTable_t m_modelHandleTable;	// 3Dモデルのハンドル
	HandleTable_t m_imgHandleTable;		// 画像のハンドル
	HandleTable_t m_soundHandleTable;	// サウンドのハンドル

};

