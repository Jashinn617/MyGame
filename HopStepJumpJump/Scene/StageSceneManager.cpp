#include "StageSceneManager.h"

#include "../Object/ObjectManager.h"

#include "../Util/CountTime.h"
#include "../Util/Time.h"
#include "../Util/Ranking.h"
#include "../Util/Pad.h"
#include "../Util/SoundManager.h"

#include <cassert>

namespace
{
	// �X�e�[�W���Ƃ̃N���A���Ԃ̊
	constexpr double kResultDataTable[static_cast<int>(Game::Stage::StageNum)] =
	{
		3600,		// �e�X�g
		7200,		// �X�e�[�W1
		14400,		// �X�e�[�W2
		0
	};

	/*�摜�t�@�C���p�X*/
	const char* const kClearTextFileName = "Data/Img/Result/GameClearLogo.png";		// �Q�[���N���A�e�L�X�g
	const char* const kOperationFileName = "Data/Img/Operation.png";				// �������
	// �N���A�^�C��
	const char* const kMyTimeNumFileName[11] =
	{
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum0.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum1.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum2.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum3.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum4.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum5.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum6.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum7.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum8.png",
		 "Data/Img/Result/ClearTimeNum/ClearTimeNum9.png",
		 "Data/Img/Result/ClearTimeNum/ClearTime.png"
	};
	// �����L���O�^�C��
	const char* const kRankingTimeNumFileName[11] =
	{
		"Data/Img/Ranking/RankingNum/RankingNum0.png",
		"Data/Img/Ranking/RankingNum/RankingNum1.png",
		"Data/Img/Ranking/RankingNum/RankingNum2.png",
		"Data/Img/Ranking/RankingNum/RankingNum3.png",
		"Data/Img/Ranking/RankingNum/RankingNum4.png",
		"Data/Img/Ranking/RankingNum/RankingNum5.png",
		"Data/Img/Ranking/RankingNum/RankingNum6.png",
		"Data/Img/Ranking/RankingNum/RankingNum7.png",
		"Data/Img/Ranking/RankingNum/RankingNum8.png",
		"Data/Img/Ranking/RankingNum/RankingNum9.png",
		"Data/Img/Ranking/RankingNum/RankingTime.png"
	};
	// �����N
	const char* const kRankFileName[static_cast<int>(StageSceneManager::Rank::RankNum)] =
	{
		"Data/Img/Result/Rank/S.png",
		"Data/Img/Result/Rank/A.png",
		"Data/Img/Result/Rank/B.png",
		"Data/Img/Result/Rank/C.png"
	};
	// �e�L�X�g
	const char* const kTextFileName[3] =
	{
		"Data/Img/Result/ClearTimeText.png",
		"Data/Img/Result/RankText.png",
		"Data/Img/Result/RankingText.png"
	};
	// �����L���O
	const char* const kRankingFileName[3] =
	{
		"Data/Img/Ranking/Ranking1.png",
		"Data/Img/Ranking/Ranking2.png",
		"Data/Img/Ranking/Ranking3.png"
	};
	// �e�L�X�g�{�b�N�X
	const char* const kTextBoxFileName[2] =
	{
		"Data/Img/Result/ResultTextBox1.png",
		"Data/Img/Result/ResultTextBox2.png"
	};
	// �{�^��
	const char* const kButtonFileName[3] =
	{
		"Data/Img/Result/SceneChangeText1.png",
		"Data/Img/Result/SceneChangeText2.png",
		"Data/Img/Result/SceneChangeText3.png",
	};
	/*���W*/
	// �e�L�X�g
	constexpr int kTextPosX1 = 537;
	constexpr int kTextPosX2 = 1440;
	constexpr int kTextPosY1 = 151;
	constexpr int kTextPosY2 = 464;
	// �����L���O
	constexpr int kRankingPosX = 1209;
	constexpr int kRnakingPosY1 = 350;
	constexpr int kRnakingPosY2 = 600;
	constexpr int kRnakingPosY3 = 850;
	// �e�L�X�g�{�b�N�X���W
	constexpr int kTextBoxPosX1 = static_cast<int>(Game::kScreenWidth * 0.28f);
	constexpr int kTextBoxPosX2 = static_cast<int>(Game::kScreenWidth * 0.75f);
	constexpr int kTextBoxPosY = static_cast<int>(Game::kScreenHeight * 0.48f);
	// �����N���W
	constexpr int kRankPosX = 500;
	constexpr int kRankPosY = 750;
	// �N���A�^�C�����W
	constexpr int kClearMinutesFirstPosX = 200;
	constexpr int kClearMinutesSecondPosX = 350;
	constexpr int kClearSecondFirstPosX = 650;
	constexpr int kClearSecondSecondPosX = 800;
	constexpr int kClearTimeColonPosX = 500;
	constexpr int kClearTimePosY = 300;
	// �����L���O�^�C�����W
	constexpr int kRankingMinutesFirstPosX = 1400;
	constexpr int kRankingMinutesSecondPosX = 1500;
	constexpr int kRankingSecondFirstPosX = 1600;
	constexpr int kRankingSecondSecondPosX = 1700;
	constexpr int kRankingTimeColonPosX = 1550;
	constexpr int kRankingTimePosY[3] = { 350,600,850 };
	// �{�^�����W
	constexpr int kButtonPosX = Game::kScreenWidth / 2;
	constexpr int kButtonPosY1 = 200;
	constexpr int kButtonPosY2 = 500;
	constexpr int kButtonPosY3 = 750;
	// ����������W
	constexpr int kOperationPosX = 1750;
	constexpr int kOperationPosY = 200;
	// �N���A�e�L�X�g
	constexpr int kClearTextPosX = 1000;
	constexpr int kClearTextPosY = 200;
	
