#include "DxLib.h"
#include "SceneRanking.h"
#include "../Util/Input.h"

#include "../Util/Ranking.h"
#include "../Util/Game.h"

namespace
{
	const char* const kBackgroundFileName = "Data/Img/Ranking/Background.png";	// �w�i�摜�t�@�C��
	const char* const kBackButtonFileName = "Data/Img/Rnking/BackButton.png";	// �߂�{�^���摜�t�@�C��

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

	// �e�L�X�g�{�b�N�X�摜�t�@�C��
	const char* const kTextBoxFileName = "Data/Img/Result/ResultTextBox1.png";

	// �����L���O�摜�t�@�C��
	const char* const kRankingFileName[3] =
	{
		"Data/Img/Ranking/Ranking1.png",
		"Data/Img/Ranking/Ranking2.png",
		"Data/Img/Ranking/Ranking3.png"
	};

	/*�����L���O�^�C�����W*/
	constexpr int kRankingMinutesFirstPosX = 1400;
	constexpr int kRankingMinutesSecondPosX = 1500;
	constexpr int kRankingSecondFirstPosX = 1600;
	constexpr int kRankingSecondSecondPosX = 1700;
	constexpr int kRankingTimePosY[3] = { 350,600,850 };
	constexpr int kRankingTimeColonPosX = 1550;
	constexpr float krankingTimeSize = 0.4f;

	constexpr int kColonArrayNum = 10;			// �^�C���̊Ԃɕ\������R�����̔z��ԍ�

}

SceneRanking::SceneRanking():
	m_backgroundH(-1)
{
	/*�摜�̃��[�h*/
	m_backgroundH = LoadGraph(kBackgroundFileName);

	m_pRanking = std::make_shared <Ranking>();
}

SceneRanking::~SceneRanking()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_backgroundH);
}

void SceneRanking::Init()
{
	// �����L���O�̎擾
	m_stage1Ranking = m_pRanking->GetRanking(Game::Stage::Stage1);
	m_stage2Ranking = m_pRanking->GetRanking(Game::Stage::Stage2);
}

std::shared_ptr<SceneBase> SceneRanking::Update(Input& input)
{
	return shared_from_this();
}

void SceneRanking::Draw()
{
	// �w�i�`��
	DrawGraph(0, 0, m_backgroundH, false);

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Ranking");
#endif // _DEBUG   
}

void SceneRanking::End()
{
}

void SceneRanking::RankTimeDraw(int ranking)
{
	int rankingTime = 0;
	/*�^�C���v�Z*/
	if (m_isStage1)
	{
		rankingTime = m_stage1Ranking[ranking] / 60;
	}
	else
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
