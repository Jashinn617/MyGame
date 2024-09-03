#include "DxLib.h"

#include "SceneGameClear.h"
#include "StageSceneManager.h"

#include "../Util/Time.h"
#include "../Util/Ranking.h"
#include "../Util/SoundManager.h"



#include <cassert>

namespace
{
	// �X�e�[�W���Ƃ̃N���A���Ԃ̊
	constexpr double kResultDataTable[static_cast<int>(Game::Stage::StageNum)] =
	{
		3600,		// �e�X�g
		7200,		// �X�e�[�W1
		0,
		0
	};

	const char* const kBackgroundFikeName = "Data/Img/Result/Background.png";	// �w�i�摜�t�@�C��

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
	const char* const kRankFileName[static_cast<int>(SceneGameClear::Rank::RankNum)] =
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
	const char* const kButtonFileName[2] =
	{
		"Data/Img/Result/StageBackButton.png",
		"Data/Img/Result/TitleBackButton.png"
	};

	/*�e�L�X�g���W*/
	constexpr int kTextPosX1 = static_cast<int>(Game::kScreenWidth * 0.28f);
	constexpr int kTextPosX2 = static_cast<int>(Game::kScreenWidth * 0.75f);
	constexpr int kTextPosY1 = static_cast<int>(Game::kScreenHeight * 0.13f);
	constexpr int kTextPosY2 = static_cast<int>(Game::kScreenHeight * 0.42f);
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
	constexpr float kRankSize = 0.8f;	// �����N�T�C�Y
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
	
	constexpr int kColonNum = 10;
	constexpr int kRankingNum = 3;
	constexpr int kImageDrawTime = 120;	// �摜���\�������܂ł̎���
	constexpr int kFallSpeed = 20;		// �摜�̗������x
}

SceneGameClear::SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager, Game::Stage stageKind):
	m_backgroundH(-1),
	m_clearTime(0),
	m_isSceneEnd(false),
	m_isNextScene(false),
	m_isMyRank(false),
	m_isFall(true),
	m_stageKind(stageKind),
	m_pStageSceneManager(pStageSceneManager)
{
	m_pImageDrawTime = std::make_shared<Time>(kImageDrawTime);

	// �N���A�^�C��
	m_clearTime = m_pStageSceneManager->GetGameClearTime();

	/*�摜�n���h���̃��[�h*/
	m_backgroundH = LoadGraph(kBackgroundFikeName);
	assert(m_backgroundH != -1);
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

SceneGameClear::~SceneGameClear()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_backgroundH);
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

void SceneGameClear::Init()
{
	// �����L���O�̍X�V�A�擾
	m_pRanking->UpdateRanking(m_stageKind, m_clearTime);
	m_ranking = m_pRanking->GetRanking(m_stageKind);

	// �O�̃V�[���̃T�E���h���~�߂�
	SoundManager::GetInstance().StopSound();
}

std::shared_ptr<SceneBase> SceneGameClear::Update(Input& input)
{
	m_plusPosY -= kFallSpeed;
	if (m_plusPosY <= 0)
	{
		m_plusPosY = 0;
		m_isFall = false;
	}


	return shared_from_this();
}

void SceneGameClear::Draw()
{
#ifdef _DEBUG
	DrawString(0, 0, "GameClear", 0xffffff);
	DrawFormatString(0, 80, 0xffffff, "1�ʁF%d 2�ʁF%d 3��:%d",
		m_ranking[0] / 60, m_ranking[1] / 60, m_ranking[2] / 60);
#endif // _DEBUG

	// �w�i�`��
	DrawGraph(0, 0, m_backgroundH, false);

	// �e�L�X�g�`��
	TextDraw();
	// �^�C���`��
	TimeDraw();
	// �����L���O�`��
	RankingDraw();
	// �����N�`��
	RankDraw();
	// �{�^���`��
	ButtonDraw();
}

void SceneGameClear::End()
{
	/*��������*/
}

