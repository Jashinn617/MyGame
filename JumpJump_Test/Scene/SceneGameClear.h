#pragma once
#include "DxLib.h"
#include "SceneBase.h"

#include <memory>

class Input;
class StageSceneManager;
class Time;
class Result;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager);
	~SceneGameClear();

	virtual void Init() override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	// シーンの種類の取得
	virtual SceneKind GetSceneKind() { return SceneKind::GameClear; }


private:	// 関数
	void ChangeMainScene();
	void ChangeTitleScene();
private:	// 変数
	int m_graphH;		// 画像ハンドル
	bool m_isSceneEnd;	// シーンが終了したかどうか
	bool m_isNextScene;	// 次のシーンに移動可能かどうか

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;
	std::shared_ptr<Time> m_pImageDrawTime;
	std::shared_ptr<Result> m_pResult;
};

