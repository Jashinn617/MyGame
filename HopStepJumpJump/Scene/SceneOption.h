#pragma once
#include "SceneBase.h"

class Input;
class ImageManaer;

class SceneOption : public SceneBase
{
public:
	SceneOption(std::shared_ptr<SceneBase> prevScene);
	virtual ~SceneOption();

	virtual void Init()override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	virtual SceneKind GetSceneKind() { return SceneKind::Option; }

private:
	bool m_isSceneEnd;

	// �O�̃V�[��
	std::shared_ptr<SceneBase> m_pPrevScene;

	// ���̃V�[���|�C���^
	std::shared_ptr<SceneBase> m_pNextScene;
};

