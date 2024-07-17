#pragma once
#include "SceneBase.h"
class SceneTutorial : public SceneBase
{
public:
	SceneTutorial();
	virtual ~SceneTutorial();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
};

