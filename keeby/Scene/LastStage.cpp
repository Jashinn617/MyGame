#include "LastStage.h"
#include "../Game.h"
#include "../util/Input.h"
#include "../Player.h"
#include "../Camera.h"
#include "../UI.h"
#include "../Object/GoalFlower.h"
#include "../Enemy/Boss.h"

#include "DxLib.h"

namespace
{
	// �}�b�v�̍L��
	constexpr int kMapWidth = Game::kScreenWidth;
	constexpr int kMapHeight = Game::kScreenHeight;

	// �}�b�v�`�b�v�̏��
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;

	// �w�i�̑傫��
	constexpr int kBackWidth = Game::kScreenWidth;
	constexpr int kBackHeight = Game::kScreenHeight;

	// �`�b�v��u����
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

	// �v���C���[�̏������W
	constexpr int kStartX = kChipWidth * 4;
	constexpr int kStartY = kChipHeight * 12;

	// ��ʂ̑傫��
	constexpr int kScreenWidht = Game::kScreenWidth;
	constexpr int kScreenHeight = Game::kScreenHeight;

	// �{�X�L�����N�^�[��HP
	constexpr int kBossHp = 6;

	// �v���C���[���~�X�������Ƃ��̉��o�t���[��
	constexpr int kMissSe02Frame = 60;
	constexpr int kMissFrameMax = 60 * 2;
	constexpr float kMissFadeFrame = 60 * 2.2;
	constexpr float kContinueFrame = 60 * 2.6;
}

LastStage::LastStage():
	m_bgHandle(-1),
	m_fgHandle(-1),
	m_chipHandle(-1),
	m_moveFlowerHandle(-1),
	m_bossHandle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_bgmHandle(-1),
	m_missSeHandle(-1),
	m_missSeHandle02(-1),
	m_flowerMoveSeHandle(-1),
	m_fadeAlpha(0),
	m_isMissFade(0),
	m_isBossExist(false),
	m_shakeFrame(0),
	m_nextScene(kClear),
	m_isMiss(false),
	m_scrollX(0),
	m_backW(0),
	m_backH(0),
	m_isClear(false),
	m_moveEventX(0),
	m_moveEventY(0),
	m_moveEventFrame(0),
	m_extRate(0),
	m_isSceneEnd(false)
{
	// �Q�[����ʕ`���̐���
	m_gameScreenHandle = MakeScreen(kScreenWidht, kScreenHeight, true);
	/*�摜�̃��[�h*/
	m_bgHandle = LoadGraph(_T("data/Map/TutorialBg.png"));
	m_fgHandle = LoadGraph(_T("data/Map/TutorialFg.png"));
	m_chipHandle = LoadGraph("data/Map/map.png");
	m_moveFlowerHandle = LoadGraph(_T("data/Event/MoveFlowerColor.png"));

	/*SE�̃��[�h*/
	m_flowerMoveSeHandle = LoadSoundMem(_T("data/Sound/SE/FlowerMove.mp3"));

	// �}�b�v�`�b�v�̔z�u�f�[�^�̏�����
	m_chipData = {
		{04,04,04,04,04,04,03,04,04,04,04,03,04,04,04,04,04,03,04,04,04,04,04,04,04,04,03,04,04,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,04},
		{04,04,04,04,04,04,04,03,04,04,04,04,04,03,04,04,04,04,03,04,04,04,04,04,04,04,03,04,04,04},
		{04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04},
		{04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04},
		{04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04,04}
	};

	// �}�b�v�`�b�v�̐��𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_chipHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;
}

LastStage::~LastStage()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_gameScreenHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_fgHandle);
	DeleteGraph(m_chipHandle);
	DeleteGraph(m_moveFlowerHandle);

}

void LastStage::Init()
{
	m_pCamera->StartMixture();

	// BGM�̓ǂݍ���
	m_bgmHandle = LoadSoundMem(_T("data/Sound/BGM/Boss.mp3"));
	// BGM�̉��ʐݒ�
	ChangeVolumeSoundMem(200, m_bgmHandle);

	/*SE�̃��[�h*/
	m_missSeHandle = LoadSoundMem(_T("data/Sound/SE/Miss.wav"));
	m_missSeHandle02 = LoadSoundMem(_T("data/Sound/SE/Miss02.mp3"));

	// �ԂɐF��t����
	m_pFlower->SetFlowerColor();

	RestartInit();	

	m_pFlower->Init(kMapWidth / 2, kMapHeight / 2);

	m_moveEventX = 880;
	m_moveEventY = 270;

	// �V�[�����I�����Ȃ��悤�ɂ���
	m_isSceneEnd = false;
	m_isClear = false;
	m_isBossExist = false;
	m_moveEventFrame = 0;
	m_isMiss = false;
}

