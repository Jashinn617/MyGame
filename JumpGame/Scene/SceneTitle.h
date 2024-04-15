#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

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
	int m_titleLogoHandle;			// �^�C�g�����S�̉摜
	int m_startLogoHandle;			// �X�^�[�g�̉摜
	int m_endLogoHandle;			// �Q�[���I���̉摜
	int m_selectCursorHandle;		// �I��p�̃J�[�\���̉摜
	int m_bgHandle;					// �w�i�̉摜
	int m_bgmHandle;				// BGM
	int m_cursorMoveSeHandle;		// �J�[�\�����ړ������ۂ�SE
	int m_startSeHandle;			// �X�^�[�g����SE

	double m_startExtRate;			// �X�^�[�g�̉摜�̊g�嗦
	double m_endExtRate;			// �Q�[���I���̉摜�̊g�嗦

	float m_cursorSinCount;			// �J�[�\���𓮂����ۂ̃J�E���g
	float m_cursorSinPosX;			// �J�[�\���̈ʒu�v�Z�Ɏg��Sin
	float m_cursorPosY;				// �J�[�\����Y�ʒu

	int m_cursorCount;				// �J�[�\���̕\���ʒu�p�̃J�E���g

	int m_fadeAlpha;				// �t�F�[�h�C���A�A�E�g

	bool m_isSceneEnd;				// �V�[�����I���������ǂ���

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


	static constexpr int kBgmVolume = 130;	// BGM�̉���
	static constexpr int kSeVolume = 255;	// SE�̉���

	static constexpr int kScreenWidth = 1600;	// ��ʂ̉��T�C�Y
	static constexpr int kScreenHeight = 900;	// ��ʂ̏c�T�C�Y

	static constexpr int kFadeSpeed = 3;	// �t�F�[�h�̃X�s�[�h
};

