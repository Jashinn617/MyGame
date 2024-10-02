#include "DxLib.h"
#include "SceneRanking.h"
#include "SceneSelect.h"

#include "../Util/Pad.h"
#include "../Util/Ranking.h"
#include "../Util/Game.h"
#include "../Util/SoundManager.h"


#include <assert.h>

namespace
{
	/*�摜�t�@�C���p�X*/
	const char* const kBackgroundFileName = "Data/Img/Ranking/Background.png";	// �w�i
	const char* const kBackButtonFileName = "Data/Img/Ranking/BackButton.png";	// �߂�{�^��
	const char* const kArrowFileName = "Data/Img/Ranking/Arrow.png";			// ���
	const char* const kTextBoxFileName = "Data/Img/Result/ResultTextBox1.png";	// �e�L�X�g�{�b�N�X
	// �����L���O�摜
	const char* const kRankingFileName[3] =
	{
		"Data/Img/Ranking/Ranking1.png",
		"Data/Img/Ranking/Ranking2.png",
		"Data/Img/Ranking/Ranking3.png"
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
	// �e�L�X�g�摜
	const char* const kTextFileName[2] =
	{
		"Data/Img/Ranking/RankingText1.png",
		"Data/Img/Ranking/RankingText2.png",
	};

	/*���W*/
	// �����L���O�^�C��
	constexpr int kRankingMinutesFirstPosX = 775;
	constexpr int kRankingMinutesSecondPosX = 875;
	constexpr int kRankingSecondFirstPosX = 975;
	constexpr int kRankingSecondSecondPosX = 1075;
	constexpr int kRankingTimePosY[3] = { 350,600,850 };
	constexpr int kRankingTimeColonPosX = 925;
	// �����L���O���W
	constexpr int kRankingPosX = 584;
	constexpr int kRnakingPosY1 = 340;
	constexpr int kRnakingPosY2 = 590;
	constexpr int kRnakingPosY3 = 840;
	// �e�L�X�g���W
	constexpr int kTextPosX = 850;
	constexpr int kTextPosY = 165;
	// �{�^�����W
	constexpr int kButtonPosX = 1600;
	constexpr int kButtonPosY = 900;
	// �����W
	constexpr int kArrowPosX = 1500;
	constexpr int kArrowPosY = 500;
	// �{�b�N�X���W
	constexpr int kBoxPosX = 835;
	constexpr int kBoxPosY = 505;

	/*�T�C�Y*/
	constexpr float kRankingSize = 0.3f;		// �����L���O
	constexpr float krankingTimeSize = 0.4f;	// �����L���O�^�C��
	constexpr float kTextSize = 0.9f;			// �e�L�X�g
	constexpr float kButtonSize = 0.9f;			// �{�^��
	constexpr float kArrowSize = 0.4f;			// ���
	constexpr float kBoxSize = 0.95f;			// �{�b�N�X

	constexpr float kArrowAngle = 60.0f * DX_PI_F / 120.0f;	 // ���̊p�x

	constexpr int kColonArrayNum = 10;			// �^�C���̊Ԃɕ\������R�����̔z��ԍ�
	constexpr int kRankingNum = 3;				// �����L���O�̐�
	constexpr int kBoxAlpha = 200;				// �{�b�N�X�̓����x
	constexpr float kButtonSinSpeed = 0.07f;	// �{�^���̊g�k�X�s�[�h
	constexpr float kButtonAnimSwing = 0.03f;	// �{�^���̊g�k��
}

SceneRanking::SceneRanking():
	m_backgroundH(-1),
	m_isStage1(true),
	m_isArrow(false),
	m_arrowSize(0),
	m_backButtonSize(0),
	m_expansionButtonSize(0),
	m_buttonSinCount(0),
	m_buttonSinSize(0)
{
	/*�摜�̃��[�h*/
	LoadImg();

	m_pRanking = std::make_shared <Ranking>();
}

SceneRanking::~SceneRanking()
{
	/*�摜�̃f���[�g*/
	DeleteImg();
}

void SceneRanking::Init()
{
	// �����L���O�̎擾
	m_stage1Ranking = m_pRanking->GetRanking(Game::Stage::Stage1);
	m_stage2Ranking = m_pRanking->GetRanking(Game::Stage::Stage2);

	// SE��炷
	SoundManager::GetInstance().Play("DoorOpen");
	// BGM��炷
	SoundManager::GetInstance().Play("RankingScene");
}

std::shared_ptr<SceneBase> SceneRanking::Update()
{
	// �t�F�[�h�X�V
	UpdateFade();

	// �㉺�{�^���������ꂽ�ꍇ
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		// SE��炷
		SoundManager::GetInstance().Play("Select");
		// �{�^����؂�ւ���
		m_isArrow = !m_isArrow;
	}