void SceneGameClear::TextDraw()
{
	/*�e�L�X�g�{�b�N�X�̕`��*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kTextBoxAlpha);
	DrawRotaGraph(kTextBoxPosX1, kTextBoxPosY,
		1.0f, 0.0f,
		m_textBoxH[0], true);
	DrawRotaGraph(kTextBoxPosX2, kTextBoxPosY,
		1.0f, 0.0f,
		m_textBoxH[1], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*�e�L�X�g�̕`��*/
	DrawRotaGraph(kTextPosX1, kTextPosY1,
		1.0f, 0.0f,
		m_textH[0], true);
	DrawRotaGraph(kTextPosX1, kTextPosY2,
		1.0f, 0.0f,
		m_textH[1], true);
	DrawRotaGraph(kTextPosX2, kTextPosY1,
		1.0f, 0.0f,
		m_textH[2], true);
}

void SceneGameClear::TimeDraw()
{
	/*�^�C���v�Z*/
	int clearTime = m_clearTime / 60;
	// ����
	int clearMinutesTime = clearTime / 60;
	int minutesTimeFirst = clearMinutesTime / 10;	// ��̈�
	int minutesTimeSecond = clearMinutesTime % 10;	// �\�̈�
	// �b��
	int clearSecondTime = clearTime % 60;
	int secondTimeFirst = clearSecondTime / 10;		// ��̈�
	int secondTimeSecond = clearSecondTime % 10;	// �\�̈�

	/*�N���A�^�C���̕`��*/
	DrawRotaGraph(kClearMinutesFirstPosX, kClearTimePosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeFirst], true);
	DrawRotaGraph(kClearMinutesSecondPosX, kClearTimePosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeSecond], true);
	DrawRotaGraph(kClearTimeColonPosX, kClearTimePosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[kColonNum], true);
	DrawRotaGraph(kClearSecondFirstPosX, kClearTimePosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kClearSecondSecondPosX, kClearTimePosY,
		kClearTimeSize, 0.0f,
		m_myTimeNumH[secondTimeSecond], true);
}

void SceneGameClear::RankingDraw()
{
	/*�����L���O�̕`��*/
	DrawRotaGraph(kRankingPosX, kRnakingPosY1,
		kRankingSize, 0.0f,
		m_rankingH[0], true);
	DrawRotaGraph(kRankingPosX, kRnakingPosY2,
		kRankingSize, 0.0f,
		m_rankingH[1], true);
	DrawRotaGraph(kRankingPosX, kRnakingPosY3,
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

void SceneGameClear::RankDraw()
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
	DrawRotaGraph(kRankPosX, kRankPosY,
		kRankSize, 0.0f,
		m_rankH[static_cast<int>(m_rank)], true);
}

void SceneGameClear::RankTimeDraw(int ranking)
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
	DrawRotaGraph(kRankingMinutesFirstPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[minutesTimeFirst], true);
	DrawRotaGraph(kRankingMinutesSecondPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[minutesTimeSecond], true);
	DrawRotaGraph(kRankingTimeColonPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[kColonNum], true);
	DrawRotaGraph(kRankingSecondFirstPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kRankingSecondSecondPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[secondTimeSecond], true);
}

void SceneGameClear::MyRankTimeDraw(int ranking)
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
	DrawRotaGraph(kRankingMinutesFirstPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeFirst], true);
	DrawRotaGraph(kRankingMinutesSecondPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[minutesTimeSecond], true);
	DrawRotaGraph(kRankingTimeColonPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[kColonNum], true);
	DrawRotaGraph(kRankingSecondFirstPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kRankingSecondSecondPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_myTimeNumH[secondTimeSecond], true);
}

void SceneGameClear::ButtonDraw()
{
	// �摜�̗������͕\�������Ȃ�
	if (m_isFall) return;
}

void SceneGameClear::ChangeMainScene()
{
}

void SceneGameClear::ChangeTitleScene()
{
}
