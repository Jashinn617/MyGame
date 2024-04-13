#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	~SceneGameOver();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	int m_gameOverLogoHandle;
	int m_continueLogoHandle;
	int m_endLogoHandle;
	int m_selectCursorHandle;
	int m_bgmHandle;
	int m_cursorMoveSeHandle;
	int m_startSeHandle;
	int m_endSeHandle;

	double m_continueExtRate;
	double m_endExtRate;

	float m_cursorSinCount;
	float m_cursorSinPosX;
	int m_cursorPosY;

	int m_cursorCount;

private:	// �萔
	static constexpr float kGameOverPosX = 800.0f;	// �Q�[���I�[�o�[���S��X�ʒu
	static constexpr float kGameOverPosY = 250.0f;	// �Q�[���I�[�o�[���S��Y�ʒu
	static constexpr double kGameOverExtRate = 0.8;	// �Q�[���I�[�o�[���S�̊g�嗦

	static constexpr float kContinuePosX = kGameOverPosX;	// �R���e�j���[��X�ʒu
	static constexpr float kContinuePosY = kGameOverPosY + 250.0f;	// �R���e�j���[��X�ʒu
	static constexpr double kSmallContinueExtRate = 0.5f;	// �R���e�j���[�̊g�嗦(�ʏ펞)
	static constexpr double kBigContinueExtRate = 0.55f;	// �R���e�j���[�̊g�嗦(�g�厞)

	static constexpr float kEndPosX = kGameOverPosX;	// �G���h��X�ʒu
	static constexpr float kEndPosY = kContinuePosY + 200.0f;	// �G���h��Y�ʒu
	static constexpr double kSmallEndExtRate = kSmallContinueExtRate;	// �G���h�̊g�嗦(�ʏ펞)
	static constexpr double kBigEndExtRate = kBigContinueExtRate;	// �G���h�̊g�嗦(�g�厞)

	static constexpr float kCursorPosX = kGameOverPosX - 450.0f;	// �J�[�\����X�ʒu
	static constexpr double kCursorExtRate = 0.15;	// �J�[�\���̊g�嗦

	static constexpr float kCursorSinSpeed = 0.08f;	// �J�[�\���̈ړ��X�s�[�h
	static constexpr float kCursorAnimationSwing = 30.0f;	// �J�[�\���̈ړ���

	static constexpr int kBgmVolume = 130;	// BGM�̉���
	static constexpr int kSeVolume = 255;	// SE�̉���
};

