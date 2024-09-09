#include "DxLib.h"
#include "SceneSelect.h"
#include "SceneRanking.h"
#include "SceneStage.h"

#include "../Util/SoundManager.h"
#include "../Util/Input.h"
#include "../Util/Pad.h"
#include "../Util/Game.h"

#include <cassert>

namespace
{
	// �摜�̃t�@�C���p�X
	const char* const kBackGroundFileName = "Data/Img/Select/Background.png";

	const char* const kBackSideFileName = "Data/Img/Select/BackSide.png";

	// �Z���N�g�{�b�N�X�t�@�C���p�X
	const char* const kSelectBoxFileName[4] =
	{
		"Data/Img/Select/Stage1Box.png",
		"Data/Img/Select/Stage2Box.png",
		"Data/Img/Select/OnlineRankingBox.png",
		"Data/Img/Select/GameEndBox.png"
	};

	// �e�L�X�g�t�@�C���p�X
	const char* const kTextFileName[4] =
	{
		"Data/Img/Select/Text1.png",
		"Data/Img/Select/Text2.png",
		"Data/Img/Select/Text3.png",
		"Data/Img/Select/Text4.png",
	};

	constexpr int kIndexBackNum = 2;	// �X�N���[���ɕK�v�Ȕw�i�̐�

	constexpr int kScrollSpeed = 1;		// �X�N���[���̃X�s�[�h
	constexpr int kTextScrollSpeed = 2;		// �X�N���[���̃X�s�[�h

	constexpr int kBackSideRightPosX = Game::kScreenWidth - 220;
	constexpr int kBackSideLeftPosX = -80;

	/*�Z���N�g�{�b�N�X�̍��W*/
	constexpr int kSelectBoxPosX1 = 600;
	constexpr int kSelectBoxPosX2 = 1300;
	constexpr int kSelectBoxPosX3 = 700;
	constexpr int kSelectBoxPosX4 = 1100;
	constexpr int kUpSelectBoxPosY = 400;		// ��̃Z���N�g�{�b�N�X��Y�ʒu
	constexpr int kDownSelectBoxPosY = 820;		// ���̃Z���N�g�{�b�N�X��Y�ʒu

	constexpr float kUpBoxSize = 0.7f;
	constexpr float kDownBoxSize = 0.6f;

	constexpr float kBoxSinSpeed = 0.07f;	// �{�b�N�X���g�k����X�s�[�h
	constexpr float kBoxAnimSwing = 0.03f;	// �{�b�N�X�̊g�k��

	constexpr int kInfoBackAlpha = 200;
}

SceneSelect::SceneSelect() :
	m_backgroundH(-1),
	m_scrollX(0),
	m_scrollY(0),
	m_textWidth(0),
	m_textHeight(0),
	m_backWidth(0),
	m_backHeight(0),
	m_isUp(true),
	m_isLeft(true),
	m_upBoxSize1(0.0f),
	m_upBoxSize2(0.0f),
	m_downBoxSize1(0.0f),
	m_downBoxSize2(0.0f),
	m_expansionBoxSize(0.0f),
	m_boxSinCount(0.0f),
	m_boxSinSize(0.0f),
	m_next(NextScene::My)
{
	/*�摜�n���h���̃��[�h*/
	m_backgroundH = LoadGraph(kBackGroundFileName);
	assert(m_backgroundH != -1);
	m_backSideH = LoadGraph(kBackSideFileName);
	assert(m_backSideH != -1);
	for (int i = 0; i < m_SelectBoxH.size(); i++)
	{
		m_SelectBoxH[i] = LoadGraph(kSelectBoxFileName[i]);
		assert(m_SelectBoxH[i] != -1);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		m_textH[i] = LoadGraph(kTextFileName[i]);
	}

	// �w�i�摜�̃T�C�Y�̎擾
	GetGraphSize(m_backgroundH, &m_backWidth, &m_backHeight);
	GetGraphSize(m_textH[0], &m_textWidth, &m_textHeight);
}

SceneSelect::~SceneSelect()
{
	/*�摜�n���h���̃f���[�g*/
	DeleteGraph(m_backgroundH);
	DeleteGraph(m_backSideH);
	for (int i = 0; i < m_SelectBoxH.size(); i++)
	{
		DeleteGraph(m_SelectBoxH[i]);
	}
	for (int i = 0; i < m_textH.size(); i++)
	{
		DeleteGraph(m_textH[i]);
	}
}

void SceneSelect::Init()
{
	/*BGM�𗬂�*/
	SoundManager::GetInstance().Play("SelectScene");
}

std::shared_ptr<SceneBase> SceneSelect::Update(Input& input)
{
	UpdateFade();

	// �w�i�̃X�N���[��
	m_scrollX += kScrollSpeed;
	// �����̃X�N���[��
	m_scrollY += kTextScrollSpeed;

	// �㉺�̑I���̓���ւ�
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		SoundManager::GetInstance().Play("Select");
		m_scrollY = 0;
		m_isUp = !m_isUp;
	}
	// ���E�̓���ւ�
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		SoundManager::GetInstance().Play("Select");
		m_scrollY = 0;
		m_isLeft = !m_isLeft;
	}

	SelectBoxUpdate();


	SelectUpdate();

	switch (m_next)
	{
	case SceneSelect::NextScene::My:
		return shared_from_this();
		break;

	case SceneSelect::NextScene::Stage1:
		return std::make_shared<SceneStage>(Game::Stage::Stage1);
		break;

	case SceneSelect::NextScene::Stage2:
		return std::make_shared<SceneStage>(Game::Stage::Stage2);
		break;

	case SceneSelect::NextScene::Ranking:
		return std::make_shared<SceneRanking>();
		break;

	case SceneSelect::NextScene::End:
		DxLib_End();
		break;

	default:
		break;
	}

	return shared_from_this();
}

