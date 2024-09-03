#include "DxLib.h"
#include "CountGetItem.h"
#include "../../Util/Game.h"

namespace
{
	const char* const kFileName1 = "Data/Img/ItemNum/ItemNumImg1.png";
	const char* const kFileName2 = "Data/Img/ItemNum/ItemNumImg2.png";
	const char* const kNumberFileName[10] =
	{
		"Data/Img/ItemNum/ItemNum0.png",
		"Data/Img/ItemNum/ItemNum1.png",
		"Data/Img/ItemNum/ItemNum2.png",
		"Data/Img/ItemNum/ItemNum3.png",
		"Data/Img/ItemNum/ItemNum4.png",
		"Data/Img/ItemNum/ItemNum5.png",
		"Data/Img/ItemNum/ItemNum6.png",
		"Data/Img/ItemNum/ItemNum7.png",
		"Data/Img/ItemNum/ItemNum8.png",
		"Data/Img/ItemNum/ItemNum9.png",
	};

	constexpr int kAlpha = 170;	// �摜�̓����x
	/*�摜�̍��W1*/
	constexpr int kImagePosX1 = static_cast<int>(Game::kScreenWidth * 0.42f);	// X
	constexpr int kImagePosY1 = 100;	// Y
	/*�摜�̍��W2*/
	constexpr int kImagePosX2 = static_cast<int>(Game::kScreenWidth * 0.62f);	// X
	constexpr int kImagePosY2 = 100;	// Y
	/*�����̍��W*/
	constexpr int kNumberPosX = static_cast<int>(Game::kScreenWidth * 0.525f);	// X
	constexpr int kNumberPosY = 100;	// Y
	/*�����̍��W(��̈�)*/
	constexpr int kNumberFirstPosX = static_cast<int>(Game::kScreenWidth * 0.55f);	// X
	constexpr int kNumberFirstPosY = 100;	// Y
	/*�����̍��W(�\�̈�)*/
	constexpr int kNumberSecondPosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kNumberSecondPosY = 100;	// Y

	constexpr float kFontSize = 0.5f;	// �����̃T�C�Y
}

CountGetItem::CountGetItem(int maxCount):
	m_count(0),
	m_maxCount(maxCount)
{
	m_H1 = LoadGraph(kFileName1);
	m_H2 = LoadGraph(kFileName2);

	// �����摜�n���h�����[�h
	for (int i = 0; i < m_numberH.size(); i++)
	{
		m_numberH[i] = LoadGraph(kNumberFileName[i]);
	}
}

CountGetItem::~CountGetItem()
{
	DeleteGraph(m_H1);
	DeleteGraph(m_H2);

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
	DrawRotaGraph(kImagePosX1, kImagePosY1,
		0.5f, 0.0f,
		m_H1, true);

	DrawRotaGraph(kImagePosX2, kImagePosY2,
		0.55f, 0.0f,
		m_H2, true);

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