void LastStage::Update(Input& input)
{
	// �X�N���[��
	m_scrollX += 2;

	if (!m_isSceneEnd)
	{
		// �v���C���[���~�X�������ꍇ�̓v���C���[�ȊO�̏������~�߂�
		if (!m_isMiss || !m_isClear)
		{
			m_pFlower->Update();
			m_pUI->Update();
			m_pBoss->Update();
		}

		if (!m_isClear)
		{
			// �v���C���[�Ƀ}�b�v�`�b�v�̃f�[�^��n���Ă���
			m_pPlayer->Update(input, m_chipData, kChipNumX, kChipNumY, kChipWidth, kChipHeight);
		}

		// ��ʗh��̏���
		m_shakeFrame--;
		if (m_shakeFrame < 0) m_shakeFrame = 0;

		// �~�X
		OnMiss();

		// �c�@��0�ɂȂ�����Q�[���I�[�o�[
		if (m_pPlayer->GetRemainingLives() < 0)
		{
			m_nextScene = kGameOver;
			m_isSceneEnd = true;
		}


		// �v���C���[���~�X���������̃t�F�[�h����
		if (m_isMissFade)
		{
			m_fadeAlpha += 20;
			if (m_fadeAlpha > 255)
			{
				m_fadeAlpha = 255;
				m_isMissFade = false;
			}
		}
		else
		{
			m_fadeAlpha -= 20;
			if (m_fadeAlpha < 0)
			{
				m_fadeAlpha = 0;
			}
		}

		// �{�X��HP��0�ɂȂ�����BGM���~�߂�
		if (m_pBoss->IsBossEnd())
		{
			StopSoundMem(m_bgmHandle);
		}

		// �{�X����������Ԃ��o������
		if (!m_pBoss->IsExist())
		{
			// �v���C���[���ԂɐG�ꂽ�玟�̃V�[���Ɉړ�����
			// �S�[��
			if (m_pFlower->IsColision())
			{
				StopSoundMem(m_bgmHandle);
				m_nextScene = kClear;
				m_isClear = true;

			}
		}
		

		if (m_isClear)
		{
			// �N���A���o
			ClearPerformance();
		}

		// �t�F�[�h�A�E�g
		m_fadeAlpha -= 12;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}

	}
	// ��ʓ]���̃t�F�[�h
	else // �t�F�[�h�C��
	{
		m_fadeAlpha += 12;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}	

#ifdef _DEBUG
	if (input.IsTriggered("S"))
	{
		m_nextScene = kGameOver;
		m_isSceneEnd = true;
	}
	else if (input.IsTriggered("P"))
	{
		m_nextScene = kClear;
		m_isSceneEnd = true;
	}
#endif
}

