#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "MainScene.h"
#include "DxLib.h"

SceneGameOver::SceneGameOver():
	m_gameOverLogoHandle(-1),
	m_continueLogoHandle(-1),
	m_endLogoHandle(-1),
	m_selectCursorHandle(-1),
	m_bgmHandle(-1),
	m_cursorMoveSeHandle(-1),
	m_startSeHandle(-1),
	m_endSeHandle(-1),
	m_continueExtRate(kSmallContinueExtRate),
	m_endExtRate(kSmallEndExtRate),
	m_cursorSinCount(0),
	m_cursorSinPosX(0),
	m_cursorPosY(kContinuePosY),
	m_cursorCount(0),
	m_fadeAlpha(255),
	m_isSceneEnd(false)
{
	m_gameOverLogoHandle = LoadGraph("Data/Image/Logo/GameOver.png");
	m_continueLogoHandle = LoadGraph("Data/Image/Logo/Continue.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End2.png");
	m_selectCursorHandle = LoadGraph("Data/Image/SelectCursor.png");
	m_bgmHandle = LoadSoundMem("Data/Sound/BGM/GameOver.ogg");
	m_cursorMoveSeHandle = LoadSoundMem("Data/Sound/SE/CursorMove.mp3");
	m_startSeHandle = LoadSoundMem("Data/Sound/SE/Start.mp3");
	m_endSeHandle = LoadSoundMem("Data/Sound/SE/GameEnd.mp3");
}

SceneGameOver::~SceneGameOver()
{
	DeleteGraph(m_gameOverLogoHandle);
	DeleteGraph(m_continueLogoHandle);
	DeleteGraph(m_endLogoHandle);
	DeleteGraph(m_selectCursorHandle);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_cursorMoveSeHandle);
	DeleteSoundMem(m_startSeHandle);
	DeleteSoundMem(m_endSeHandle);
}

void SceneGameOver::Init()
{
	ChangeVolumeSoundMem(kBgmVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kSeVolume, m_cursorMoveSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_startSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_endSeHandle);
	// BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

shared_ptr<SceneBase> SceneGameOver::Update(Input& input)
{
	if (m_isSceneEnd)
	{
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;

			if (m_cursorCount % 2 == 0)
			{
				return make_shared<MainScene>();
			}
			else if (m_cursorCount % 2 == 1)
			{
				return make_shared<SceneTitle>();
			}
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
			m_cursorPosY = kContinuePosY;
			m_continueExtRate = kBigContinueExtRate;
			m_endExtRate = kSmallEndExtRate;
		}
		else if (m_cursorCount % 2 == 1)
		{
			m_cursorPosY = kEndPosY;
			m_continueExtRate = kSmallContinueExtRate;
			m_endExtRate = kBigEndExtRate;
		}

		// カーソルのアニメーション
		m_cursorSinCount += kCursorSinSpeed;
		m_cursorSinPosX = sinf(m_cursorSinCount) * kCursorAnimationSwing;

		if (input.IsTriggered("A"))
		{
			if (m_cursorCount % 2 == 0)
			{
				StopSoundMem(m_bgmHandle);
				PlaySoundMem(m_startSeHandle, DX_PLAYTYPE_BACK);
			}
			else if (m_cursorCount % 2 == 1)
			{
				StopSoundMem(m_bgmHandle);
				PlaySoundMem(m_endSeHandle, DX_PLAYTYPE_BACK);
			}

			m_isSceneEnd = true;
		}

		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	
	return shared_from_this();
}

void SceneGameOver::Draw()
{
	DrawRotaGraphF(kGameOverPosX, kGameOverPosY, kGameOverExtRate, 0.0, m_gameOverLogoHandle, true, false);
	DrawRotaGraphF(kContinuePosX, kContinuePosY, m_continueExtRate, 0.0, m_continueLogoHandle, true, false);
	DrawRotaGraphF(kEndPosX, kEndPosY, m_endExtRate, 0.0, m_endLogoHandle, true, false);

	float curosrX = kCursorPosX + m_cursorSinPosX;
	DrawRotaGraphF(curosrX, m_cursorPosY, kCursorExtRate, 0.0, m_selectCursorHandle, true, false);


#ifdef _DEBUG
	DrawString(0, 0, "GameOver", 0xffffff);
	DrawFormatString(0, 50, 0xffffff, "Count：%d", m_cursorCount % 2);
#endif // _DEBUG	

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, kScreenWidth, kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneGameOver::End()
{
	
}
