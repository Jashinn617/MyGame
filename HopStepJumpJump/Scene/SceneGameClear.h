#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "../Util/Game.h"

#include <memory>
#include <vector>
#include <array>

class Input;
class StageSceneManager;
class Time;

class SceneGameClear : public SceneBase
{
public:
	// �����N
	enum class Rank
	{
		S,
		A,
		B,
		C,
		RankNum,
	};
public:
	SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager, Game::Stage stageKind);
	~SceneGameClear();

	virtual void Init() override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	// �V�[���̎�ނ̎擾
	virtual SceneKind GetSceneKind() { return SceneKind::GameClear; }

private:	// �֐�
	void TextDraw();
	void TimeDraw();
	void RankingDraw();
	void RankDraw();
	void RankTimeDraw(int ranking);
	void MyRankTimeDraw(int ranking);
	void ButtonDraw();
	
	void ChangeMainScene();
	void ChangeTitleScene();

private:	// �ϐ�
	int m_clearTime;		// �X�e�[�W�̃N���A����
	bool m_isSceneEnd;	// �V�[�����I���������ǂ���
	bool m_isNextScene;	// ���̃V�[���Ɉړ��\���ǂ���
	bool m_isMyRank;	// �����̃^�C�������f����Ă��邩
	bool m_isFall;		// ��������
	
	int m_plusPosY;		// ����Y���W

	std::array<int, 11> m_myTimeNumH{};	// ���g�̃N���A�^�C���̉摜�n���h��
	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�̃^�C���̉摜�n���h��
	std::array<int, 4> m_rankH{};			// �����N�摜�n���h��
	std::array<int, 3> m_textH{};	// �e�L�X�g�摜�n���h��
	std::array<int, 3> m_rankingH{};	// �����L���O�摜�n���h��
	std::array<int, 2> m_textBoxH{};	// �e�L�X�g�{�b�N�X�摜�n���h��
	std::array<int, 2> m_buttonH{};		// �{�^���̉摜�n���h��

	Rank m_rank;			// �����N

	std::vector<int> m_ranking{};	// �����L���O
	Game::Stage m_stageKind;		// �X�e�[�W�̎��

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;
	std::shared_ptr<Time> m_pImageDrawTime;
	std::shared_ptr<Time> m_pStageClearSETime;	// �X�e�[�W�N���A���̃T�E���h�̊J�n����
};

