#include "SceneClear.h"
#include "SceneTitle.h"
#include "MainScene.h"
#include "DxLib.h"

SceneClear::SceneClear():
	m_clearLogoHandle(-1),
	m_continueLogoHandle(-1),
	m_endLogoHandle(-1),
	m_selectCursorHandle(-1),
	m_bgHandle(-1),
	m_bgmHandle(-1),
	m_cursorMoveSeHandle(-1),
	m_continueSeHandle(-1),
	m_endSeHandle(-1),
	m_continueExtRate(kSmallContinueExtRate),
	m_endExtRate(kSmallEndExtRate),
	m_cursorSinPosX(0),
	m_cursorPosY(kContinuePosY),
	m_cursorSinCount(0),
	m_cursorCount(0),
	m_fadeAlpha(0),
	m_isSceneEnd(false)
{
	/*�摜�̃��[�h*/
	m_clearLogoHandle = LoadGraph("Data/Image/Logo/Clear.png");
	m_continueLogoHandle = LoadGraph("Data/Image/Logo/Continue.png");
	m_endLogoHandle = LoadGraph("Data/Image/Logo/End2.png");
	m_selectCursorHandle = LoadGraph("Data/Image/SelectCursor.png");
	m_bgHandle = LoadGraph("Data/Image/Background/ClearBg.jpg");
	/*BGM�ASE�̃��[�h*/
	m_bgmHandle = LoadSoundMem("Data/Sound/BGM/Clear.ogg");
	m_cursorMoveSeHandle = LoadSoundMem("Data/Sound/SE/CursorMove.mp3");
	m_continueSeHandle = LoadSoundMem("Data/Sound/SE/Start.mp3");
	m_endSeHandle = LoadSoundMem("Data/Sound/SE/GameEnd.mp3");
}

SceneClear::~SceneClear()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_clearLogoHandle);
	DeleteGraph(m_continueLogoHandle);
	DeleteGraph(m_endLogoHandle);
	DeleteGraph(m_selectCursorHandle);
	DeleteGraph(m_bgHandle);
	/*BGM�ASE�̃f���[�g*/
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_cursorMoveSeHandle);
	DeleteSoundMem(m_continueSeHandle);
	DeleteSoundMem(m_endSeHandle);
}

void SceneClear::Init()
{
	/*BGM�ASE�̃{�����[������*/
	ChangeVolumeSoundMem(kBgmVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kSeVolume, m_cursorMoveSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_continueSeHandle);
	ChangeVolumeSoundMem(kSeVolume, m_endSeHandle);
	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	// ��ʓ]��
	if (m_isSceneEnd)
	{
		// �t�F�[�h�C��
		m_fadeAlpha += kFadeSpeed;

		// ���S�Ƀt�F�[�h���������Ă����ʓ]��������
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
		// �t�F�[�h�A�E�g
		m_fadeAlpha -= kFadeSpeed;

		// �J�[�\���̈ړ��Ə���
		CursorMove(input);		

		// �J�[�\���̃A�j���[�V����
		m_cursorSinCount += kCursorSinSpeed;
		m_cursorSinPosX = sinf(m_cursorSinCount) * kCursorAnimationSwing;

		// A��������SE��炵�ă��C���V�[�����^�C�g���V�[���ɖ߂�
		if (input.IsTriggered("A"))
		{
			if (m_cursorCount % 2 == 0)
			{
				StopSoundMem(m_bgmHandle);
				PlaySoundMem(m_continueSeHandle, DX_PLAYTYPE_BACK);
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

void SceneClear::Draw()
{
	// �w�i
	DrawGraph(0, 0, m_bgHandle, true);
	// ���S
	DrawRotaGraphF(kClearPosX, kClearPosY, kClearExtRate, 0.0, m_clearLogoHandle, true, false);
	DrawRotaGraphF(kContinuePosX, kContinuePosY, m_continueExtRate, 0.0, m_continueLogoHandle, true, false);
	DrawRotaGraphF(kEndPosX, kEndPosY, m_endExtRate, 0.0, m_endLogoHandle, true, false);
	// �J�[�\��
	float curosrX = kCursorPosX + m_cursorSinPosX;
	DrawRotaGraphF(curosrX, m_cursorPosY, kCursorExtRate, 0.0, m_selectCursorHandle, true, false);

#ifdef _DEBUG
	DrawString(0, 0, "Clear", 0xffffff);
	DrawFormatString(0, 50, 0xffffff, "Count�F%d", m_cursorCount % 2);
#endif // _DEBUG

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, kScreenWidth, kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneClear::End()
{
	/*��������*/
}

void SceneClear::CursorMove(Input& input)
{
	// �J�[�\���𓮂����ۂ̏���
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
	// �J�[�\���̈ʒu�ɂ���ă��S�̊g�嗦��A���̃V�[�����ς��
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
}
