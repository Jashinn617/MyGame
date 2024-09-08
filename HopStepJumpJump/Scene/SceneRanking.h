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

private:
	int m_backgroundH;	// �w�i�摜�n���h��
	int m_textBoxH;		// �e�L�X�g�{�b�N�X�摜�n���h��
	int m_buttonH;		// �{�^���摜�n���h��
	bool m_isStage1;	// �X�e�[�W1�̃����L���O���ǂ���



	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�^�C���̉摜�n���h��
	std::array<int, 3> m_rankingH{};			// �����L���O�摜�n���h��

	std::vector<int> m_stage1Ranking{};
	std::vector<int> m_stage2Ranking{};

	std::shared_ptr<Ranking> m_pRanking;

};

