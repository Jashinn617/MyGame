#pragma once
#include "SceneBase.h"

class SceneClear : public SceneBase
{
public:
	SceneClear();
	~SceneClear();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	int m_clearLogoHandle;
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

	int m_fadeAlpha;	// �t�F�[�h�C���A�A�E�g

	bool m_isSceneEnd;	// �V�[�����I���������ǂ���

private:	// �萔
	static constexpr float kClearPosX = 800.0f;	// �N���A��X�ʒu
	static constexpr float kClearPosY = 200.0f;	// �N���A��Y�ʒu
	static constexpr double kClearExtRate = 0.8;	// �N���A�̊g�嗦

	static constexpr float kContinuePosX = kClearPosX;	// �R���e�j���[��X�ʒu
	static constexpr float kContinuePosY = kClearPosY + 300.0f;	// �R���e�j���[��X�ʒu
	static constexpr double kSmallContinueExtRate = 0.5f;	// �R���e�j���[�̊g�嗦(�ʏ펞)
	static constexpr double kBigContinueExtRate = 0.55f;	// �R���e�j���[�̊g�嗦(�g�厞)

	static constexpr float kEndPosX = kClearPosX;	// �G���h��X�ʒu
	static constexpr float kEndPosY = kContinuePosY + 200.0f;	// �G���h��Y�ʒu
	static constexpr double kSmallEndExtRate = kSmallContinueExtRate;	// �G���h�̊g�嗦(�ʏ펞)
	static constexpr double kBigEndExtRate = kBigContinueExtRate;	// �G���h�̊g�嗦(�g�厞)

	static constexpr float kCursorPosX = kClearPosX - 450.0f;	// �J�[�\����X�ʒu
	static constexpr double kCursorExtRate = 0.15;	// �J�[�\���̊g�嗦

	static constexpr float kCursorSinSpeed = 0.08f;	// �J�[�\���̈ړ��X�s�[�h
	static constexpr float kCursorAnimationSwing = 30.0f;	// �J�[�\���̈ړ���

	static constexpr int kBgmVolume = 130;	// BGM�̉���
	static constexpr int kSeVolume = 255;	// SE�̉���

	static constexpr int kScreenWidth = 1600;	// ��ʂ̉��T�C�Y
	static constexpr int kScreenHeight = 900;	// ��ʂ̏c�T�C�Y

	static constexpr int kFadeSpeed = 3;	// �t�F�[�h�̃X�s�[�h
};

