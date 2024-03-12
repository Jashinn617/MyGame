#include "Tutorial01.h"
#include "../Game.h"
#include "../util/Input.h"
#include "../Player.h"
#include "../Camera.h"
#include "../UI.h"
#include "../Object/Door.h"

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

	// ���̃A�j���[�V����
	constexpr int kAnimFrame = 60;

	// ���̓_�ő��x
	constexpr int kArrowBlinkingSpeed = 30;
	// ���̓_�ŕp�x
	constexpr int kArrowBlinkingFrequency = 15;

	// �{�^���̑傫��
	constexpr int kButtonWidth = 26;
	constexpr int kButtonHeight = 29;

	// �{�^���̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,0 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 12;
	// �A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// �t�F�[�h�̃X�s�[�h
	constexpr int kFadeSpeed = 8;
	// �t�F�[�h�̍ő�Alpha
	constexpr int kFadeMaxAlpha = 255;

	// �h�A�̈ʒu
	constexpr int kDoorX = kChipWidth * 23;
	constexpr int kDoorY = kChipHeight * 12;

	// �{�^���̈ʒu
	constexpr int kButtonX = 780;
	constexpr int kButtonY = 390;

	// �{�^���̊g�嗦
	constexpr float kButtonRate = 2.0f;

	// �w�i�̃X�N���[���̑���
	constexpr int kScrollSpeed = 2;

	// �w�i�ɏd�˂�F�̔Z��
	constexpr int kBackOverlayAlpha = 50;

	/* ���̈ʒu*/
	// �v���C���[���w�����
	constexpr int kPlayerToPointArrowX = kChipWidth * 5;
	constexpr int kPlayerToPointArrowY = kChipHeight * 10;
	constexpr int kPlayerToPointArrowAngle = 43;
	// �h�A���w�����
	constexpr int kDoorToPointArrowX = kChipWidth * 24;
	constexpr int kDoorToPointArrowY = kChipHeight * 9;
	constexpr int kDoorToPointArrowAngle = 43;

}

Tutorial01::Tutorial01() :
	m_fgHandle(-1),
	m_bgHandle(-1),
	m_chipHandle(-1),
	m_buttonHandle(-1),
	m_arrowHandle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_buttonAnimFrame(0),
	m_blinkingArrowAnimFrame(0),
	m_bgmHandle(-1),
	m_pushSeHandle(-1),
	m_moveSeHandle(-1),
	m_fadeAlpha(0),
	m_tutorialCount(0),
	m_scrollX(0),
	m_backW(0),
	m_backH(0),
	m_isOperation(false),
	m_isDoor(false),
	m_isSceneEnd(false)
{
	/*�摜�̃��[�h*/
	m_bgHandle = LoadGraph(_T("data/Map/TutorialBg.png"));
	m_fgHandle = LoadGraph(_T("data/Map/TutorialFg.png"));
	m_arrowHandle = LoadGraph(_T("data/Tutorial/Arrow.png"));
	m_buttonHandle = LoadGraph(_T("data/Object/Button.png"));
	m_windowTextHandle[0] = LoadGraph(_T("data/Tutorial/00.png"));
	m_windowTextHandle[1] = LoadGraph(_T("data/Tutorial/01.png"));
	m_windowTextHandle[2] = LoadGraph(_T("data/Tutorial/02.png"));
	m_windowTextHandle[3] = LoadGraph(_T("data/Tutorial/04.png"));
	m_windowTextHandle[4] = LoadGraph(_T("data/Tutorial/04.png"));
	m_windowTextHandle[5] = LoadGraph(_T("data/Tutorial/05.png"));
	m_windowTextHandle[6] = LoadGraph(_T("data/Tutorial/06.png"));
	m_chipHandle = LoadGraph("data/Map/map.png");

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

Tutorial01::~Tutorial01()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_fgHandle);
	DeleteGraph(m_chipHandle);
	DeleteGraph(m_arrowHandle);
	DeleteGraph(m_buttonHandle);
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(m_windowTextHandle[i]);
	}
}

void Tutorial01::Init()
{
	// �}�b�v�̍L�������߂�
	m_pCamera->StartMixture();
	m_pCamera->Init();

	// �v���C���[��HP�Ǝc�@��S�񕜂���
	m_pPlayer->CompleteRecoveryHp();
	m_pPlayer->CompleteRecoveryLives();

	// BGM�̓ǂݍ���
	m_bgmHandle = LoadSoundMem(_T("data/Sound/BGM/Tutorial.mp3"));
	// BGM�̉��ʐݒ�
	ChangeVolumeSoundMem(200, m_bgmHandle);

	// SE�̓ǂݍ���
	m_moveSeHandle = LoadSoundMem(_T("data/Sound/SE/Move.wav"));
	m_pushSeHandle = LoadSoundMem(_T("data/Sound/SE/Push.wav"));

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, true);

	// �v���C���[�̏�����
	m_pPlayer->Init();
	// �������W�̐ݒ�
	m_pPlayer->SetStartPos(kStartX, kStartY);
	// �h�A�̏�����
	m_pDoor->Init(kDoorX, kDoorY);
	// UI�̏�����
	m_pUI->Init();

	// �V�[�����I�����Ȃ��悤�ɂ���
	m_tutorialCount = 0;
	m_isOperation = false;
	m_isSceneEnd = false;
}

