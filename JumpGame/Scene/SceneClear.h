#pragma once
#include "SceneBase.h"

class SceneClear : public SceneBase
{
public:
	SceneClear();
	~SceneClear();
	/// <summary>
	/// ������
	/// </summary>
	virtual void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <returns>���݂̃V�[��</returns>
	virtual shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// �V�[���I�����̏���
	/// </summary>
	virtual void End();

private:	// �֐�
	/// <summary>
	/// �J�[�\���̈ړ�
	/// </summary>
	/// <param name="input">����</param>
	void CursorMove(Input& input);


private:	// �ϐ�
	int m_clearLogoHandle;			// �N���A�̉摜
	int m_continueLogoHandle;		// �R���e�j���[�̉摜
	int m_endLogoHandle;			// �Q�[���I���̉摜
	int m_selectCursorHandle;		// �I��p�̃J�[�\���̉摜
	int m_bgmHandle;				// BGM
	int m_cursorMoveSeHandle;		// �J�[�\�����ړ������ۂ�SE
	int m_continueSeHandle;			// �R���e�j���[����SE
	int m_endSeHandle;				// �Q�[���I������SE

	double m_continueExtRate;		// �R���e�j���[�̉摜�̊g�嗦
	double m_endExtRate;			// �Q�[���I���̉摜�̊g�嗦

	float m_cursorSinCount;			// �J�[�\���𓮂����ۂ̃J�E���g
	float m_cursorSinPosX;			// �J�[�\���̈ʒu�v�Z�Ɏg��Sin
	float m_cursorPosY;				// �J�[�\����Y�ʒu

	int m_cursorCount;				//	�J�[�\���̕\���ʒu�p�̃J�E���g

	int m_fadeAlpha;				// �t�F�[�h�C���A�A�E�g

	bool m_isSceneEnd;				// �V�[�����I���������ǂ���

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

