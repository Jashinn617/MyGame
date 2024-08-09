#pragma once
#include "SceneBase.h"
class SceneRanking : public SceneBase
{
public:
	SceneRanking();
	virtual ~SceneRanking();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
	virtual SceneKind GetSceneKind() { return SceneKind::Ranking; }
};