void Tutorial01::Update(Input& input)
{
	if (!m_isSceneEnd)
	{
		// �w�i���X�N���[��������
		m_scrollX += kScrollSpeed;

		m_pUI->Update();

		// ���̓_��
		m_blinkingArrowAnimFrame--;
		if (m_blinkingArrowAnimFrame < 0)m_blinkingArrowAnimFrame = kAnimFrame;

		// �v���C���[�����������Ԃ��ǂ���
		if (m_isOperation)
		{
			m_pPlayer->Update(input, m_chipData, kChipNumX, kChipNumY, kChipWidth, kChipHeight);
		}
		// �h�A�����݂��Ă��邩�ǂ���
		if (m_isDoor)
		{
			m_pDoor->Update();

			if (m_pDoor->IsColision())
			{
				if (input.IsTriggered("up"))
				{
					PlaySoundMem(m_moveSeHandle, DX_PLAYTYPE_BACK, true);
					m_isSceneEnd = true;
				}
			}
		}

		// �������̏���
		if (!m_isOperation)
		{
			// A�{�^���������Ǝ��̐����ɐi��
			// �`���[�g���A���̃J�E���^���������
			if (input.IsTriggered("A"))
			{
				PlaySoundMem(m_pushSeHandle, DX_PLAYTYPE_BACK, true);
				m_tutorialCount++;
			}
		}

		// �`���[�g���A���̃J�E���^��3�ɂȂ�ƃh�A���o������
		if (m_tutorialCount == 3)
		{
			m_isDoor = true;
			m_tutorialCount++;
		}
		// �`���[�g���A���̃J�E���^��6�ɂȂ�ƃv���C���[����������悤�ɂȂ�
		if (m_tutorialCount >= 6)
		{
			m_isOperation = true;
		}

		// �{�^���̃A�j���[�V����
		if (!m_isOperation)
		{	
			m_buttonAnimFrame++;
			if (m_buttonAnimFrame >= kAnimFrameCycle)
			{
				m_buttonAnimFrame = 0;
			}
		}

		// �t�F�[�h�C��
		m_fadeAlpha -= kFadeSpeed;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	// ��ʓ]��
	else
	{
		// �t�F�[�h�A�E�g
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha > kFadeMaxAlpha)
		{
			m_fadeAlpha = kFadeMaxAlpha;
		}
	}
}

void Tutorial01::Draw()
{
	// �w�i�̕\��
	BackDraw();

	// �}�b�v�`�b�v�̕`��
	ChipDraw();

	// �h�A�̕`��
	if (m_isDoor)
	{
		m_pDoor->Draw();
	}

	// UI�̕`��
	m_pUI->Draw();
	// �`���[�g���A���̐����̉摜�̕`��
	DrawGraph(0, 0, m_windowTextHandle[m_tutorialCount], true);
	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �{�^���̕`��
	if (!m_isOperation)
	{
		// �A�j���[�V����
		int animFrame = m_buttonAnimFrame / kAnimFrameNum;
		int srcY = kUseFrame[animFrame] * kButtonHeight;

		DrawRectRotaGraph(kButtonX, kButtonY, 0, srcY, kButtonWidth, kButtonHeight, kButtonRate, 0.0, m_buttonHandle, true);
	}
	// ���̓_��
	if (m_blinkingArrowAnimFrame % kArrowBlinkingSpeed >= kArrowBlinkingFrequency)return;
	// ���̕`��
	if (m_tutorialCount == 2)
	{
		DrawRotaGraph(kPlayerToPointArrowX, kPlayerToPointArrowY, 1.0, kPlayerToPointArrowAngle, m_arrowHandle, true);
	}
	if (m_tutorialCount >= 3)
	{
		DrawRotaGraph(kDoorToPointArrowX, kDoorToPointArrowY, 1.0, kDoorToPointArrowAngle, m_arrowHandle, true);
	}

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, kScreenWidht, kScreenHeight, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void Tutorial01::ChipDraw()
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

void Tutorial01::BackDraw()
{
	// �����X�N���[��
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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kBackOverlayAlpha);
	DrawBox(0, 0, kScreenWidht, kScreenHeight, 0xb22222, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void Tutorial01::End()
{
	// BGM���~�߂�
	StopSoundMem(m_bgmHandle);
	// BGM������������폜����
	DeleteSoundMem(m_bgmHandle);
	// SE������������폜����
	DeleteSoundMem(m_pushSeHandle);
	DeleteSoundMem(m_moveSeHandle);
}

bool Tutorial01::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= kFadeMaxAlpha);
}
