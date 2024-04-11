#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	int m_titleLogoHandle;
	int m_startLogoHandle;
	int m_endLogoHandle;
	int m_selectCursorHandle;

	double m_startExtRate;
	double m_endExtRate;

	int m_cursorPosY;

	int m_cursorCount;

private: // �萔
	static constexpr float kTitlePosX = 800.0f;	// �^�C�g����X�ʒu
	static constexpr float kTitlePosY = 250.0f;	// �^�C�g����Y�ʒu
	static constexpr double kTitleExtRate = 0.5;	// �^�C�g���̊g�嗦

	static constexpr float kStartPosX = 800.0f;	// �X�^�[�g��X�ʒu
	static constexpr float kStartPosY = kTitlePosY + 300.0f;	// �X�^�[�g��Y�ʒu
	static constexpr double kSmallStartExtRate = 0.3;	// �X�^�[�g�̊g�嗦(�ʏ펞)
	static constexpr double kBigStartExtRate = 0.5;	// �X�^�[�g�̊g�嗦(�g�厞)

	static constexpr float kEndPosX = 800.0f;	// �G���h��X�ʒu
	static constexpr float kEndPosY = kStartPosY + 200.0f;	// �G���h��Y�ʒu
	static constexpr double kSmallEndExtRate = 0.3;	// �G���h�̊g�嗦(�ʏ펞)
	static constexpr double kBigEndExtRate = 0.5;	// �G���h�̊g�嗦(�g�厞)

	static constexpr float kCursorPosX = 500.0f;	// �J�[�\����X�ʒu
	static constexpr double kCursorExtRate = 0.15;	// �J�[�\���̊g�嗦


};

