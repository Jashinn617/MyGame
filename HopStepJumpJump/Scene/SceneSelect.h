#pragma once
#include "SceneBase.h"

#include <array>

class SceneSelect : public SceneBase
{
public:
	// ���̃V�[��
	enum class NextScene
	{
		My,			// ���݃V�[��
		Stage1,		// �X�e�[�W1
		Stage2,		// �X�e�[�W2
		Ranking,	// �����L���O
		End			// �I��
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneSelect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneSelect();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init()  override final;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���V�[��</returns>
	virtual std::shared_ptr<SceneBase> Update()  override final;
	
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw()  override final;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void End()  override final;

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns>�V�[���̎��</returns>
	virtual SceneKind GetSceneKind()  override final { return SceneKind::StageSelect; }

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

	/// <summary>
	/// ���̐����̕`��
	/// </summary>
	void InfoDraw();

	/// <summary>
	/// �Z���N�g�{�b�N�X�̕`��
	/// </summary>
	void SelectBoxDraw();

	/// <summary>
	/// �摜�̃��[�h
	/// </summary>
	void LoadImg();

	/// <summary>
	/// �摜�̃f���[�g
	/// </summary>
	void DeleteImg();

private:	// �ϐ�
	int m_backgroundH;					// �w�i�摜�̃n���h��
	int m_backSideH;					// ���E�̔w�i�摜�n���h��
	std::array<int, 4> m_SelectBoxH{};	// �Z���N�g�{�b�N�X�摜�̃n���h��
	std::array<int, 4> m_textH{};		// �e�L�X�g�摜�̃n���h��
	int m_scrollX;						// �w�i�̃X�N���[���l
	int m_scrollY;						// �����̃X�N���[���l
	int m_textWidth;					// �e�L�X�g�̉���
	int m_textHeight;					// �e�L�X�g�̏c��
	int m_backWidth;					// �摜�̉���
	int m_backHeight;					// �摜�̏c��
	float m_upBoxSize1;					// ��̃{�b�N�X�̃T�C�Y1
	float m_upBoxSize2;					// ��̃{�b�N�X�̃T�C�Y2
	float m_downBoxSize1;				// ���̃{�b�N�X�̃T�C�Y1
	float m_downBoxSize2;				// ���̃{�b�N�X�̃T�C�Y2
	float m_expansionBoxSize;			// �{�b�N�X�̊g�k�T�C�Y
	float m_boxSinCount;	// �{�b�N�X���g�k���邽�߂̃J�E���g
	float m_boxSinSize;		// �{�b�N�X�̃T�C�Y�v�Z�Ɏg��Sin
	bool m_isUp;						// �オ�I������Ă��邩�ǂ���
	bool m_isLeft;						// �����I������Ă��邩�ǂ���
	NextScene m_next;					// ���̃V�[��
};

