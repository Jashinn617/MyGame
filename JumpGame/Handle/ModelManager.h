#pragma once
class ModelManager
{
public:
	ModelManager();
	virtual ~ModelManager();

	void CreateModel();
	void DestroyModel();

	int GetPlayerHandle() { return playerHandle; }

private:
	int playerHandle;
};