void SceneSelect::Draw()
{
	BackDraw();

	InfoDraw();

	SelectBoxDraw();

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Select");
	if (m_isUp) DrawFormatString(0, 20, 0x000000, "��");
	if (!m_isUp) DrawFormatString(0, 20, 0x000000, "��");
	if (m_isLeft) DrawFormatString(0, 40, 0x000000, "��");
	if (!m_isLeft) DrawFormatString(0, 40, 0x000000, "�E");
	
#endif // _DEBUG   

	DrawFade();
}

void SceneSelect::End()
{
	SoundManager::GetInstance().DesignationStopSound("SelectScene");
}

void SceneSelect::SelectUpdate()
{
	// A�{�^����B�{�^���������ꂽ�玟�̃V�[���ɑJ�ڂ���
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
	{
		// SE��炷
		SoundManager::GetInstance().Play("Decide");

		if (m_isUp)	// ��̑I�����Ă���
		{
			if (m_isLeft)	// ����I�����Ă���
			{
				m_next = NextScene::Stage1;
			}
			else
			{
				m_next = NextScene::Stage2;
			}

		}
		else	// ���̑I�������Ă���
		{
			if (m_isLeft)	// ����I�����Ă���
			{
				m_next = NextScene::Ranking;
			}
			else
			{
				m_next = NextScene::End;
			}
		}
	}
	else
	{
		m_next = NextScene::My;
	}
}

void SceneSelect::SelectBoxUpdate()
{
	// ���ݑI�΂�Ă���{�b�N�X���g�k����

	// �g�k����
	m_boxSinCount += kBoxSinSpeed;
	m_expansionBoxSize = sinf(m_boxSinCount) * kBoxAnimSwing;

	if (m_isUp)	// ��̑I�����Ă���
	{
		if (m_isLeft)	// ����I�����Ă���
		{
			m_upBoxSize1 = m_expansionBoxSize + kUpBoxSize;
			m_upBoxSize2 = kUpBoxSize;
			m_downBoxSize1 = kDownBoxSize;
			m_downBoxSize2 = kDownBoxSize;
		}
		else
		{
			m_upBoxSize1 = kUpBoxSize;
			m_upBoxSize2 = m_expansionBoxSize + kUpBoxSize;
			m_downBoxSize1 = kDownBoxSize;
			m_downBoxSize2 = kDownBoxSize;
		}

	}
	else	// ���̑I�������Ă���
	{
		if (m_isLeft)	// ����I�����Ă���
		{
			m_upBoxSize1 = kUpBoxSize;
			m_upBoxSize2 = kUpBoxSize;
			m_downBoxSize1 = m_expansionBoxSize + kDownBoxSize;
			m_downBoxSize2 = kDownBoxSize;
		}
		else
		{
			m_upBoxSize1 = kUpBoxSize;
			m_upBoxSize2 = kUpBoxSize;
			m_downBoxSize1 = kDownBoxSize;
			m_downBoxSize2 = m_expansionBoxSize + kDownBoxSize;
		}
	}

}

void SceneSelect::BackDraw()
{
	// �w�i���X�N���[��������
	int scrollBack = m_scrollX % m_backWidth;
	for (int index = 0; index < kIndexBackNum; index++)
	{
		DrawGraph(-scrollBack + index * m_backWidth,
			0, m_backgroundH, true);
	}
}

void SceneSelect::InfoDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kInfoBackAlpha);
	DrawGraph(kBackSideRightPosX, 0, m_backSideH, false);
	DrawGraph(kBackSideLeftPosX, 0, m_backSideH, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �������X�N���[����������
	int scroll = m_scrollY % m_textHeight;
	for (int index = 0; index < kIndexBackNum; index++)
	{
		if (m_isUp)	// ��̑I�����Ă���
		{
			if (m_isLeft)	// ����I�����Ă���
			{
				DrawGraph(kBackSideRightPosX,
					-scroll + index * m_textHeight,
					m_textH[0], true);
				DrawGraph(0,
					-scroll + index * m_textHeight,
					m_textH[0], true);
			}
			else
			{
				DrawGraph(kBackSideRightPosX,
					-scroll + index * m_textHeight,
					m_textH[1], true);
				DrawGraph(0,
					-scroll + index * m_textHeight,
					m_textH[1], true);
			}

		}
		else	// ���̑I�������Ă���
		{
			if (m_isLeft)	// ����I�����Ă���
			{
				DrawGraph(kBackSideRightPosX,
					-scroll + index * m_textHeight,
					m_textH[2], true);
				DrawGraph(0,
					-scroll + index * m_textHeight,
					m_textH[2], true);
			}
			else
			{
				DrawGraph(kBackSideRightPosX,
					-scroll + index * m_textHeight,
					m_textH[3], true);
				DrawGraph(0,
					-scroll + index * m_textHeight,
					m_textH[3], true);
			}
		}
	}

}

void SceneSelect::SelectBoxDraw()
{
	DrawRotaGraph(kSelectBoxPosX1, kUpSelectBoxPosY,
		m_upBoxSize1, 0.0f, m_SelectBoxH[0], true);
	DrawRotaGraph(kSelectBoxPosX2, kUpSelectBoxPosY,
		m_upBoxSize2, 0.0f, m_SelectBoxH[1], true);

	DrawRotaGraph(kSelectBoxPosX1, kDownSelectBoxPosY,
		m_downBoxSize1, 0.0f, m_SelectBoxH[2], true);
	DrawRotaGraph(kSelectBoxPosX2, kDownSelectBoxPosY,
		m_downBoxSize2, 0.0f, m_SelectBoxH[3], true);
}
