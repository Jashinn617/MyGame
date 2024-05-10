#pragma once
#include "../Util/Input.h"
#include "../Util/HandleManager.h"
#include "../Util/Game.h"
#include <memory>
#include <math.h>

using namespace std;

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase :public enable_shared_from_this<SceneBase>
{
public:
	SceneBase() {}
	virtual ~SceneBase() {};

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	/// <returns>現在のシーン</returns>
	virtual shared_ptr<SceneBase> Update(Input& input, HandleManager& handle) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(HandleManager& handle) = 0;
	/// <summary>
	/// シーン終了時の処理
	/// </summary>
	virtual void End() = 0;
};
