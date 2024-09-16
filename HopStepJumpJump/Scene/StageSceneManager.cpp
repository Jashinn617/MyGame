#include "StageSceneManager.h"

#include "../Object/ObjectManager.h"

#include "../Util/CountTime.h"
#include "../Util/Time.h"
#include "../Util/Ranking.h"
#include "../Util/Input.h"
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

	// �N���A���ɏo���摜�̃n���h��
	const char* const kClearTextFileName = "Data/Img/Result/GameClearLogo.png";

	// ��������̉摜�n���h��
	const char* const kOperationFileName = "Data/Img/Operation.png";

	// ���g�̃N���A�^�C���̉摜�t�@�C��
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

	// �����L���O�^�C���̉摜�t�@�C��
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

	// �����N�̉摜�n���h��
	const char* const kRankFileName[static_cast<int>(StageSceneManager::Rank::RankNum)] =
	{
		"Data/Img/Result/Rank/S.png",
		"Data/Img/Result/Rank/A.png",
		"Data/Img/Result/Rank/B.png",
		"Data/Img/Result/Rank/C.png"
	};

	// �e�L�X�g�摜�t�@�C��
	const char* const kTextFileName[3] =
	{
		"Data/Img/Result/ClearTimeText.png",
		"Data/Img/Result/RankText.png",
		"Data/Img/Result/RankingText.png"
	};

	// �����L���O�摜�t�@�C��
	const char* const kRankingFileName[3] =
	{
		"Data/Img/Ranking/Ranking1.png",
		"Data/Img/Ranking/Ranking2.png",
		"Data/Img/Ranking/Ranking3.png"
	};

	// �e�L�X�g�{�b�N�X�摜�t�@�C��
	const char* const kTextBoxFileName[2] =
	{
		"Data/Img/Result/ResultTextBox1.png",
		"Data/Img/Result/ResultTextBox2.png"
	};

	// �{�^���摜�t�@�C��
	const char* const kButtonFileName[3] =
	{
		"Data/Img/Result/SceneChangeText1.png",
		"Data/Img/Result/SceneChangeText2.png",
		"Data/Img/Result/SceneChangeText3.png",
	};

	/*�e�L�X�g���W*/
	constexpr int kTextPosX1 = static_cast<int>(Game::kScreenWidth * 0.28f);
	constexpr int kTextPosX2 = static_cast<int>(Game::kScreenWidth * 0.75f);
	constexpr int kTextPosY1 = static_cast<int>(Game::kScreenHeight * 0.14f);
	constexpr int kTextPosY2 = static_cast<int>(Game::kScreenHeight * 0.43f);
	/*�����L���O���W*/
	constexpr int kRankingPosX = 1209;
	constexpr int kRnakingPosY1 = 350;
	constexpr int kRnakingPosY2 = 600;
	constexpr int kRnakingPosY3 = 850;
	constexpr float kRankingSize = 0.3f;	// �����L���O�T�C�Y
	/*�e�L�X�g�{�b�N�X���W*/
	constexpr int kTextBoxPosX1 = static_cast<int>(Game::kScreenWidth * 0.28f);
	constexpr int kTextBoxPosX2 = static_cast<int>(Game::kScreenWidth * 0.75f);
	constexpr int kTextBoxPosY = static_cast<int>(Game::kScreenHeight * 0.48f);
	constexpr int kTextBoxAlpha = static_cast<int>(255 * 0.8f);	// �e�L�X�g�{�b�N�X�̕s�����x
	/*�����N���W*/
	constexpr int kRankPosX = 500;
	constexpr int kRankPosY = 750;
	/*�N���A�^�C�����W*/
	constexpr int kClearMinutesFirstPosX = 200;
	constexpr int kClearMinutesSecondPosX = 350;
	constexpr int kClearSecondFirstPosX = 650;
	constexpr int kClearSecondSecondPosX = 800;
	constexpr int kClearTimeColonPosX = 500;
	constexpr int kClearTimePosY = 300;
	constexpr float kClearTimeSize = 0.5f;

	/*�����L���O�^�C�����W*/
	constexpr int kRankingMinutesFirstPosX = 1400;
	constexpr int kRankingMinutesSecondPosX = 1500;
	constexpr int kRankingSecondFirstPosX = 1600;
	constexpr int kRankingSecondSecondPosX = 1700;
	constexpr int kRankingTimePosY[3] = { 350,600,850 };
	constexpr int kRankingTimeColonPosX = 1550;
	constexpr float krankingTimeSize = 0.4f;

	/*�{�^�����W*/
	constexpr int kButtonPosX = Game::kScreenWidth / 2;
	constexpr int kButtonPosY1 = 200;
	constexpr int kButtonPosY2 = 500;
	constexpr int kButtonPosY3 = 750;
	constexpr float kButtonSize = 1.0f;
	constexpr float kSelectButtonSize = 1.7f;	// �I�΂�Ă���{�^���̃T�C�Y
	constexpr int kStartButtonPosY = 2000;		// �{�^���̏����ʒu
	constexpr int kButtonUpSpeed = 40;			// �{�^���̏㏸���x

	/*����������W*/
	constexpr int kOperationPosX = 1750;
	constexpr int kOperationPosY = 200;
	constexpr float kOperationSize = 0.5f;

	constexpr int kColonArrayNum = 10;			// �^�C���̊Ԃɕ\������R�����̔z��ԍ�

	constexpr int kRankingNum = 3;			// �����L���O�̕\����
	constexpr int kClearAnim = 63;			// �N���A�A�j���[�V����
	constexpr int kStageClearSETime = 20;	// �N���ASE�������܂ł̎���
	constexpr int kImageDrawTime = 500;		// ���摜���\�������܂ł̎���
	constexpr int kRightImgDrawTime = 100;	// �E�摜���\�������܂ł̎���
	constexpr int kFallSpeed = 50;			// �摜�̗������x
	constexpr int kStartLeftPosY = 2000;		// ���摜�̏����ʒuY
	constexpr int kStartRightPosX = -1000;	// �E�摜�̏����ʒuX

	constexpr int kTimePlusSpeed = 80;		// �\���p�̃^�C���������Ă����X�s�[�h

	constexpr float kRankMaxSize = 1.5f;	// �����N�摜�̍ő�T�C�Y
	constexpr float kRankEndSize = 0.8f;	// �ŏI�����N�T�C�Y
	constexpr float kRankScaleUpSpeed = 0.07f;	// �����N�摜���g�傷��X�s�[�h
	constexpr int kRankDrawTime = 40;			// �����N���\�������܂ł̎���

	constexpr int kSceneChangeAlpha = 200;	// �V�[���J�ڎ��̉�ʂ̈Â�

	constexpr int kClearTextPosX = 1000;
	constexpr int kClearTextPosY = 200;
	constexpr float kClearTextSize = 1.2f;


}

