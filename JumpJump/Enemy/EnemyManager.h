#pragma once
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemyes();
	void DestroyEnemyes();

	void Update();
	void Draw();

private:

	void CollisionToPlayer();
};

