#include "DxLib.h"
#include "Result.h"

#include "../Image/ExpansionImage.h"
#include "../Image/FadeImage.h"

#include "../Util/Easing.h"
#include "../Util/Time.h"
#include "../Util/Pad.h"
#include "../Util/SoundManager.h"

#include <cassert>

namespace
{
	// �X�e�[�W���Ƃ̃N���A���Ԃ̊
	constexpr double kResultDataTable[static_cast<int>(Game::Stage::StageNum)] =
	{
		0,
		0,
		0,
		0
	};

	const char* const kTimeFileName = "Data/Img/Result/ClearTimeNum/ClearTime.png";

	// �����̉摜�n���h��
	const char* const kMyTimeNumFileName[10] =
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
	};

	// �����N�̉摜�n���h��
	const char* const kRankImage[static_cast<int>(Result::Rank::RankNum)] =
	{
		"Data/Img/Result/Rank/S.png",
		"Data/Img/Result/Rank/A.png",
		"Data/Img/Result/Rank/B.png",
		"Data/Img/Result/Rank/C.png"
	};

	// �摜�̃f�[�^
	const char* const kResultImageName = "";
	const char* const kEndImageName = "";

	// �`��ʒu
	constexpr float kStageClearTimePosY = 150.0f;
	constexpr float kMaxComboCountPosY = 300.0f;
	constexpr float kTotalDamagePosY = 450.0f;
	constexpr float kRankPosY = 650.0f;

	// �����̕`��ʒu
	constexpr float kStartPosX = 1200.0f;

	// �ڕW�̕`��ʒu
	constexpr float kEndPosX = 160.0f;

	// �C�[�W���O����
	constexpr float kEasingTime = 60.0f;
	constexpr float kOneFrame = 1.0f;

	// ���U���g��ʂ��o��������܂ł̎���
	constexpr int kResultTime = 250;

	// ���U���g��ʂ̑傫��
	constexpr int kResultImageSizeX = 1080;
	constexpr int kResultImageSizeY = 702;
	
	// ���U���g��ʂ̕`��ʒu
	constexpr int kResultImagePosX = 50;
	constexpr int kResultImagePosY = 300;
	
	// �����N�̕`��ʒu
	constexpr int kRankImagePosX = 740;
	constexpr int kRankImagePosY = 300;

	// �����N�摜�̃A���t�@�l�̑�����
	constexpr int kRankAlphaAdd = 8;

	// �����N�p��SE��炷�܂ł̎���
	constexpr int kRankSound = 30;
}

Result::Result(int stageClearTime, Game::Stage stage):
	m_timeImageH(-1),
	m_clearTime(stageClearTime / 60),
	m_isEnd(false),
	m_clearTimePos{kStartPosX,kStageClearTimePosY},
	m_rankPos{kStartPosX,kRankPosY},
	m_rank(Result::Rank::RankNum)
{
	/*�|�C���^�쐬*/
	m_pResultTime = std::make_shared<Time>(kResultTime);
	

	// �����N�v�Z
	CalcRank();

	// ���U���g�摜�̐���
	m_timeImageH = LoadGraph(kTimeFileName);

	// �����̉摜�n���h�����[�h
	for (int i = 0; i < m_timeNumH.size(); i++)
	{
		m_timeNumH[i] = LoadGraph(kMyTimeNumFileName[i]);
	}
	// �����N�̉摜�n���h�����[�h
	for (int i = 0; i < m_rankH.size(); i++)
	{
		m_rankH[i] = LoadGraph(kRankImage[i]);
	}

}

Result::~Result()
{
	// ���U���g��ʂ̃f���[�g
	DeleteGraph(m_timeImageH);
	for (int i = 0; i < m_timeNumH.size(); i++)
	{
		DeleteGraph(m_timeNumH[i]);
	}
	for (int i = 0; i < m_rankH.size(); i++)
	{
		DeleteGraph(m_rankH[i]);
	}
}

void Result::Update()
{
	// ���U���g��ʂ��o��������܂�
	if (!m_pResultTime->Update())return;

}

void Result::Draw()
{
	/*�^�C���v�Z*/
	// ����
	int clearMinutesTime = m_clearTime / 60;
	int minutesTimeFirst = clearMinutesTime / 10;	// ��̈�
	int minutesTimeSecond = clearMinutesTime % 10;	// �\�̈�
	// �b��
	int clearSecondTime = m_clearTime % 60;
	int secondTimeFirst = clearSecondTime / 10;		// ��̈�
	int secondTimeSecond = clearSecondTime % 10;	// �\�̈�

	// �N���A�^�C���̕`��
	DrawRotaGraph(200, 300,
		0.5f, 0.0f,
		m_timeNumH[minutesTimeFirst], true);
	DrawRotaGraph(350, 300,
		0.5f, 0.0f,
		m_timeNumH[minutesTimeSecond], true);
	DrawRotaGraph(650, 300,
		0.5f, 0.0f,
		m_timeNumH[secondTimeFirst], true);
	DrawRotaGraph(800, 300,
		0.5f, 0.0f,
		m_timeNumH[secondTimeSecond], true);

	DrawRotaGraph(500, 300,
		0.5f, 0.0f,
		m_timeImageH, true);

	// �����N�̕`��
	DrawRotaGraph(500, 750,
		0.8f, 0.0f,
		m_rankH[0], true);

	// �����L���O�̕`��

#ifdef _DEBUG

	DrawFormatString(0, 20, 0xffffff, "�N���A�^�C���F%d��%d�b", clearMinutesTime, clearSecondTime);

#endif // _DEBUG
}

void Result::CalcRank()
{
}