	/*�T�C�Y*/
	constexpr float kRankingSize = 0.3f;		// �����L���O
	constexpr float kClearTimeSize = 0.5f;		// �N���A�^�C��
	constexpr float krankingTimeSize = 0.4f;	// �����L���O�^�C��
	constexpr float kButtonSize = 1.0f;			// �ʏ�̃{�^��
	constexpr float kSelectButtonSize = 1.7f;	// �I�΂�Ă���{�^��
	constexpr float kOperationSize = 0.5f;		// �������
	constexpr float kClearTextSize = 1.2f;		// �N���A�e�L�X�g

	constexpr int kStartButtonPosY = 2000;		// �{�^���̏������W
	constexpr int kButtonUpSpeed = 40;			// �{�^���̏㏸���x
	constexpr int kTextBoxAlpha = 204;			// �e�L�X�g�{�b�N�X�̕s�����x
	constexpr int kColonArrayNum = 10;			// �^�C���̊Ԃɕ\������R�����̔z��ԍ�
	constexpr int kRankingNum = 3;				// �����L���O�̕\����
	constexpr int kClearAnim = 63;				// �N���A�A�j���[�V����
	constexpr int kStageClearSETime = 20;		// �N���ASE�������܂ł̎���
	constexpr int kImageDrawTime = 500;			// ���摜���\�������܂ł̎���
	constexpr int kRightImgDrawTime = 100;		// �E�摜���\�������܂ł̎���
	constexpr int kFallSpeed = 50;				// �摜�̗������x
	constexpr int kStartLeftPosY = 2000;		// ���摜�̏����ʒuY
	constexpr int kStartRightPosX = -1000;		// �E�摜�̏����ʒuX
	constexpr int kTimePlusSpeed = 80;			// �\���p�̃^�C���������Ă����X�s�[�h
	constexpr int kRankDrawTime = 40;			// �����N���\�������܂ł̎���
	constexpr int kSceneChangeAlpha = 200;		// �V�[���J�ڎ��̉�ʂ̈Â�
	constexpr float kRankMaxSize = 1.5f;		// �����N�摜�̍ő�T�C�Y
	constexpr float kRankEndSize = 0.8f;		// �ŏI�����N�T�C�Y
	constexpr float kRankScaleUpSpeed = 0.07f;	// �����N�摜���g�傷��X�s�[�h
}

