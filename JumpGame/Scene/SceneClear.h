#pragma once
#include "SceneBase.h"

class SceneClear : public SceneBase
{
public:
	SceneClear();
	~SceneClear();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	int m_clearLogoHandle;
	int m_continueLogoHandle;
	int m_endLogoHandle;

private:	// �萔
	static constexpr float kClearPosX = 800.0f;	// �N���A���S��X�ʒu
	static constexpr float kClearPosY = 300.0f;	// �N���A���S��Y�ʒu
	static constexpr double kClearExtRate = 0.8;	// �N���A���S�̊g�嗦
};

