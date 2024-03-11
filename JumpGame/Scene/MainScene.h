#pragma once
#include "SceneBase.h"

class Player;
class MainScene:public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:

	/*ƒ|ƒCƒ“ƒ^‚ÌŽæ“¾*/
	shared_ptr<Player> m_pPlayer;
};

