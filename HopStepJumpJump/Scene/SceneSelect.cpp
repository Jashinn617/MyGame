#include "DxLib.h"
#include "SceneSelect.h"
#include "SceneRanking.h"
#include "SceneStage.h"

#include "../Util/SoundManager.h"
#include "../Util/Pad.h"
#include "../Util/Game.h"

#include <cassert>

namespace
{
	/*�摜�̃t�@�C���p�X*/
	const char* const kBackGroundFileName = "Data/Img/Select/Background.png";	// �w�i
	const char* const kBackSideFileName = "Data/Img/Select/BackSide.png";		// ��ʉ��̍��{�b�N�X
	// �Z���N�g�{�b�N�X
	const char* const kSelectBoxFileName[4] =
	{
		"Data/Img/Select/Stage1Box.png",
		"Data/Img/Select/Stage2Box.png",
		"Data/Img/Select/OnlineRankingBox.png",
		"Data/Img/Select/GameEndBox.png"
	};
	// �e�L�X�g
	const char* const kTextFileName[4] =
	{
		"Data/Img/Select/Text1.png",
		"Data/Img/Select/Text2.png",
		"Data/Img/Select/Text3.png",
		"Data/Img/Select/Text4.png",
	};

	constexpr int kIndexBackNum = 2;								// �X�N���[���ɕK�v�Ȕw�i�̐�
	constexpr int kScrollSpeed = 1;									// �X�N���[���̃X�s�[�h
	constexpr int kTextScrollSpeed = 2;								// �X�N���[���̃X�s�[�h
	constexpr int kBackSideRightPosX = Game::kScreenWidth - 220;	// ��ʉ����{�b�N�X�̍��WX
	constexpr int kBackSideLeftPosX = -80;							// ��ʉ����{�b�N�X�̍��WY

	/*�Z���N�g�{�b�N�X���W*/
	constexpr int kSelectBoxPosX1 = 600;
	constexpr int kSelectBoxPosX2 = 1300;
	constexpr int kSelectBoxPosX3 = 700;
	constexpr int kSelectBoxPosX4 = 1100;
	constexpr int kUpSelectBoxPosY = 400;
	constexpr int kDownSelectBoxPosY = 820;

	/*�{�b�N�X�T�C�Y*/
	constexpr float kUpBoxSize = 0.7f;
	constexpr float kDownBoxSize = 0.6f;

	constexpr float kBoxSinSpeed = 0.07f;	// �{�b�N�X���g�k����X�s�[�h
	constexpr float kBoxAnimSwing = 0.03f;	// �{�b�N�X�̊g�k��

	constexpr int kInfoBackAlpha = 200;		// ��ʉ����{�b�N�X�̕s�����x
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
	LoadImg();

	// �w�i�摜�̃T�C�Y�̎擾
	GetGraphSize(m_backgroundH, &m_backWidth, &m_backHeight);
	// �e�L�X�g�摜�T�C�Y�̎擾
	GetGraphSize(m_textH[0], &m_textWidth, &m_textHeight);
}

SceneSelect::~SceneSelect()
{
	/*�摜�n���h���̃f���[�g*/
	DeleteImg();
}

void SceneSelect::Init()
{
	/*BGM�𗬂�*/
	SoundManager::GetInstance().Play("SelectScene");
}

std::shared_ptr<SceneBase> SceneSelect::Update()
{
	// �t�F�[�h�X�V
	UpdateFade();

	// �w�i�̃X�N���[��
	m_scrollX += kScrollSpeed;
	// �����̃X�N���[��
	m_scrollY += kTextScrollSpeed;

	// �㉺�{�^���������ꂽ�ꍇ
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		SoundManager::GetInstance().Play("Select");
		m_scrollY = 0;
		// �㉺�̑I�������ւ���
		m_isUp = !m_isUp;
	}
	// ���E���Ԃ������ꂽ�ꍇ
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		SoundManager::GetInstance().Play("Select");
		m_scrollY = 0;
		// ���E�̑I�������ւ���
		m_isLeft = !m_isLeft;
	}
	// �{�b�N�X�̍X�V
	SelectBoxUpdate();
	// �Z���N�g�̍X�V
	SelectUpdate();

	// ���̃V�[���ւ̑J�ڏ���
	switch (m_next)
	{
	case SceneSelect::NextScene::My:
		return shared_from_this();
		break;
	case SceneSelect::NextScene::Stage1:
		// �X�e�[�W1�ɑJ�ڂ���
		return std::make_shared<SceneStage>(Game::Stage::Stage1);
		break;
	case SceneSelect::NextScene::Stage2:
		// �X�e�[�W2�ɑJ�ڂ���
		return std::make_shared<SceneStage>(Game::Stage::Stage2);
		break;
	case SceneSelect::NextScene::Ranking:
		// �����L���O�V�[���ɑJ�ڂ���
		return std::make_shared<SceneRanking>();
		break;
	case SceneSelect::NextScene::End:
		// �Q�[���I��
		DxLib_End();
		break;
	default:
		break;
	}

	return shared_from_this();
}

void SceneSelect::Draw()
{
	// �w�i�`��
	BackDraw();
	// �����e�L�X�g�`��
	InfoDraw();
	// �Z���N�g�{�b�N�X�`��
	SelectBoxDraw();

#ifdef _DEBUG
	// �V�[�����`��
	DrawFormatString(0, 0, 0xffffff, "Select");
#endif // _DEBUG   

	// �t�F�[�h�`��
	DrawFade();
}

void SceneSelect::End()
{
	// BGM���~�߂�
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
				// �X�e�[�W1
				m_next = NextScene::Stage1;
			}
			else
			{
				// �X�e�[�W2
				m_next = NextScene::Stage2;
			}

		}
		else	// ���̑I�������Ă���
		{
			if (m_isLeft)	// ����I�����Ă���
			{
				// �����L���O
				m_next = NextScene::Ranking;
			}
			else
			{
				// �I��
				m_next = NextScene::End;
			}
		}
	}
	else
	{
		// ���݃V�[��
		m_next = NextScene::My;
	}
}

void SceneSelect::SelectBoxUpdate()
{
	/*���ݑI�΂�Ă���{�b�N�X���g�k����*/
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
	// ��ʉ����{�b�N�X�̕`��
	// �s�����x������������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kInfoBackAlpha);
	DrawGraph(kBackSideRightPosX, 0, m_backSideH, false);
	DrawGraph(kBackSideLeftPosX, 0, m_backSideH, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �摜�ԍ��̐ݒ�
	// �I��ł���ꏊ�ɂ���ăe�L�X�g��ς���
	int imgNum = m_isUp ? m_isLeft ? 0 : 1 : m_isLeft ? 2 : 3;

	// �������X�N���[����������
	int scroll = m_scrollY % m_textHeight;
	for (int index = 0; index < kIndexBackNum; index++)
	{
		DrawGraph(kBackSideRightPosX,
			-scroll + index * m_textHeight,
			m_textH[imgNum], true);
		DrawGraph(0,
			-scroll + index * m_textHeight,
			m_textH[imgNum], true);
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

void SceneSelect::LoadImg()
{
	// ���[�h�Ɏ��s�����ꍇ�͎~�߂�
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
}

void SceneSelect::DeleteImg()
{
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
