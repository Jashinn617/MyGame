#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "StageSceneManager.h"
#include "SceneStage.h"

#include "../Util/Game.h"
#include "../Util/Pad.h"
#include "../Util/SoundManager.h"

#include "../Object/SkyDome.h"
#include "../Object/Camera.h"

#include <assert.h>

namespace
{
	/*�摜�t�@�C���p�X*/
	const char* const kTitleLogoImg = "Data/Img/Title/Logo.png";				// �^�C�g�����S
	const char* const kPressAnyButtonImg = "Data/Img/Title/PressAnyButton.png";	// �e�L�X�g
	const char* const kMovieFileName = "Data/Movie/DemoMovie.mp4";				// ����t�@�C���p�X

	/*�^�C�g�����S�摜�̏������W*/
	constexpr int kStartTitleLogoPosY = -1200;
	/*�^�C�g�����S�摜�̍��W*/
	constexpr int kTitleLogoPosX = static_cast<int>(Game::kScreenWidth * 0.5f);
	constexpr int kTitleLogoPosY = static_cast<int>(Game::kScreenHeight * 0.5f);
	/*�v���X�{�^���̉摜�̍��W*/
	constexpr int kPressAnyButtonPosX = static_cast<int>(Game::kScreenWidth * 0.5f);
	constexpr int kPressAnyButtonPosY = static_cast<int>(Game::kScreenHeight * 0.5f);

	constexpr int kTitleFallSpeed = 30;	// �^�C�g���������Ă��鑬�x
}

SceneTitle::SceneTitle():
	m_titleLogoH(LoadGraph(kTitleLogoImg)),
	m_textH(LoadGraph(kPressAnyButtonImg)),
	m_movieH(LoadGraph(kMovieFileName)),
	m_titlePosY(kStartTitleLogoPosY),
	m_isPlayFallSE(false)
{
	// �摜�̃��[�h�Ɏ��s���Ă�����~�܂�
	assert(m_titleLogoH != -1);
	assert(m_textH != -1);
	// ����̃��[�h�Ɏ��s���Ă�����~�܂�
	assert(m_movieH != -1);
}

SceneTitle::~SceneTitle()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_titleLogoH);
	DeleteGraph(m_textH);
	/*����̃f���[�g*/
	DeleteGraph(m_movieH);
}

void SceneTitle::Init()
{
	/*��������*/
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	// �t�F�[�h�̍X�V
	UpdateFade();

	// �^�C�g���𗎂Ƃ�
	m_titlePosY += kTitleFallSpeed;
	// �^�C�g���ʒu������̈ʒu��艺�ɍs���Ȃ��悤�ɂ���
	m_titlePosY = min(m_titlePosY, kTitleLogoPosY);

	/*�^�C�g��������*/
	// �^�C�g���̗������𗬂�
	if (m_titlePosY <= kTitleLogoPosY && !m_isPlayFallSE)
	{
		// ������������ĂȂ������ꍇ
		if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Fall"))
		{
			// ������
			SoundManager::GetInstance().Play("Fall");
		}
	}
	// �^�C�g�������n�����璅�n���𗬂�
	if (m_titlePosY >= kTitleLogoPosY && !m_isPlayFallSE)
	{
		// ����̍Đ�
		PlayMovieToGraph(m_movieH);
		// ���n��
		SoundManager::GetInstance().Play("TitleLanding");
		m_isPlayFallSE = true;
	}
	// SE������I����Ă���BGM�𗬂�
	if (m_titlePosY >= kTitleLogoPosY && m_isPlayFallSE)
	{
		// BGM�𗬂�
		SoundManager::GetInstance().Play("TitleScene");

		// ���悪��~���Ă�����Đ��ʒu���ŏ��ɖ߂�
		if (GetMovieStateToGraph(m_movieH) == 0)
		{
			SeekMovieToGraph(m_movieH, 0);
		}

		// ����̍Đ�
		PlayMovieToGraph(m_movieH);
		
	}

	// �^�C�g������������ɉ�������̃{�^����������Ă����玟�̃V�[���ɑJ�ڂ���
	if (CheckHitKeyAll() && m_titlePosY >= kTitleLogoPosY)
	{
		// ����SE�𗬂�
		SoundManager::GetInstance().Play("TitleButtonPush");

		return std::make_shared<SceneSelect>();
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
	// ����̕`��
	DrawGraph(0, 0, m_movieH, true);

	// �^�C�g���摜�̕`��
	DrawRotaGraph(kTitleLogoPosX, m_titlePosY,
		1.0f, 0.0f,
		m_titleLogoH, true);

	// �^�C�g�������肫���ĂȂ������ꍇ�͕\�����Ȃ�
	if (m_titlePosY < kTitleLogoPosY) return;
	// �e�L�X�g�̕`��
	DrawRotaGraph(kPressAnyButtonPosX, kPressAnyButtonPosY,
		1.0f, 0.0f,
		m_textH, true);

#ifdef _DEBUG
	// �V�[�����̕`��
	DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG   

	// �t�F�[�h�̕`��
	DrawFade();
}

void SceneTitle::End()
{
	// BGM������
	SoundManager::GetInstance().DesignationStopSound("TitleScene");
}
