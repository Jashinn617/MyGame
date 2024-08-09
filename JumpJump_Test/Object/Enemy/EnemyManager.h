#pragma once
#include "../../Util/Game.h"

#include <vector>
#include <memory>
#include <array>

class Time;
class ObjectBase;
class EnemyBase;
class Player;
class ObjectManager;

class EnemyManager
{
public:
	EnemyManager(Game::Stage stage, std::shared_ptr<ObjectManager> pObjectManager);
	~EnemyManager();

	void Init();
	void Update();
	void Draw();

	void SetObjectManager(std::shared_ptr<ObjectManager> pObjectManager) { m_pObjectManager = pObjectManager; }


private:
	std::array<int, 11> m_modelH;

	std::shared_ptr<ObjectManager> m_pObjectManager;	
};
