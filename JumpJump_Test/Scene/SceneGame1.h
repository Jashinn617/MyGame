#pragma once
#include "SceneBase.h"
class SceneGame1 : public SceneBase
{
public:
	SceneGame1();
	virtual ~SceneGame1();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
};

