#pragma once
#include <memory>

using namespace std;

class SceneBase;
class Input;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void Init();
	void Update(Input& input);
	void Draw();
	void End();

private:
	shared_ptr<SceneBase> m_pScene;
};