	// ��󂪑I������Ă����Ԃ�A�{�^����B�{�^����������Ă�����
	if (m_isArrow && (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2)))
	{
		// SE��炷
		SoundManager::GetInstance().Play("Decide");
		// �����L���O��؂�ւ���
		m_isStage1 = !m_isStage1;
	}
	// ��󂪑I������Ă��Ȃ���Ԃ�A�{�^����B�{�^����������Ă�����
	else if (!m_isArrow && (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2)))
	{
		// SE��炷
		SoundManager::GetInstance().Play("DoorClose");
		// �Z���N�g�V�[���ɖ߂�
		return std::make_shared<SceneSelect>();
	}

	return shared_from_this();
}

void SceneRanking::Draw()
{
	// �w�i�`��
	DrawGraph(0, 0, m_backgroundH, false);

	// �{�b�N�X�`��
	// �s�����x������������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kBoxAlpha);
	DrawRotaGraph(kBoxPosX, kBoxPosY, kBoxSize, 0.0f, m_textBoxH, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �{�^���`��
	DrawButton();

	// �e�L�X�g�`��
	if (m_isStage1)	 // �X�e�[�W1
	{
		DrawRotaGraph(kTextPosX, kTextPosY, kTextSize, 0.0f,
			m_textH[0], true);
	}
	else	// �X�e�[�W2
	{
		DrawRotaGraph(kTextPosX, kTextPosY, kTextSize, 0.0f,
			m_textH[1], true);
	}

	// �����L���O�`��
	DrawRanking();


#ifdef _DEBUG
	// �V�[�����`��
	DrawFormatString(0, 0, 0xffffff, "Ranking");
#endif // _DEBUG   

	// �t�F�[�h�`��
	DrawFade();
}

void SceneRanking::End()
{
	// BGM���~�߂�
	SoundManager::GetInstance().DesignationStopSound("RankingScene");
}

void SceneRanking::DrawRankingTime(int ranking)
{
	int rankingTime = 0;
	/*�^�C���v�Z*/
	if (m_isStage1)		// �X�e�[�W1
	{
		rankingTime = m_stage1Ranking[ranking] / 60;
	}
	else	// �X�e�[�W2
	{
		rankingTime = m_stage2Ranking[ranking] / 60;
	}
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
		m_rankingTimeNumH[kColonArrayNum], true);
	DrawRotaGraph(kRankingSecondFirstPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[secondTimeFirst], true);
	DrawRotaGraph(kRankingSecondSecondPosX, kRankingTimePosY[ranking],
		krankingTimeSize, 0.0f,
		m_rankingTimeNumH[secondTimeSecond], true);
}

void SceneRanking::DrawRanking()
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

	// �����L���O�^�C���̕`��
	for (int i = 0; i < kRankingNum; i++)
	{
		DrawRankingTime(i);
	}
}

void SceneRanking::DrawButton()
{
	// �g�k����
	m_buttonSinCount += kButtonSinSpeed;
	m_expansionButtonSize = sinf(m_buttonSinCount) * kButtonAnimSwing;

	if (m_isArrow)	// ���̑I��
	{
		m_arrowSize = m_expansionButtonSize + kArrowSize;
		m_backButtonSize = kButtonSize;
	}
	else
	{
		m_arrowSize = kArrowSize;
		m_backButtonSize = m_expansionButtonSize + kButtonSize;
	}

	// �{�^���`��
	DrawRotaGraph(kButtonPosX, kButtonPosY, m_backButtonSize, 0.0f, m_buttonH, true);

	// ���`��
	DrawRotaGraph(kArrowPosX, kArrowPosY, m_arrowSize, 0.0f, m_arrowH, true);
}

void SceneRanking::LoadImg()
{
	// �摜���[�h�����s���Ă�����~�߂�
	m_backgroundH = LoadGraph(kBackgroundFileName);
	assert(m_backgroundH != -1);
	m_textBoxH = LoadGraph(kTextBoxFileName);
	assert(m_textBoxH != -1);
	m_buttonH = LoadGraph(kBackButtonFileName);
	assert(m_buttonH != -1);
	m_arrowH = LoadGraph(kArrowFileName);
	assert(m_arrowH != -1);
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		m_rankingTimeNumH[i] = LoadGraph(kRankingTimeNumFileName[i]);
		assert(m_rankingTimeNumH[i] != -1);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		m_rankingH[i] = LoadGraph(kRankingFileName[i]);
		assert(m_rankingH[i] != -1);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		m_textH[i] = LoadGraph(kTextFileName[i]);
		assert(m_textH[i] != -1);
	}
}

void SceneRanking::DeleteImg()
{
	DeleteGraph(m_backgroundH);
	DeleteGraph(m_textBoxH);
	DeleteGraph(m_buttonH);
	DeleteGraph(m_arrowH);
	for (int i = 0; i < m_rankingTimeNumH.size(); i++)
	{
		DeleteGraph(m_rankingTimeNumH[i]);
	}
	for (int i = 0; i < m_rankingH.size(); i++)
	{
		DeleteGraph(m_rankingH[i]);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		DeleteGraph(m_textH[i]);
	}
}
