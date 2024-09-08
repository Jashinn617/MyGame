#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "StageSceneManager.h"
#include "SceneStage.h"

#include "../Util/Game.h"
#include "../Util/Input.h"
#include "../Util/Pad.h"
#include "../Util/SoundManager.h"

#include "../Object/SkyDome.h"
#include "../Object/Camera.h"

#include <assert.h>

namespace
{
	const char* const kTitleLogoImg = "Data/Img/Title/Logo.png";
	const char* const kPressAnyButtonImg = "Data/Img/Title/PressAnyButton.png";
	const char* const kMovieFileName = "Data/Movie/DemoMovie.mp4";

	/*�^�C�g�����S�摜�̏������W*/
	constexpr int kStartTitleLogoPosY = -1200;
	/*�^�C�g�����S�摜�̍��W*/
	constexpr int kTitleLogoPosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kTitleLogoPosY = static_cast<int>(Game::kScreenHeight * 0.5f);	// Y
	/*�v���X�{�^���̉摜�̍��W*/
	constexpr int kPressAnyButtonPosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kPressAnyButtonPosY = static_cast<int>(Game::kScreenHeight * 0.5f);	// Y

	constexpr int kTitleFallSpeed = 30;	// �^�C�g���������Ă��鑬�x
}

SceneTitle::SceneTitle():
	m_H1(-1),
	m_H2(-1),
	m_movieH(-1),
	m_TitlePosY(kStartTitleLogoPosY),
	m_IsPlayFallSE(false)
{
	/*�摜�̃��[�h*/
	m_H1 = LoadGraph(kTitleLogoImg);
	m_H2 = LoadGraph(kPressAnyButtonImg);
	/*����̃��[�h*/
	m_movieH = LoadGraph(kMovieFileName);
	assert(m_movieH != -1);
}

SceneTitle::~SceneTitle()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_H1);
	DeleteGraph(m_H2);
	/*����̃f���[�g*/
	DeleteGraph(m_movieH);
}

void SceneTitle::Init()
{
	/*��������*/

}

std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	UpdateFade();

	m_TitlePosY += kTitleFallSpeed;
	m_TitlePosY = min(m_TitlePosY, kTitleLogoPosY);

	/*�^�C�g��������*/
	// �^�C�g���̗������𗬂�
	if (m_TitlePosY <= kTitleLogoPosY && !m_IsPlayFallSE)
	{
		// ������������ĂȂ������ꍇ
		if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("Fall"))
		{
			SoundManager::GetInstance().Play("Fall");
		}
	}

	// �^�C�g�������n�����璅�n���𗬂�
	if (m_TitlePosY >= kTitleLogoPosY && !m_IsPlayFallSE)
	{
		// ����̍Đ�
		PlayMovieToGraph(m_movieH);
		SoundManager::GetInstance().Play("TitleLanding");
		m_IsPlayFallSE = true;
	}
	// SE������I����Ă���BGM�𗬂�
	if (m_TitlePosY >= kTitleLogoPosY && m_IsPlayFallSE)
	{
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
	if (CheckHitKeyAll() && m_TitlePosY >= kTitleLogoPosY)
	{
		// BGM������
		SoundManager::GetInstance().DesignationStopSound("TitleScene");

		// ����SE�𗬂�
		SoundManager::GetInstance().Play("TitleButtonPush");

		return make_shared<SceneSelect>();
	}

	

	return shared_from_this();
}

void SceneTitle::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG   

	// ����̕`��
	DrawGraph(0, 0, m_movieH, true);


	// �^�C�g���摜�̕`��
	DrawRotaGraph(kTitleLogoPosX, m_TitlePosY,
		1.0f, 0.0f,
		m_H1, true);

	// �^�C�g�������肫���ĂȂ������ꍇ�͕\�����Ȃ�
	if (m_TitlePosY < kTitleLogoPosY) return;

	DrawRotaGraph(kPressAnyButtonPosX, kPressAnyButtonPosY,
		1.0f, 0.0f,
		m_H2, true);

	DrawFade();
}

void SceneTitle::End()
{
	/*��������*/
}
