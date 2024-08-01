#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class StageTest;
class EnemyManager;
class ItemManager;

/// <summary>
/// メインシーンクラス
/// </summary>
class SceneTest : public SceneBase
{
public:
	SceneTest();
	virtual ~SceneTest();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End();

private:	// 関数

	/// <summary>
	/// デバッグ表示用
	/// </summary>
	void DrawGrid();

private:	// メンバ関数ポインタ
	
private:	// 変数
	
};