#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class StageTest;

using namespace std;

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
	virtual shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="handle">ハンドル</param>
	virtual void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End();

private:

	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
	shared_ptr<StageTest> m_pStage;


private:

	void DrawGrid();
};