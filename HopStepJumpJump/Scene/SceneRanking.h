#pragma once
#include "SceneBase.h"

#include <array>
#include <vector>
#include <memory>

class Ranking;

class SceneRanking : public SceneBase
{
public:
	SceneRanking();
	virtual ~SceneRanking();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
	virtual SceneKind GetSceneKind() { return SceneKind::Ranking; }

private:
	void RankTimeDraw(int ranking);
	void RankingDraw();

	void ButtonDraw();

private:
	int m_backgroundH;	// �w�i�摜�n���h��
	int m_textBoxH;		// �e�L�X�g�{�b�N�X�摜�n���h��
	int m_buttonH;		// �{�^���摜�n���h��
	int m_arrowH;		// ���摜�n���h��
	bool m_isStage1;	// �X�e�[�W1�̃����L���O���ǂ���
	bool m_isArrow;		// ��󂪑I�΂�Ă��邩�ǂ���

	float m_arrowSize;
	float m_backButtonSize;

	float m_expansionButtonSize;
	float m_buttonSinCount;		// �I�΂�Ă���ꏊ���g�k���邽�߂̃J�E���g
	float m_buttonSinSize;		// �I�΂�Ă���ꏊ�̃T�C�Y�v�Z�Ɏg��Sin



	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�^�C���̉摜�n���h��
	std::array<int, 3> m_rankingH{};			// �����L���O�摜�n���h��
	std::array<int, 2> m_textH{};				// �e�L�X�g�摜�n���h��

	std::vector<int> m_stage1Ranking{};
	std::vector<int> m_stage2Ranking{};

	std::shared_ptr<Ranking> m_pRanking;

};

