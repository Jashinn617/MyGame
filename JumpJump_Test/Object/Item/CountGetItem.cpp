#include "DxLib.h"
#include "CountGetItem.h"
#include "../../Util/Game.h"
#include "../../Util/Font.h"

namespace
{
	const char* const kFileName = "";
	const char* const kNumberFileName[10] =
	{
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
	};

	constexpr int kAlpha = 170;	// �摜�̓����x
	/*�摜�̍��W*/
	constexpr int kImagePosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kImagePosY = 100;	// Y
	/*�����̍��W*/
	constexpr int kStringPosX = static_cast<int>(Game::kScreenWidth * 0.5f - 75);	// X
	constexpr int kStringPosY = 85;	// Y
	/*�����̍��W*/
	constexpr int kNumberPosX = static_cast<int>(Game::kScreenWidth * 0.5f + 17);	// X
	constexpr int kNumberPosY = 100;	// Y
	/*�����̍��W(��̈�)*/
	constexpr int kNumberFirstPosX = static_cast<int>(Game::kScreenWidth * 0.5f + 30);	// X
	constexpr int kNumberFirstPosY = 100;	// Y
	/*�����̍��W(�\�̈�)*/
	constexpr int kNumberSecondPosX = static_cast<int>(Game::kScreenWidth * 0.5f - 4);	// X
	constexpr int kNumberSecondPosY = 100;	// Y

	constexpr float kFontSize = 0.26f;	// �����̃T�C�Y
}

CountGetItem::CountGetItem(int maxCount):
	m_count(0),
	m_maxCount(maxCount)
{
	m_H = LoadGraph(kFileName);

	// �����摜�n���h�����[�h
	for (int i = 0; i < m_numberH.size(); i++)
	{
		m_numberH[i] = LoadGraph(kNumberFileName[i]);
	}
}

CountGetItem::~CountGetItem()
{
	DeleteGraph(m_H);

	for (int i = 0; i < m_numberH.size(); i++)
	{
		DeleteGraph(m_numberH[i]);
	}
}

void CountGetItem::Draw()
{
	// �c��A�C�e���̐�
	int remainingItem = m_maxCount - m_count;

	// �c��̃A�C�e���̐���0�̏ꍇ�͉����`�悵�Ȃ�
	if (remainingItem <= 0)return;

	// �c��̃A�C�e�����̉摜�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawRotaGraph(kImagePosX, kImagePosY,
		1.0f, 0.0f,
		m_H, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �c��̃A�C�e�������ꌅ�̎�
	if (remainingItem < 10)
	{
		DrawRotaGraph(kNumberPosX, kNumberPosY, 
			kFontSize, 0.0f,
			m_numberH[remainingItem], true);
	}
	else // �c��̃A�C�e�������񌅂̎�
	{
		int numFirst = remainingItem % 10;	// ��̈�
		int numSecond = remainingItem / 10;	// �\�̈�

		DrawRotaGraph(kNumberFirstPosX, kNumberFirstPosY, 
			kFontSize, 0.0f, 
			m_numberH[numFirst], true);
		DrawRotaGraph(kNumberSecondPosX, kNumberSecondPosY, 
			kFontSize, 0.0f,
			m_numberH[numSecond], true);
	}

#ifdef _DEBUG
	DrawFormatString(0, 80, 0xffffff, "�c��̃A�C�e�����F%d", remainingItem);
#endif // _DEBUG
}

void CountGetItem::Add()
{
	m_count = min(m_count++, m_maxCount);
}

bool CountGetItem::IsCountMax()
{
	// �J�E���g���ő�l�ȏ�ɂȂ��Ă����ꍇ
	if (m_count >= m_maxCount) return true;

	return false;
}
