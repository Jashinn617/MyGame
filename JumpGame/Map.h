#pragma once
#include <vector>

class WorldSprite;

/// <summary>
/// 2D�̔w�i�}�b�v
/// </summary>
class Map
{
public:
	Map();
	~Map();

	/// <summary>
	/// ���[�h
	/// </summary>
	void Load();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/*�}�b�v�`�b�v�̃T�C�Y*/
	static const float	kChipSize;
	static const int	kChipPixelSize;

	static const int	kStageDataColNum = 16;		// �}�b�v�s
	static const int	kStageDataRowNum = 480;		// �}�b�v��

private:
	static const int m_stage1Data[kStageDataColNum][kStageDataRowNum];	// �}�b�v�`�b�v����ׂ�z��

	std::vector<WorldSprite*> m_pSprites;		// ���[���h�X�v���C�g�̃|�C���^
	int m_chipHandle;							// �}�b�v�`�b�v�̉摜
};