StageSceneManager::StageSceneManager(Game::Stage stageKind):
	m_clearTextH(-1),
	m_clearTime(0),
	m_drawClearTime(0),
	m_rankSize(0.0f),
	m_isGameClear(false),
	m_isMyRank(false),
	m_isPlayClearSE(false),
	m_isExpasionRnak(true),
	m_isButtonDraw(false),
	m_isPlayRankingSE(false),
	m_isButtonFall(false),
	m_stageKind(stageKind),
	m_minusLeftPosY(kStartLeftPosY),
	m_minusRightPosX(kStartRightPosX),
	m_minusButtonPosY(kStartButtonPosY),
	m_clearSceneType(ClearSceneType::LeftImgDraw),
	m_alpha(0),
	m_buttonCount(0),
	m_nextSelect(NextSelect::Title),
	m_nextScene(NextScene::My),
	m_titleChangeTextSize(kButtonSize),
	m_gameSceneChangeTextSize(kButtonSize)
{
	m_pStageClearSETime = std::make_shared<Time>(kStageClearSETime);
	m_pImageDrawTime = std::make_shared<Time>(kImageDrawTime);
	m_pLeftImgDrawTime = std::make_shared<Time>(kImageDrawTime);
	m_pRightImgDrawTime = std::make_shared<Time>(kRightImgDrawTime);
	m_pRankDrawTime = std::make_shared<Time>(kRankDrawTime);

	m_pObjectManager = std::make_shared<ObjectManager>(stageKind);
	m_pCountTime = std::make_shared<CountTime>();
	m_pRanking = std::make_shared<Ranking>();
	ImageLoad();
}

StageSceneManager::~StageSceneManager()
{
	ImageDelete();
}

