#pragma once
#include "SceneBase.h"

class SceneClear : public SceneBase
{
public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneClear();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SceneClear();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override final;

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
	virtual SceneKind GetSceneKind() override final { return SceneKind::Gear; }
};

