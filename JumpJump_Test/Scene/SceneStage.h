#pragma
#include "SceneBase.h"
#include "../Util/Game.h"

#include <list>

class StageSceneManager;
class ObjectBase;
class Player;
class Camera;
class EnemyBase;
class EnemyManager;
class Field;
class SkyDome;
class Collision;
class Input;


class SceneStage : public SceneBase
{
public:
	SceneStage(Game::Stage stage);
	virtual ~SceneStage();

	virtual void Init() override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	virtual SceneKind GetSceneKind() { return SceneKind::Stage; }

private:
	void GameClear();


	bool m_isSceneEnd;

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;
	std::shared_ptr<SceneBase> m_nextScene;
};

