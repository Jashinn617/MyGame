#include "StoryScene.h"
#include"DxLib.h"
#include "../Game.h"
#include "../util/Input.h"

namespace
{
	// �{�^���̑傫��
	constexpr int kButtonWidth = 26;
	constexpr int kButtonHeight = 29;

	// �摜�؂�ւ��̃t���[����
	constexpr int kStoryFrame = 300;

	// �t�F�[�h���̑���
	constexpr int kMissFadeSpeed = 12;
}

StoryScene::StoryScene() :
	m_bgmHandle(-1),
	m_skipHandle(-1),
	m_buttonHandle(-1),
	m_storyFrame(0),
	m_storyCount(0),
	m_fadeAlpha(255),
	m_isSceneEnd(false)
{
	/*�O���t�B�b�N�̃��[�h*/
	m_storyHandle[0] = LoadGraph(_T("data/Story/00.png"));
	m_storyHandle[1] = LoadGraph(_T("data/Story/01.png"));
	m_storyHandle[2] = LoadGraph(_T("data/Story/02.png"));
	m_storyHandle[3] = LoadGraph(_T("data/Story/03.png"));
	m_storyHandle[4] = LoadGraph(_T("data/Story/04.png"));
	m_storyHandle[5] = LoadGraph(_T("data/Story/05.png"));
	m_storyHandle[6] = LoadGraph(_T("data/Story/06.png"));
	m_storyHandle[7] = LoadGraph(_T("data/Story/07.png"));
	m_skipHandle = LoadGraph(_T("data/Story/skip.png"));
	m_buttonHandle = LoadGraph(_T("data/Object/Button.png"));
}

StoryScene::~StoryScene()
{
	/*�O���t�B�b�N�̃f���[�g*/
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(m_storyHandle[i]);
	}
	DeleteGraph(m_skipHandle);
	DeleteGraph(m_buttonHandle);
}

void StoryScene::Init()
{
	/*BGM�̃��[�h*/
	m_bgmHandle = LoadSoundMem(_T("data/Sound/BGM/Story.mp3"));
	/*BGM�̍Đ�*/
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, true);
	// �V�[�����I�����Ȃ��悤�ɂ���
	m_isSceneEnd = false;
	m_storyFrame = 0;
}

void StoryScene::Update(Input& input)
{
	if (!m_isSceneEnd)
	{
		m_storyFrame++;

		// A�{�^������������X�L�b�v���ł���
		if (input.IsTriggered("A"))
		{
			m_isSceneEnd = true;
		}

		if (m_storyFrame >= kStoryFrame)
		{
			m_storyCount++;
			m_storyFrame = 0;
		}

		// �X�g�[���[���I���ƃV�[�����I������
		if (m_storyCount>=_countof(m_storyHandle))
		{
			m_isSceneEnd = true;
		}

		// �t�F�[�h�A�E�g
		m_fadeAlpha -= kMissFadeSpeed;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	// ��ʓ]���̃t�F�[�h
	else // �t�F�[�h�C��
	{
		m_fadeAlpha += kMissFadeSpeed;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
}

void StoryScene::Draw()
{
	// �X�g�[���[�摜�̕\��
	DrawGraph(0, 0, m_storyHandle[m_storyCount], true);
	// �X�L�b�v�摜�̕\��
	DrawGraph(0, 0, m_skipHandle, true);
	DrawRectRotaGraph(1850, 30,
		0, 0, 
		kButtonWidth, kButtonHeight,
		2.0, 0.0, m_buttonHandle, true);

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void StoryScene::End()
{
	/*BGM���~�߂�*/
	StopSoundMem(m_bgmHandle);
	/*BGM�̍Đ�*/
	DeleteSoundMem(m_bgmHandle);
}

bool StoryScene::IsSceneEnd()
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
