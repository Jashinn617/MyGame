#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	int m_titleLogoHandle;
	int m_startLogoHandle;
	int m_endLogoHandle;
	int m_selectCursorHandle;
	int m_bgmHandle;

	double m_startExtRate;
	double m_endExtRate;

	float m_cursorSinCount;
	float m_cursorSinPosX;
	float m_cursorPosY;

	int m_cursorCount;


private: // �萔
	static constexpr float kTitlePosX = 800.0f;	// �^�C�g����X�ʒu
	static constexpr float kTitlePosY = 250.0f;	// �^�C�g����Y�ʒu
	static constexpr double kTitleExtRate = 0.5;	// �^�C�g���̊g�嗦

	static constexpr float kStartPosX = kTitlePosX;	// �X�^�[�g��X�ʒu
	static constexpr float kStartPosY = kTitlePosY + 300.0f;	// �X�^�[�g��Y�ʒu
	static constexpr double kSmallStartExtRate = 0.3;	// �X�^�[�g�̊g�嗦(�ʏ펞)
	static constexpr double kBigStartExtRate = 0.35;	// �X�^�[�g�̊g�嗦(�g�厞)

	static constexpr float kEndPosX = kTitlePosX;	// �G���h��X�ʒu
	static constexpr float kEndPosY = kStartPosY + 200.0f;	// �G���h��Y�ʒu
	static constexpr double kSmallEndExtRate = kSmallStartExtRate;	// �G���h�̊g�嗦(�ʏ펞)
	static constexpr double kBigEndExtRate = kBigStartExtRate;	// �G���h�̊g�嗦(�g�厞)

	static constexpr float kCursorPosX = kTitlePosX - 300.0f;	// �J�[�\����X�ʒu
	static constexpr double kCursorExtRate = 0.15;	// �J�[�\���̊g�嗦

	static constexpr float kCursorSinSpeed = 0.08f;	// �J�[�\���̈ړ��X�s�[�h
	static constexpr float kCursorAnimationSwing = 30.0f;	// �J�[�\���̈ړ���

};

