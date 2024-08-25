#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

#include "../Util/Game.h"
#include "../Util/Input.h"
#include "../Util/Pad.h"

#include "../Object/SkyDome.h"
#include "../Object/Camera.h"

namespace
{
	const char* const kTitleLogoImg = "Data/Img/Title/Logo.png";
	const char* const kPressAnyButtonImg = "Data/Img/Title/PressAnyButton.png";

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
	m_TitlePosY(kStartTitleLogoPosY)
{
	/*�摜�̃��[�h*/
	m_H1 = LoadGraph(kTitleLogoImg);
	m_H2 = LoadGraph(kPressAnyButtonImg);
}

SceneTitle::~SceneTitle()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_H1);
	DeleteGraph(m_H2);
}

void SceneTitle::Init()
{
}

std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_TitlePosY += kTitleFallSpeed;
	m_TitlePosY = min(m_TitlePosY, kTitleLogoPosY);

	// �^�C�g������������ɉ�������̃{�^����������Ă����玟�̃V�[���ɑJ�ڂ���
	if (CheckHitKeyAll() && m_TitlePosY >= kTitleLogoPosY)
	{
		return make_shared<SceneSelect>();
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG   

	// �^�C�g���摜�̕`��
	DrawRotaGraph(kTitleLogoPosX, m_TitlePosY,
		1.0f, 0.0f,
		m_H1, true);

	// �^�C�g�������肫���ĂȂ������ꍇ�͕\�����Ȃ�
	if (m_TitlePosY < kTitleLogoPosY) return;

	DrawRotaGraph(kPressAnyButtonPosX, kPressAnyButtonPosY,
		1.0f, 0.0f,
		m_H2, true);
}

void SceneTitle::End()
{
}
