#include "UI.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"

namespace
{

	constexpr int kAnimationFrameMax = 15;
	constexpr int kMaxHp = 6;
}

UI::UI() :
	m_UIX(0),
	m_UIY(0),
	m_playerHp(0),
	m_animationFrame(0),
	m_isUp(false),
	m_playerRemainingLives(0),
	m_fontHandle(-1),
	m_fontBackHandle(-1)
{
	// HP�o�[�̉摜�����[�h����
	m_UIHandle0 = LoadGraph("data/UI/UI0.png");
	m_UIHandle1 = LoadGraph("data/UI/UI1.png");
	m_UIHandle2 = LoadGraph("data/UI/UI2.png");
	// HP�̉摜�����[�h����
	m_hpHandle1 = LoadGraph("data/UI/HP1.png");
	m_hpHandle0 = LoadGraph("data/UI/HP.png");
	// UI�̃T�C�Y���擾����
	GetGraphSize(m_UIHandle0, &m_w, &m_h);

	// �c�@���\���p�̃t�H���g
	m_fontHandle = CreateFontToHandle("GN-�L���SU����NA", 150, -1);
	m_fontBackHandle = CreateFontToHandle("GN-�L���SU����NA", 160, -1);
}

UI::~UI()
{
	/*�摜�̃f���[�g*/
	DeleteGraph(m_UIHandle0);
	DeleteGraph(m_UIHandle1);
	DeleteGraph(m_UIHandle2);
	DeleteGraph(m_hpHandle1);
	DeleteGraph(m_hpHandle0);
	/*�t�H���g�̃f���[�g*/
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontBackHandle);
}

void UI::Init()
{
	// �v���C���[��HP���擾����
	m_playerHp = m_pPlayer->GetHp();
	// �v���C���[�̎c�@���擾����
	m_playerRemainingLives = m_pPlayer->GetRemainingLives();	
}

void UI::Draw()
{
	// �A�j���[�V����
	int UIY = Game::kScreenHeight - m_h - m_UIY;
	// UI�̕`��
	DrawGraph(m_UIX, Game::kScreenHeight - m_h, m_UIHandle2, true);
	DrawGraph(m_UIX, UIY, m_UIHandle1, true);
	DrawGraph(m_UIX, UIY, m_UIHandle0, true);

	// �A�j���[�V����
	int HpY = Game::kScreenHeight - m_h + 25 - m_UIY;
	for (int i = 0; i < 6; i++)
	{
		DrawGraph(450 + (i * 100), HpY, m_hpHandle1, true);
	}
	// HP�̐������\������
	for (int i = 0; i < m_playerHp; i++)
	{
		DrawGraph(450 + (i * 100),HpY, m_hpHandle0, true);
	}

	// �A�j���[�V����
	int SY = Game::kScreenHeight - m_h + 80 - m_UIY;
	// �c�@�̕`��
	DrawFormatStringToHandle(1500, SY, 0xffff00, m_fontBackHandle, "%d", m_playerRemainingLives);
	DrawFormatStringToHandle(1505, SY, 0x000000, m_fontHandle, "%d", m_playerRemainingLives);
}

void UI::Update()
{
	// �v���C���[��HP���擾����
	m_playerHp = m_pPlayer->GetHp();
	// �v���C���[�̎c�@���擾����
	m_playerRemainingLives = m_pPlayer->GetRemainingLives();

	// �A�j���[�V����
	m_animationFrame++;
	if (m_animationFrame >= kAnimationFrameMax)
	{
		if (!m_isUp)// �������Ă���
		{
			m_isUp = true;
			m_UIY = 5;
			m_animationFrame = 0;
		}
		else if (m_isUp)// �オ���Ă���
		{
			m_isUp = false;
			m_UIY = 0;
			m_animationFrame = 0;
		}
	}
}
