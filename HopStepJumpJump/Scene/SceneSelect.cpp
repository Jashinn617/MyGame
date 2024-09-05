#include "DxLib.h"
#include "SceneSelect.h"

#include "../Util/SoundManager.h"
#include "../Util/Input.h"
#include "../Util/Pad.h"
#include "../Util/Game.h"

#include <cassert>

namespace
{
	// �摜�̃t�@�C���p�X
	const char* const kBackGroundFineName = "Data/Img/Select/Background.png";

	// �Z���N�g�{�b�N�X�t�@�C���p�X
	const char* const kSelectBoxFileName[4] =
	{
		"Data/Img/Select/Stage1Box.png",
		"Data/Img/Select/Stage1Box.png",
		"Data/Img/Select/OnlineRankingBox.png",
		"Data/Img/Select/GameEndBox.png"
	};

	constexpr int kIndexBackNum = 2;	// �X�N���[���ɕK�v�Ȕw�i�̐�

	constexpr int kScrollSpeed = 1;		// �X�N���[���̃X�s�[�h

	/*�Z���N�g�{�b�N�X�̍��W*/
	constexpr int kSelectBoxPosX1 = 600;
	constexpr int kSelectBoxPosX2 = 1300;
	constexpr int kSelectBoxPosX3 = 700;
	constexpr int kSelectBoxPosX4 = 1100;
	constexpr int kUpSelectBoxPosY = 400;		// ��̃Z���N�g�{�b�N�X��Y�ʒu
	constexpr int kDownSelectBoxPosY = 820;		// ���̃Z���N�g�{�b�N�X��Y�ʒu

	constexpr float kMinUpBoxSize = 0.7f;
	constexpr float kMaxUpBoxSize = 0.7f;
	constexpr float kMinDownBoxSize = 0.6f;
	constexpr float kMaxDownBoxSize = 0.6f;
}

SceneSelect::SceneSelect() :
	m_backgroundH(-1),
	m_scrollX(0),
	m_backWidth(0),
	m_backHeight(0),
	m_isUp(true),
	m_isLeft(true),
	m_next(NextScene::My)
{
	/*�摜�n���h���̃��[�h*/
	m_backgroundH = LoadGraph(kBackGroundFineName);
	assert(m_backgroundH != -1);
	for (int i = 0; i < m_SelectBoxH.size(); i++)
	{
		m_SelectBoxH[i] = LoadGraph(kSelectBoxFileName[i]);
		assert(m_SelectBoxH[i] != -1);
	}

	// �w�i�摜�̃T�C�Y�̎擾
	GetGraphSize(m_backgroundH, &m_backWidth, &m_backHeight);
}

SceneSelect::~SceneSelect()
{
	/*�摜�n���h���̃f���[�g*/
	DeleteGraph(m_backgroundH);
	for (int i = 0; i < m_SelectBoxH.size(); i++)
	{
		DeleteGraph(m_SelectBoxH[i]);
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

	// �㉺�̑I���̓���ւ�
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_isUp = !m_isUp;
	}
	// ���E�̓���ւ�
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_isLeft = !m_isLeft;
	}



	return shared_from_this();
}

void SceneSelect::Draw()
{
	BackDraw();

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

void SceneSelect::SelectBoxDraw()
{
	DrawRotaGraph(kSelectBoxPosX1, kUpSelectBoxPosY,
		kMinUpBoxSize, 0.0f, m_SelectBoxH[0], true);
	DrawRotaGraph(kSelectBoxPosX2, kUpSelectBoxPosY,
		kMinUpBoxSize, 0.0f, m_SelectBoxH[1], true);

	DrawRotaGraph(kSelectBoxPosX1, kDownSelectBoxPosY,
		kMinDownBoxSize, 0.0f, m_SelectBoxH[2], true);
	DrawRotaGraph(kSelectBoxPosX2, kDownSelectBoxPosY,
		kMinDownBoxSize, 0.0f, m_SelectBoxH[3], true);
}
