#pragma once
#include "SceneBase.h"

#include <array>
#include <vector>
#include <memory>

class SceneRanking : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneRanking();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneRanking();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() override final;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���̃V�[��</returns>
	virtual std::shared_ptr<SceneBase> Update() override final;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() override final;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void End() override final;

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns>�V�[���̎��</returns>
	virtual SceneKind GetSceneKind()  override final { return SceneKind::Ranking; }

private:	// �֐�
	/// <summary>
	/// �����L���O�^�C���̕`��
	/// </summary>
	/// <param name="ranking"></param>
	void DrawRankingTime(int ranking);

	/// <summary>
	/// �����L���O�̕`��
	/// </summary>
	void DrawRanking();

	/// <summary>
	/// �{�^���̕`��
	/// </summary>
	void DrawButton();

	/// <summary>
	/// �摜�̃��[�h����
	/// </summary>
	void LoadImg();

	/// <summary>
	/// �摜�̃f���[�g����
	/// </summary>
	void DeleteImg();

private:
	int m_backgroundH;	// �w�i�摜�n���h��
	int m_textBoxH;		// �e�L�X�g�{�b�N�X�摜�n���h��
	int m_buttonH;		// �{�^���摜�n���h��
	int m_arrowH;		// ���摜�n���h��
	bool m_isStage1;	// �X�e�[�W1�̃����L���O���ǂ���
	bool m_isArrow;		// ��󂪑I�΂�Ă��邩�ǂ���

	float m_arrowSize;			// ���̃T�C�Y
	float m_backButtonSize;		// �߂�{�^���̃T�C�Y

	float m_expansionButtonSize;	// �g�k���Ă���{�^���̃T�C�Y
	float m_buttonSinCount;			// �I�΂�Ă���ꏊ���g�k���邽�߂̃J�E���g
	float m_buttonSinSize;			// �I�΂�Ă���ꏊ�̃T�C�Y�v�Z�Ɏg��Sin



	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�^�C���̉摜�n���h��
	std::array<int, 3> m_rankingH{};			// �����L���O�摜�n���h��
	std::array<int, 2> m_textH{};				// �e�L�X�g�摜�n���h��

	std::vector<int> m_stage1Ranking{};			// �X�e�[�W1�̃����L���O
	std::vector<int> m_stage2Ranking{};			// �X�e�[�W2�̃����L���O
};