void StageSceneManager::Init()
{
	// BGM�𗬂�
	SoundManager::GetInstance().Play("MainScene");
}

void StageSceneManager::Update(Input& input)
{
	m_pObjectManager->Update(input);

	if (!m_isGameClear)
	{
		// �Q�[���N���A���Ԃ̍X�V
		m_clearTime++;

		m_pCountTime->Update(m_clearTime);

		// �N���A������B��������
		if (m_pObjectManager->IsGameEnd() && !m_isGameClear)
		{
			m_isGameClear = true;
			// �����L���O�̎擾�A�X�V
			m_pRanking->UpdateRanking(m_stageKind, m_clearTime);
			m_ranking = m_pRanking->GetRanking(m_stageKind);
			// BGM���~�߂�
			SoundManager::GetInstance().DesignationStopSound("MainScene");
		}
	}
	else
	{
		if (m_pObjectManager->IsGameClear())
		{
			ClearUpdate();
		}

	
	}

}

void StageSceneManager::Draw()
{
	m_pObjectManager->Draw();
	if (!m_isGameClear)
	{
		// ���ݎ��Ԃ̕`��
		m_pCountTime->Draw();

		// ��������̕`��
		DrawRotaGraph(kOperationPosX, kOperationPosY, kOperationSize,
			0.0f, m_operationH, true);
	}
	else
	{
		if (m_pObjectManager->IsGameClear())
		{
			ClearDraw();
		}
	}
	
}

void StageSceneManager::SetGameClear()
{
	m_pObjectManager->SetGameClear();
	m_isGameClear = true;
}

