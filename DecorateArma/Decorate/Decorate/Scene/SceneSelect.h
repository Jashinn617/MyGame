#pragma once
#include "SceneBase.h"

#include <vector>

/// <summary>
/// セレクト画面
/// </summary>
class SceneSelect : public SceneBase
{
public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneSelect();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init()override final;

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>次のシーン</returns>
	virtual std::shared_ptr<SceneBase> Update() override final;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() override final;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() override final;

	/// <summary>
	/// シーン種類の取得
	/// </summary>
	/// <returns>シーンの種類</returns>
	virtual SceneKind GetSceneKind() override final { return SceneKind::Select; }

private:	// 関数
	/// <summary>
	/// 背景描画
	/// </summary>
	void BackDraw();

private:	// 変数
	std::vector<int> m_backH;		// 背景画像ハンドル
};

