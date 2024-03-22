#pragma once
#include <vector>
#include <memory>

using namespace std;

class WorldSprite;

/// <summary>
/// 2Dの背景マップ
/// </summary>
class Map
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Map();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Map();

	/// <summary>
	/// マップのロード
	/// </summary>
	void Load();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/*マップチップのサイズ*/
	static const float m_chipSize;
	static const int m_chipPixelSize;
	static const int m_stageDataColNum = 16;	// マップの行
	static const int m_stageDataRowNum = 20;	// マップの列


private:
	// マップチップの配置データ
	static const int m_stageData[m_stageDataColNum][m_stageDataRowNum];

	// WorldSpriteのポインタ
	vector<shared_ptr<WorldSprite>> m_sprites;
	// マップチップのハンドル
	int m_chipHandle;
};

