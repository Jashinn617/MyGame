#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class StageTest;
class EnemyManager;

/// <summary>
/// メインシーンクラス
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="handle">ハンドル</param>
	virtual void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="handle">ハンドル</param>
	/// <returns>シーンポインタ</returns>
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="handle">ハンドル</param>
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
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<StageTest> m_pStage;
	std::shared_ptr<EnemyManager> m_pEnemy;

	int m_back;


};