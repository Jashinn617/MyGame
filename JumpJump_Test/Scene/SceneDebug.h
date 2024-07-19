#pragma once
#include "SceneBase.h"
class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:	// •Ï”

	int m_count;

};

