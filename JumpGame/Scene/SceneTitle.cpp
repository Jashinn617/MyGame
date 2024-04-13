#include "SceneTitle.h"
#include "MainScene.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_titleLogoHandle(-1),
	m_startLogoHandle(-1),
	m_endLogoHandle(-1),
	m_selectCursorHandle(-1),
	m_bgmHandle(-1),
	m_cursorMoveSeHandle(-1),
	m_startSeHandle(-1),
	m_startExtRate(kSmallStartExtRate),
	m_endExtRate(kSmallEndExtRate),
	m_cursorSinPosX(0),
	m_cursorPosY(kStartPosY),
	m_cursorCount(0),
	m_cursorSinCount(0),
	m_fadeAlpha(255),
	m_isSceneEnd(false)
{
	m_titleLogoHandle = LoadGraph("Data/Image/Logo/Title.png");
	m_startLogoHandle = LoadGraph("Data/Image/Logo/Start.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End.png");
	m_selectCursorHandle = LoadGraph("Data/Image/SelectCursor.png");
	m_bgmHandle = LoadSoundMem("Data/Sound/BGM/Title.ogg");
	m_cursorMoveSeHandle = LoadSoundMem("Data/Sound/SE/CursorMove.mp3");
	m_startSeHandle = LoadSoundMem("Data/Sound/SE/Start.mp3");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogoHandle);
	DeleteGraph(m_startLogoHandle);
	DeleteGraph(m_endLogoHandle);
	DeleteGraph(m_selectCursorHandle);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_cursorMoveSeHandle);
	DeleteSoundMem(m_startSeHandle);
}

void SceneTitle::Init()
{
	ChangeVolumeSoundMem(kBgmVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kSeVolume, m_cursorMoveSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_startSeHandle);
	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	// ��ʓ]��
	if (m_isSceneEnd)
	{
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
			return make_shared<MainScene>();
		}
	}
	else
	{
		m_fadeAlpha -= kFadeSpeed;

		if (input.IsTriggered("up"))
		{
			m_cursorCount--;
			PlaySoundMem(m_cursorMoveSeHandle, DX_PLAYTYPE_BACK);
		}
		else if (input.IsTriggered("down"))
		{
			m_cursorCount++;
			PlaySoundMem(m_cursorMoveSeHandle, DX_PLAYTYPE_BACK);
		}

		if (m_cursorCount % 2 == 0)
		{
			m_cursorPosY = kStartPosY;
			m_startExtRate = kBigStartExtRate;
			m_endExtRate = kSmallEndExtRate;
		}
		else if (m_cursorCount % 2 == 1)
		{
			m_cursorPosY = kEndPosY;
			m_startExtRate = kSmallStartExtRate;
			m_endExtRate = kBigEndExtRate;
		}

		// �J�[�\���̃A�j���[�V����
		m_cursorSinCount += kCursorSinSpeed;
		m_cursorSinPosX = sinf(m_cursorSinCount) * kCursorAnimationSwing;


		if (input.IsTriggered("A"))
		{
			if (m_cursorCount % 2 == 0)
			{
				// BGM�̒�~
				StopSoundMem(m_bgmHandle);
				PlaySoundMem(m_startSeHandle, DX_PLAYTYPE_BACK);
				m_isSceneEnd = true;
			}
			else if (m_cursorCount % 2 == 1)
			{
				DxLib_End();
			}
		}

		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	
	return shared_from_this();
}

void SceneTitle::Draw()
{
	DrawRotaGraphF(kTitlePosX, kTitlePosY, kTitleExtRate, 0.0, m_titleLogoHandle, true, false);
	DrawRotaGraphF(kStartPosX, kStartPosY, m_startExtRate, 0.0, m_startLogoHandle, true, false);
	DrawRotaGraphF(kEndPosX, kEndPosY, m_endExtRate, 0.0, m_endLogoHandle, true, false);

	float curosrX = kCursorPosX + m_cursorSinPosX;
	DrawRotaGraphF(curosrX, m_cursorPosY, kCursorExtRate, 0.0, m_selectCursorHandle, true, false);

#ifdef _DEBUG
	DrawString(0, 0, "Title", 0xffffff);
	DrawFormatString(0, 50, 0xffffff, "Count�F%d", m_cursorCount % 2);
#endif	

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, kScreenWidth, kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneTitle::End()
{

}
