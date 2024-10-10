#pragma once
#include "../Utility/Game.h"

#include <memory>

/// <summary>
/// 各ステージを管理するクラス
/// </summary>
class StageManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stageKind">ステージの種類</param>
	StageManager(Game::StageKind stageKind);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~StageManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void  Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};