StageSceneManager::StageSceneManager(Game::Stage stageKind):
	m_clearTime(0),
	m_drawClearTime(0),
	m_minusLeftPosY(kStartLeftPosY),
	m_minusRightPosX(kStartRightPosX),
	m_minusButtonPosY(kStartButtonPosY),
	m_alpha(0),
	m_buttonCount(0),
	m_rankSize(0.0f),
	m_selectChangeTextSize(kButtonSize),
	m_gameSceneChangeTextSize(kButtonSize),
	m_isGameClear(false),
	m_isMyRank(false),
	m_isPlayClearSE(false),
	m_isExpasionRnak(true),
	m_isButtonFall(false),
	m_isPlayRankingSE(false),
	m_nextSelect(NextSelect::GameScene),
	m_nextScene(NextScene::My),
	m_rank(Rank::S),
	m_clearSceneType(ClearSceneType::LeftImgDraw),
	m_stageKind(stageKind),
	m_pStageClearSETime(std::make_shared<Time>(kStageClearSETime)),
	m_pImageDrawTime(std::make_shared<Time>(kImageDrawTime)),
	m_pLeftImgDrawTime(std::make_shared<Time>(kImageDrawTime)),
	m_pRightImgDrawTime(std::make_shared<Time>(kRightImgDrawTime)),
	m_pRankDrawTime(std::make_shared<Time>(kRankDrawTime)),
	m_pObjectManager(std::make_shared<ObjectManager>(stageKind)),
	m_pCountTime(std::make_shared<CountTime>()),
	m_pRanking(std::make_shared<Ranking>())
{
	// �摜�̃��[�h
	LoadImg();
}

StageSceneManager::~StageSceneManager()
{
	// �摜�̃f���[�g
	DeleteImg();
}

void StageSceneManager::Init()
{
	// BGM�𗬂�
	SoundManager::GetInstance().Play("MainScene");
}

void StageSceneManager::Update()
{
	// �I�u�W�F�N�g�̍X�V
	m_pObjectManager->Update();

	if (!m_isGameClear)		// �N���A��ԂłȂ������ꍇ
	{
		// �Q�[���N���A���Ԃ̍X�V
		m_clearTime++;
		// �J�E���g�̍X�V
		m_pCountTime->Update(m_clearTime);

		// �N���A������B��������
		if (m_pObjectManager->IsGameEnd() && !m_isGameClear)
		{
			// �N���A�t���O��true�ɂ���
			m_isGameClear = true;
			// �����L���O�̎擾�A�X�V
			m_pRanking->UpdateRanking(m_stageKind, m_clearTime);
			m_ranking = m_pRanking->GetRanking(m_stageKind);
			// BGM���~�߂�
			SoundManager::GetInstance().DesignationStopSound("MainScene");
		}
	}
	else	// �Q�[���N���A��Ԃ������ꍇ
	{
		// �S�ẴI�u�W�F�N�g���Q�[���N���A��ԂɂȂ�����
		if (m_pObjectManager->IsGameClear())
		{
			// �N���A�X�V
			ClearUpdate();
		}	
	}
}

void StageSceneManager::Draw()
{
	// �I�u�W�F�N�g�̕`��
	m_pObjectManager->Draw();

	if (!m_isGameClear)		// �N���A��ԂłȂ������ꍇ
	{
		// ���ݎ��Ԃ̕`��
		m_pCountTime->Draw();
		// ��������̕`��
		DrawRotaGraph(kOperationPosX, kOperationPosY, kOperationSize,
			0.0f, m_operationH, true);
	}
	else	// �Q�[���N���A��Ԃ������ꍇ
	{
		// �S�ẴI�u�W�F�N�g���Q�[���N���A��ԂɂȂ�����
		if (m_pObjectManager->IsGameClear())
		{
			// �N���A�`��
			ClearDraw();
		}
	}
}

