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
class Result;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear();
	SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager, Game::Stage stageKind);
	~SceneGameClear();

	virtual void Init() override final;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	// �V�[���̎�ނ̎擾
	virtual SceneKind GetSceneKind() { return SceneKind::GameClear; }

private:	// �֐�
	void ChangeMainScene();
	void ChangeTitleScene();

private:	// �ϐ�
	int m_backgroundH;		// �摜�n���h��
	int m_stageClearTime;	// �X�e�[�W�̃N���A�^�C��
	bool m_isSceneEnd;	// �V�[�����I���������ǂ���
	bool m_isNextScene;	// ���̃V�[���Ɉړ��\���ǂ���

	std::array<int, 10> m_myTimeNumH{};	// ���g�̃N���A�^�C���̉摜�n���h��
	std::array<int, 10> m_rankingTimeNumH{};	// �����L���O�̃^�C���̉摜�n���h��
	std::array<int, 3> m_textH{};	// �e�L�X�g�摜�n���h��
	std::array<int, 3> m_rankingH{};	// �����L���O�摜�n���h��
	std::array<int, 2> m_textBoxH{};	// �e�L�X�g�{�b�N�X�摜�n���h��
	std::array<int, 2> m_buttonH{};		// �{�^���̉摜�n���h��


	std::vector<int> m_ranking{};	// �����L���O
	Game::Stage m_stageKind;		// �X�e�[�W�̎��

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;
	std::shared_ptr<Time> m_pImageDrawTime;
	std::shared_ptr<Result> m_pResult;
};

