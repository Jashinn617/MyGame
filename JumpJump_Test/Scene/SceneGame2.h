#pragma once
#include "SceneBase.h"
class SceneGame2 : public SceneBase
{
public:
	SceneGame2();
	virtual ~SceneGame2();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
};