void StageSceneManager::ClearUpdate()
{
	// ���[�v�h�~
	if (!m_isPlayClearSE)
	{
		// SE�𗬂�
		SoundManager::GetInstance().Play("GameClear");
		m_isPlayClearSE = true;
	}
	// �N���ASE������I�������BGM�𗬂�
	if (m_isPlayClearSE &&
		!SoundManager::GetInstance().IsDesignationCheckPlaySound("GameClear"))
	{
		// BGM�𗬂�
		SoundManager::GetInstance().Play("ClearScene");
	}
	
	switch (m_clearSceneType)
	{
	case ClearSceneType::LeftImgDraw:
		// ��莞�Ԃ������獶���̉摜�𗎂Ƃ�
		if (!m_pImageDrawTime->Update()) return;
		m_minusLeftPosY -= kFallSpeed;
		if (m_minusLeftPosY <= 0)
		{
			m_minusLeftPosY = 0;
			m_clearSceneType = ClearSceneType::ClearTimeMeasure;
		}
		break;

	case ClearSceneType::ClearTimeMeasure:
		// �摜��������������N���A�^�C���𑝂₷
		m_drawClearTime += kTimePlusSpeed;

		if (!SoundManager::GetInstance().IsDesignationCheckPlaySound("TimeCount"))
		{
			// �J�E���g�p��SE��炷
			SoundManager::GetInstance().Play("TimeCount");
		}
		

		if (m_drawClearTime >= m_clearTime)
		{
			// SE���~�߂�
			SoundManager::GetInstance().DesignationStopSound("TimeCount");

			m_drawClearTime = m_clearTime;
			m_clearSceneType = ClearSceneType::RankDraw;

			
		}
		break;

	case ClearSceneType::RankDraw:
		// �N���A�^�C�������������Ĉ�莞�Ԃ������烉���N��\������
		if (!m_pRankDrawTime->Update()) return;
		// �����N���g�傷��
		if (m_isExpasionRnak)
		{
			m_rankSize += kRankScaleUpSpeed;
			// �����N���g�債��������
			if (m_rankSize >= kRankMaxSize)
			{
				// �����L���O�\���p��SE��炷
				SoundManager::GetInstance().Play("RankDraw");

				m_rankSize = kRankMaxSize;
				// �k�����n�߂�
				m_isExpasionRnak = false;
			}
		}
		else
		{
			m_rankSize -= kRankScaleUpSpeed;
			// �����N������̑傫���ɂȂ����烉���L���O��`�悷��
			if (m_rankSize <= kRankEndSize)
			{
				m_rankSize = kRankEndSize;
				m_clearSceneType = ClearSceneType::RankingDraw;
			}
		}
		break;

	case ClearSceneType::RankingDraw:
		// �����N��\�����Ă����莞�Ԃ������烉���L���O��\������
		if (m_pRightImgDrawTime->Update())
		{
			m_minusRightPosX -= -kFallSpeed;
		}
		if (m_minusRightPosX >= 0)
		{
			// SE��炷
			if (!m_isPlayRankingSE)
			{
				SoundManager::GetInstance().Play("RankingDraw");
				m_isPlayRankingSE = true;
			}
			
			m_minusRightPosX = 0;
			// ��������̃{�^���������ꂽ�玟�ɍs��
			if (CheckHitKeyAll())
			{
				// ��ʂ��Â�����
				m_alpha = kSceneChangeAlpha;

				// ��
				m_isButtonDraw = true;

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
			m_minusButtonPosY = 0;
			m_isButtonFall = true;
		}

		// �{�^���������猻��Ă���
		if (m_isButtonFall)
		{			
			// �J�[�\���ړ�
			if (Pad::isTrigger(PAD_INPUT_UP))
			{
				// SE��炷
				SoundManager::GetInstance().Play("Select");

				m_buttonCount--;
				if (m_buttonCount < 0)
				{
					m_buttonCount = static_cast<int>(NextSelect::Num) - 1;
				}
			}
			if (Pad::isTrigger(PAD_INPUT_DOWN))
			{
				// SE��炷
				SoundManager::GetInstance().Play("Select");

				m_buttonCount++;
				if (m_buttonCount >= static_cast<int>(NextSelect::Num))
				{
					m_buttonCount = 0;
				}
			}

			// A�{�^����B�{�^���������ꂽ��
			// �����ꂽ�{�^���ɂ���ăV�[����J�ڂ���
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
			{
				// BGM������
				SoundManager::GetInstance().DesignationStopSound("ClearScene");

				
				if (m_buttonCount == static_cast<int>(NextSelect::GameScene))
				{
					// SE��炷
					SoundManager::GetInstance().Play("SceneChange");

					m_nextScene = NextScene::GameScene;
				}
				else if (m_buttonCount == static_cast<int>(NextSelect::Title))
				{
					// SE��炷
					SoundManager::GetInstance().Play("SceneChange");
					m_nextScene = NextScene::Title;
				}
				else
				{
					m_nextScene = NextScene::My;
				}
			}
		}
		break;

	default:
		break;
	}
}

void StageSceneManager::ClearSoundUpdate()
{
	

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
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �{�^���`��
	ButtonDraw();

#ifdef _DEBUG
	DrawString(0, 0, "GameClear", 0xffffff);
	DrawFormatString(0, 80, 0xffffff, "1�ʁF%d 2�ʁF%d 3��:%d",
		m_ranking[0] / 60, m_ranking[1] / 60, m_ranking[2] / 60);

	DrawFormatString(0, 140, 0xffffff, "�J�E���g�F%d", m_buttonCount);
#endif // _DEBUG
}

void StageSceneManager::ImageLoad()
{
	/*�摜�n���h���̃��[�h*/
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

void StageSceneManager::ImageDelete()
{
	/*�摜�̃f���[�g*/
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
			m_isMyRank = true;
		}
		else
		{
			RankTimeDraw(i);
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

void StageSceneManager::RankTimeDraw(int ranking)
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

	/*�^�C���̕`��*/
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

	/*�^�C���̕`��*/
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
	if (!m_isButtonDraw) return;

	if (m_buttonCount == static_cast<int>(NextSelect::GameScene))
	{
		m_titleChangeTextSize = kSelectButtonSize;
		m_gameSceneChangeTextSize = kButtonSize;
	}
	else if (m_buttonCount == static_cast<int>(NextSelect::Title))
	{
		m_titleChangeTextSize = kButtonSize;
		m_gameSceneChangeTextSize = kSelectButtonSize;
	}


	DrawRotaGraph(kButtonPosX, kButtonPosY1 - m_minusButtonPosY, 
		kButtonSize, 0.0, m_buttonH[0], true);

	DrawRotaGraph(kButtonPosX, kButtonPosY2 - m_minusButtonPosY,
		m_titleChangeTextSize, 0.0, m_buttonH[1], true);
	DrawRotaGraph(kButtonPosX, kButtonPosY3 - m_minusButtonPosY,
		m_gameSceneChangeTextSize, 0.0, m_buttonH[2], true);
}