void StageSceneManager::ClearUpdate()
{
	// ���[�v�h�~
	if (!m_isPlayClearSE)
	{
		// SE�𗬂�
		SoundManager::GetInstance().Play("GameClear");
		// SE������I������t���O�𗧂Ă�
		m_isPlayClearSE = true;
	}
	// �N���ASE������I�������BGM�𗬂�
	if (m_isPlayClearSE &&
		!SoundManager::GetInstance().IsDesignationCheckPlaySound("GameClear"))
	{
		// BGM�𗬂�
		SoundManager::GetInstance().Play("ClearScene");
	}
	
	// ���݂̏�Ԃɂ���ď�����ς���
	switch (m_clearSceneType)
	{
	case ClearSceneType::LeftImgDraw:
		// ��莞�Ԃ������獶���̉摜�𗎂Ƃ�
		if (!m_pImageDrawTime->Update()) return;
		m_minusLeftPosY -= kFallSpeed;
		// �摜���������玟�̏����Ɉڂ�
		if (m_minusLeftPosY <= 0)
		{
			// �摜�̈ʒu������̈ʒu���炸��Ȃ��悤�ɂ���
			m_minusLeftPosY = 0;
			m_clearSceneType = ClearSceneType::ClearTimeMeasure;
		}
		break;

	case ClearSceneType::ClearTimeMeasure:
		// �N���A�^�C���𑝂₷
		m_drawClearTime += kTimePlusSpeed;

		if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("TimeCount"))
		{
			// �J�E���g�p��SE��炷
			SoundManager::GetInstance().Play("TimeCount");
		}
		// �N���A�^�C���������������玟�̏����Ɉڂ�
		if (m_drawClearTime >= m_clearTime)
		{
			// SE���~�߂�
			SoundManager::GetInstance().DesignationStopSound("TimeCount");
			// �N���A�^�C�������߂��Ȃ��悤�ɂ���
			m_drawClearTime = m_clearTime;
			m_clearSceneType = ClearSceneType::RankDraw;
		}
		break;

	case ClearSceneType::RankDraw:
		// ��莞�Ԍo�����烉���N��\������
		if (!m_pRankDrawTime->Update()) return;
		if (m_isExpasionRnak)
		{
			// �����N���g�傷��
			m_rankSize += kRankScaleUpSpeed;
			// �����N���g�債��������
			if (m_rankSize >= kRankMaxSize)
			{
				// �����L���O�\���p��SE��炷
				SoundManager::GetInstance().Play("RankDraw");
				// �T�C�Y���K��l�ȏ�ɂȂ�Ȃ��悤�ɂ���
				m_rankSize = kRankMaxSize;
				// �k�����n�߂�
				m_isExpasionRnak = false;
			}
		}
		else	
		{
			// �����N���k������
			m_rankSize -= kRankScaleUpSpeed;
			// �����N������̑傫���ɂȂ����玟�̏����Ɉڂ�
			if (m_rankSize <= kRankEndSize)
			{
				m_rankSize = kRankEndSize;
				m_clearSceneType = ClearSceneType::RankingDraw;
			}
		}
		break;

	case ClearSceneType::RankingDraw:
		// �����L���O��\������
		// �E����摜������Ă���
		if (m_pRightImgDrawTime->Update())
		{
			m_minusRightPosX -= -kFallSpeed;
		}
		// �摜������̈ʒu�ɗ�����
		if (m_minusRightPosX >= 0)
		{
			// SE��炷
			if (!m_isPlayRankingSE)
			{
				SoundManager::GetInstance().Play("RankingDraw");
				m_isPlayRankingSE = true;
			}
			// ����ȏ�͈ړ������Ȃ��悤�ɂ���
			m_minusRightPosX = 0;
			// ��������̃{�^���������ꂽ�玟�̏����Ɉڂ�
			if (CheckHitKeyAll())
			{
				// ��ʂ��Â�����
				m_alpha = kSceneChangeAlpha;
				m_clearSceneType = ClearSceneType::SceneChange;
			}
		}
		break;

	case ClearSceneType::SceneChange:
		// �^�񒆂Ƀ{�^����\������
		// �{�^���͉����猻���
		m_minusButtonPosY -= kButtonUpSpeed;
		if (m_minusButtonPosY <= 0)
		{
			// �摜������̈ʒu���炸��Ȃ��悤�ɂ���
			m_minusButtonPosY = 0;
			m_isButtonFall = true;
		}

		// �{�^���������猻�ꂽ��
		if (m_isButtonFall)
		{			
			// �J�[�\���ړ�
			if (Pad::isTrigger(PAD_INPUT_UP))
			{
				// SE��炷
				SoundManager::GetInstance().Play("Select");

				// �J�[�\���ړ�
				m_buttonCount--;
				// �J�[�\�������[�v������
				if (m_buttonCount < 0) m_buttonCount = static_cast<int>(NextSelect::Num) - 1;
			}
			if (Pad::isTrigger(PAD_INPUT_DOWN))
			{
				// SE��炷
				SoundManager::GetInstance().Play("Select");

				// �J�[�\���ړ�
				m_buttonCount++;
				// �J�[�\�������[�v������
				if (m_buttonCount >= static_cast<int>(NextSelect::Num)) m_buttonCount = 0;;
			}

			// A�{�^����B�{�^���������ꂽ��
			// �����ꂽ�{�^���ɂ���ăV�[����J�ڂ���
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
			{
				// BGM������
				SoundManager::GetInstance().DesignationStopSound("ClearScene");

				switch (m_buttonCount)
				{
				case static_cast<int>(NextSelect::GameScene):
					// SE��炷
					SoundManager::GetInstance().Play("SceneChange");

					m_nextScene = NextScene::GameScene;
					break;
				case static_cast<int>(NextSelect::Select):
					// SE��炷
					SoundManager::GetInstance().Play("SceneChange");

					m_nextScene = NextScene::Select;
					break;
				default:
					m_nextScene = NextScene::My;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void StageSceneManager::ClearDraw()
{
	// �Q�[���N���A�̉摜�̕`��
	// �����L���O���o�������
	if (!m_pImageDrawTime->Update())
	{
		DrawRotaGraph(kClearTextPosX, kClearTextPosY, kClearTextSize,
			0.0f, m_clearTextH, true);
	}

	// �e�L�X�g�`��
	TextDraw();
	// �^�C���`��
	TimeDraw();
	// �����L���O�`��
	RankingDraw();
	// �����N�`��
	RankDraw();
	
	// �w�i�������Â�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �{�^���`��
	ButtonDraw();

#ifdef _DEBUG
	// �V�[�����`��
	DrawString(0, 0, "GameClear", 0x000000);
	// �����L���O�`��
	DrawFormatString(0, 80, 0x000000, "1�ʁF%d 2�ʁF%d 3��:%d",
		m_ranking[0] / 60, m_ranking[1] / 60, m_ranking[2] / 60);
#endif // _DEBUG
}

void StageSceneManager::TextDraw()
{
	/*�e�L�X�g�{�b�N�X�̕`��*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kTextBoxAlpha);
	DrawRotaGraph(kTextBoxPosX1, kTextBoxPosY - m_minusLeftPosY,
		1.0f, 0.0f,
		m_textBoxH[0], true);
	DrawRotaGraph(kTextBoxPosX2 - m_minusRightPosX, kTextBoxPosY,
		1.0f, 0.0f,
		m_textBoxH[1], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*�e�L�X�g�̕`��*/
	DrawRotaGraph(kTextPosX1, kTextPosY1 - m_minusLeftPosY,
		1.0f, 0.0f,
		m_textH[0], true);
	DrawRotaGraph(kTextPosX1, kTextPosY2 - m_minusLeftPosY,
		1.0f, 0.0f,
		m_textH[1], true);
	DrawRotaGraph(kTextPosX2 - m_minusRightPosX, kTextPosY1,
		1.0f, 0.0f,
		m_textH[2], true);
}

void StageSceneManager::TimeDraw()
{
	/*�^�C���v�Z*/
	int clearTime = m_drawClearTime / 60;
	// ����
	int clearMinutesTime = clearTime / 60;
	int minutesTimeFirst = clearMinutesTime / 10;	// ��̈�
	int minutesTimeSecond = clearMinutesTime % 10;	// �\�̈�
	// �b��
	int clearSecondTime = clearTime % 60;
	int secondTimeFirst = clearSecondTime / 10;		// ��̈�
	int secondTimeSecond = clearSecondTime % 10;	// �\�̈�

	/*�N���A�^�C���̕`��*/
	DrawRotaGraph(kClearMinutesFirstPosX, kClearTimePosY - m_minusLeftPosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeFirst], true);
	DrawRotaGraph(kClearMinutesSecondPosX, kClearTimePosY - m_minusLeftPosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeSecond], true);
	DrawRotaGraph(kClearTimeColonPosX, kClearTimePosY - m_minusLeftPosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[kColonArrayNum], true);
	DrawRotaGraph(kClearSecondFirstPosX, kClearTimePosY - m_minusLeftPosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kClearSecondSecondPosX, kClearTimePosY - m_minusLeftPosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[secondTimeSecond], true);
}

void StageSceneManager::RankingDraw()
{
	/*�����L���O�̕`��*/
	DrawRotaGraph(kRankingPosX - m_minusRightPosX, kRnakingPosY1,
		kRankingSize, 0.0f,
		m_rankingH[0], true);
	DrawRotaGraph(kRankingPosX - m_minusRightPosX, kRnakingPosY2,
		kRankingSize, 0.0f,
		m_rankingH[1], true);
	DrawRotaGraph(kRankingPosX - m_minusRightPosX, kRnakingPosY3,
		kRankingSize, 0.0f,
		m_rankingH[2], true);

	// �����̃^�C���Ɠ����^�C�����������ꍇ�ɕ\�����d�����Ȃ��悤�ɂ���t���O
	m_isMyRank = false;
	/*�����L���O�^�C���̕`��*/
	for (int i = 0; i < kRankingNum; i++)
	{
		// �����L���O�̃^�C���������Ɠ����^�C���������ꍇ��
		// �����F��ς���
		// �����^�C������ȏゾ�����ꍇ�͏�̏��ʂ̐F�����ς���
		if (m_ranking[i] == m_clearTime && !m_isMyRank)
		{
			MyRankTimeDraw(i);
			// ���f�t���O�𗧂Ă�
			m_isMyRank = true;
		}
		else
		{
			RankingTimeDraw(i);
		}
	}
}

void StageSceneManager::RankDraw()
{
	/*�����N�v�Z*/
	// ���ꂼ��̃^�C���̊
	float BRankTime = static_cast<float>(kResultDataTable[static_cast<int>(m_stageKind)]);
	float ARankTime = BRankTime * 0.8f;
	float SRankTime = ARankTime * 0.8f;

	if (BRankTime <= m_clearTime)
	{
		m_rank = Rank::C;
	}
	else if (BRankTime > m_clearTime && ARankTime <= m_clearTime)
	{
		m_rank = Rank::B;
	}
	else if (ARankTime > m_clearTime && SRankTime <= m_clearTime)
	{
		m_rank = Rank::A;
	}
	else if (SRankTime > m_clearTime)
	{
		m_rank = Rank::S;
	}
	else
	{
		m_rank = Rank::S;
	}
	// �`��
	DrawRotaGraph(kRankPosX, kRankPosY - m_minusLeftPosY,
		m_rankSize, 0.0f,
		m_rankH[static_cast<int>(m_rank)], true);
}

void StageSceneManager::RankingTimeDraw(int ranking)
{
	/*�^�C���v�Z*/
	int rankingTime = m_ranking[ranking] / 60;
	// ����
	int clearMinutesTime = rankingTime / 60;
	int minutesTimeFirst = clearMinutesTime / 10;	// ��̈�
	int minutesTimeSecond = clearMinutesTime % 10;	// �\�̈�
	// �b��
	int clearSecondTime = rankingTime % 60;
	int secondTimeFirst = clearSecondTime / 10;		// ��̈�
	int secondTimeSecond = clearSecondTime % 10;	// �\�̈�

	/*�`��*/
	DrawRotaGraph(kRankingMinutesFirstPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[minutesTimeFirst], true);
	DrawRotaGraph(kRankingMinutesSecondPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[minutesTimeSecond], true);
	DrawRotaGraph(kRankingTimeColonPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[kColonArrayNum], true);
	DrawRotaGraph(kRankingSecondFirstPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kRankingSecondSecondPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[secondTimeSecond], true);
}

void StageSceneManager::MyRankTimeDraw(int ranking)
{
	/*�^�C���v�Z*/
	int rankingTime = m_ranking[ranking] / 60;
	// ����
	int clearMinutesTime = rankingTime / 60;
	int minutesTimeFirst = clearMinutesTime / 10;	// ��̈�
	int minutesTimeSecond = clearMinutesTime % 10;	// �\�̈�
	// �b��
	int clearSecondTime = rankingTime % 60;
	int secondTimeFirst = clearSecondTime / 10;		// ��̈�
	int secondTimeSecond = clearSecondTime % 10;	// �\�̈�

	/*�`��*/
	DrawRotaGraph(kRankingMinutesFirstPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeFirst], true);
	DrawRotaGraph(kRankingMinutesSecondPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeSecond], true);
	DrawRotaGraph(kRankingTimeColonPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[kColonArrayNum], true);
	DrawRotaGraph(kRankingSecondFirstPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kRankingSecondSecondPosX - m_minusRightPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[secondTimeSecond], true);
}