void LastStage::Draw()
{
	// �����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	BackDraw();

	// �}�b�v�`�b�v�̕`��
	ChipDraw();

	if (!m_pBoss->IsExist() && !m_pPlayer->IsFlowerMove())
	{
		// �S�[���̉Ԃ̕`��
		m_pFlower->Draw();
	}
	
	// �{�X�̕`��
	m_pBoss->Draw();

	if (!m_pPlayer->IsFlowerMove())
	{
		// �v���C���[�̕`��
		m_pPlayer->Draw();
	}
	

	// UI�̕`��
	m_pUI->Draw();

	// �Ԃɏ�����ړ�
	if (m_pPlayer->IsFlowerMove())
	{
		DrawRotaGraph(m_moveEventX, m_moveEventY, m_extRate, 0.0, m_moveFlowerHandle, true);
	}

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[����ʂ��o�b�N�o�b�t�@�ɕ`�悷��
	int screenX = 0;
	int screenY = 0;
	if (m_shakeFrame > 0)
	{
		// ��ʂ�h�炷
		screenX = GetRand(16) - 8;
		screenY = GetRand(16) - 8;
	}

	// �X�N���[���̕`��
	DrawGraph(screenX, screenY, m_gameScreenHandle, true);

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, kScreenWidht, kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void LastStage::BackDraw()
{
	GetGraphSize(m_fgHandle, &m_backW, &m_backH);

	DrawGraph(0, 0, m_bgHandle, true);
	int scrollBack = static_cast<int>(m_scrollX) % m_backW;

	for (int index = 0; index < 2; ++index)
	{
		DrawGraph(-scrollBack + index * m_backW,
			kScreenHeight - m_backH,
			m_fgHandle,
			true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, kScreenWidht, kScreenHeight, 0xb22222, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void LastStage::ChipDraw()
{
	// �v���C���[�̈ʒu�ɉ������X�N���[���ʂ����肷��
	int scrollX = m_pCamera->GetScrollX();
	int scrollY = m_pCamera->GetScrollY();

	// �}�b�v�`�b�v��~���l�߂�
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			int posX = kChipWidth * x - scrollX;
			int posY = kChipHeight * y - scrollY;

			// ��ʊO��`�悵�Ȃ�
			if (posX < 0 - kChipWidth)        continue;
			if (posX > Game::kScreenWidth)    continue;
			if (posY < 0 - kChipHeight)        continue;
			if (posY > Game::kScreenHeight)    continue;

			int chipNo = m_chipData[y][x];

			// �}�b�v�`�b�v�̃O���t�B�b�N�̐؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(posX, posY, srcX, srcY, kChipWidth, kChipHeight, m_chipHandle, true);
		}
	}
}

void LastStage::OnMiss()
{
	// �v���C���[���~�X�������ꍇ�͎c�@�����炵��HP��S�񕜂��ď����ʒu�ɖ߂�
	// ���̃X�e�[�W�Ńv���C���[�������邱�Ƃ͂Ȃ��ׁAHP���[���ɂȂ����ꍇ�̃~�X���������������Ă���
	if (m_pPlayer->GetHp() <= 0)
	{
		// ��ʂ�h�炷
		if (!m_isMiss)
		{
			m_shakeFrame = 8;
			m_pPlayer->DamageMiss();
		}

		// BGM���~�߂�
		StopSoundMem(m_bgmHandle);

		// SE��炷
		if (!CheckSoundMem(m_missSeHandle02) && !m_isMiss)
		{
			PlaySoundMem(m_missSeHandle02, DX_PLAYTYPE_BACK, true);
		}
		m_pPlayer->OnMiss();

		// ��ʂ��~�߂�
		m_isMiss = true;

	}
	// �~�X�����ď��������Ă���~�X���o�p��SE��炷
	if (m_pPlayer->GetMissFrame() >= kMissSe02Frame)
	{
		if (!CheckSoundMem(m_missSeHandle))
		{
			PlaySoundMem(m_missSeHandle, DX_PLAYTYPE_BACK, true);
		}
	}
	// �t�F�[�h���o
	if (m_pPlayer->GetMissFrame() >= kMissFrameMax)
	{
		m_isMissFade = true;
	}
	// ���X�^�[�g
	if (m_pPlayer->GetMissFrame() >= kContinueFrame)
	{
		// �v���C���[�̎c�@�����炵��HP�͑S�񕜂���
		// �v���C���[��G�l�~�[�̈ʒu������������
		m_pPlayer->DeleteLives();
		m_pPlayer->CompleteRecoveryHp();
		RestartInit();
		m_pPlayer->GravityReset();
		m_isMiss = false;

	}
}

void LastStage::ClearPerformance()
{
	m_pPlayer->OnDance();

	// �ړ����o
	if (m_pPlayer->IsFlowerMove())
	{
		m_moveEventFrame++;
		m_extRate += 0.1f;


		if (m_extRate >= 2.0)
		{
			m_extRate = 2.0;

			if (!CheckSoundMem(m_flowerMoveSeHandle))
			{
				PlaySoundMem(m_flowerMoveSeHandle, DX_PLAYTYPE_LOOP, true);
			}

			if (m_moveEventFrame >= 50 && m_moveEventFrame < 120)
			{
				m_moveEventX -= 12;
				m_moveEventY += 8;
			}
			if (m_moveEventFrame >= 120)
			{
				m_moveEventX += 18;
				m_moveEventY -= 10;
			}

			if (m_moveEventX >= kScreenWidht)
			{
				m_isSceneEnd = true;
			}
		}

	}
}

void LastStage::End()
{
	// BGM���~�߂�
	StopSoundMem(m_bgmHandle);
	// BGM������������폜����
	DeleteSoundMem(m_bgmHandle);
	// SE���~�߂�
	StopSoundMem(m_flowerMoveSeHandle);
	// SE������������폜����
	DeleteSoundMem(m_flowerMoveSeHandle);
	DeleteSoundMem(m_missSeHandle);
	DeleteSoundMem(m_missSeHandle02);
}

bool LastStage::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

void LastStage::RestartInit()
{
	/*�v���C���[�̏�����*/
	m_pPlayer->Init();
	// ���������W��ݒ�
	m_pPlayer->SetStartPos(kStartX, kStartY);
	// �d�͂̏�����
	m_pPlayer->GravityReset();

	// �{�X�̏�����
	m_pBoss->Init();

	m_pCamera->Init();
	m_pUI->Init();

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, true);

	// ��ʗh��̃t���[�����[���ɖ߂�
	m_shakeFrame = 0;

	m_isMiss = false;
	m_isBossExist = false;
}