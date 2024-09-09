#pragma once
#include "SceneBase.h"

#include <array>

class SceneSelect : public SceneBase
{
public:
	enum class NextScene
	{
		My,
		Stage1,
		Stage2,
		Ranking,
		End
	};

public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

	virtual SceneKind GetSceneKind() { return SceneKind::StageSelect; }

private:	// �֐�
	/// <summary>
	/// �Z���N�g�̍X�V
	/// </summary>
	void  SelectUpdate();

	/// <summary>
	/// �Z���N�g�{�b�N�X�̍X�V
	/// </summary>
	void SelectBoxUpdate();

	/// <summary>
	/// �w�i�̕`��
	/// </summary>
	void BackDraw();

	void InfoDraw();

	/// <summary>
	/// �Z���N�g�{�b�N�X�̕`��
	/// </summary>
	void SelectBoxDraw();

private:	// �ϐ�
	int m_backgroundH;					// �w�i�摜�̃n���h��
	int m_backSideH;					// ���E�̔w�i�摜�n���h��
	std::array<int, 4> m_SelectBoxH{};	// �Z���N�g�{�b�N�X�̃n���h��
	std::array<int, 4> m_textH{};
	int m_scrollX;						// �w�i�̃X�N���[���l
	int m_scrollY;						// �����̃X�N���[���l
	int m_textWidth;
	int m_textHeight;
	int m_backWidth;					// �摜�̉���
	int m_backHeight;					// �摜�̏c��
	bool m_isUp;						// �オ�I������Ă��邩�ǂ���
	bool m_isLeft;						// �����I������Ă��邩�ǂ���

	float m_upBoxSize1;
	float m_upBoxSize2;
	float m_downBoxSize1;
	float m_downBoxSize2;

	float m_expansionBoxSize;

	float m_boxSinCount;	// �{�b�N�X���g�k���邽�߂̃J�E���g
	float m_boxSinSize;		// �{�b�N�X�̃T�C�Y�v�Z�Ɏg��Sin

	NextScene m_next;					// ���̃V�[��
};

