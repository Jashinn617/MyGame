#pragma once
#include "SceneBase.h"

class SkyDome;
class Camera;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

	virtual SceneKind GetSceneKind() { return SceneKind::Title; }

	std::shared_ptr<SkyDome> m_pSky;
	std::shared_ptr<Camera> m_pCamera;
};

