#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	~SceneGameOver();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	
};

