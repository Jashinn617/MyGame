#pragma once
#include <memory>

using namespace std;

class SceneBase;
class Input;

/// <summary>
/// シーン遷移等、各シーンを管理するためのクラス
/// </summary>
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	/// <summary>
	///  初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	void Update(Input& input);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ゲーム終了時の処理
	/// </summary>
	void End();

private:	// 変数
	shared_ptr<SceneBase> m_pScene;			// 描画するシーンのポインタ
};
