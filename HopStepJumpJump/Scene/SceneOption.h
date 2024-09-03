#pragma once
#include "SceneBase.h"

class Input;
class ImageManaer;

class SceneOption : public SceneBase
{
public:
	SceneOption(std::shared_ptr<SceneBase> prevScene);
	virtual ~SceneOption();

	virtual void Init()override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	virtual SceneKind GetSceneKind() { return SceneKind::Option; }
};

