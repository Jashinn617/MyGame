#pragma once
#include <vector>
#include <memory>

using namespace std;

class WorldSprite;

/// <summary>
/// 2D�̔w�i�}�b�v
/// </summary>
class Map
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Map();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Map();

	/// <summary>
	/// �}�b�v�̃��[�h
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
	static const float m_chipSize;
	static const int m_chipPixelSize;
	static const int m_stageDataColNum = 16;	// �}�b�v�̍s
	static const int m_stageDataRowNum = 20;	// �}�b�v�̗�


private:
	// �}�b�v�`�b�v�̔z�u�f�[�^
	static const int m_stageData[m_stageDataColNum][m_stageDataRowNum];

	// WorldSprite�̃|�C���^
	vector<shared_ptr<WorldSprite>> m_sprites;
	// �}�b�v�`�b�v�̃n���h��
	int m_chipHandle;
};

