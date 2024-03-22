#include "Map.h"
#include "WorldSprite.h"
#include "DxLib.h"

const int Map::m_stageData[m_stageDataColNum][m_stageDataRowNum] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

const float Map::m_chipSize = 0.725f;
const int Map::m_chipPixelSize = 32;

Map::Map():
	m_chipHandle(-1)
{
	// ��������
}

Map::~Map()
{
	// ��������
}

void Map::Load()
{
	// �}�b�v�̃��[�h
	m_chipHandle = LoadGraph("");

	// WorldSprite�̎��Ԑݒ�ƈʒu�̏�����
	VECTOR chipLeftTopPos = VGet(0, m_stageDataColNum * m_chipSize, 0);	// �}�b�v�̕`��J�n�ʒu(����)
	for (int x = 0; x < m_stageDataColNum; x++)
	{
		for (int y = 0; y < m_stageDataRowNum; y++)
		{
			auto sprite = make_shared<WorldSprite>();
			sprite->Init(m_chipHandle, m_chipPixelSize, m_stageData[x][y]);
			VECTOR chipHalfOffset = VGet(-Map::m_chipSize * 0.5f, -Map::m_chipSize * 0.5f, 0);	// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(y * Map::m_chipSize, (-x - 1) * Map::m_chipSize, 0), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň���ɂ���
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, Map::m_chipSize);
			m_sprites.push_back(sprite);
		}
	}

}

void Map::Update()
{
}

void Map::Draw()
{
	for (const auto& sprite : m_sprites)
	{
		sprite->Draw();
	}
}