void StageSceneManager::ButtonDraw()
{
	// �Z���N�g����Ă���{�^���̃T�C�Y��傫������
	if (m_buttonCount == static_cast<int>(NextSelect::GameScene))
	{
		m_selectChangeTextSize = kSelectButtonSize;
		m_gameSceneChangeTextSize = kButtonSize;
	}
	else if (m_buttonCount == static_cast<int>(NextSelect::Select))
	{
		m_selectChangeTextSize = kButtonSize;
		m_gameSceneChangeTextSize = kSelectButtonSize;
	}

	/*�`��*/
	DrawRotaGraph(kButtonPosX, kButtonPosY1 - m_minusButtonPosY, 
		kButtonSize, 0.0, m_buttonH[0], true);

	DrawRotaGraph(kButtonPosX, kButtonPosY2 - m_minusButtonPosY,
		m_selectChangeTextSize, 0.0, m_buttonH[1], true);
	DrawRotaGraph(kButtonPosX, kButtonPosY3 - m_minusButtonPosY,
		m_gameSceneChangeTextSize, 0.0, m_buttonH[2], true);
}

void StageSceneManager::LoadImg()
{
	// ���[�h�Ɏ��s�����ꍇ�͎~�܂�
	m_clearTextH = LoadGraph(kClearTextFileName);
	assert(m_clearTextH != -1);
	m_operationH = LoadGraph(kOperationFileName);
	assert(m_operationH != -1);
	for (int i = 0; i < m_myTimeNumH.size(); i++)
	{
		m_myTimeNumH[i] = LoadGraph(kMyTimeNumFileName[i]);
		assert(m_myTimeNumH[i] != -1);
	}
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		m_rankingTimeNumH[i] = LoadGraph(kRankingTimeNumFileName[i]);
		assert(m_rankingTimeNumH[i] != -1);
	}
	for (int i = 0; i < m_rankH.size(); i++)
	{
		m_rankH[i] = LoadGraph(kRankFileName[i]);
		assert(m_rankH[i] != -1);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		m_textH[i] = LoadGraph(kTextFileName[i]);
		assert(m_textH[i] != -1);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		m_rankingH[i] = LoadGraph(kRankingFileName[i]);
		assert(m_rankingH[i] != -1);
	}
	for (int i = 0; i < m_textBoxH.size(); i++)
	{
		m_textBoxH[i] = LoadGraph(kTextBoxFileName[i]);
		assert(m_textBoxH[i] != -1);
	}
	for (int i = 0; i < m_buttonH.size(); i++)
	{
		m_buttonH[i] = LoadGraph(kButtonFileName[i]);
		assert(m_buttonH[i] != -1);
	}
}

void StageSceneManager::DeleteImg()
{
	DeleteGraph(m_clearTextH);
	DeleteGraph(m_operationH);
	for (int i = 0; i < m_myTimeNumH.size(); i++)
	{
		DeleteGraph(m_myTimeNumH[i]);
	}
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		DeleteGraph(m_rankingTimeNumH[i]);
	}
	for (int i = 0; i < m_rankH.size(); i++)
	{
		DeleteGraph(m_rankH[i]);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		DeleteGraph(m_textH[i]);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		DeleteGraph(m_rankingH[i]);
	}
	for (int i = 0; i < m_textBoxH.size(); i++)
	{
		DeleteGraph(m_textBoxH[i]);
	}
	for (int i = 0; i < m_buttonH.size(); i++)
	{
		DeleteGraph(m_buttonH[i]);
	}
}