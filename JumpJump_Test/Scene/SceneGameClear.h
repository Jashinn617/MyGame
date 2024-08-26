#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "../Util/Game.h"

#include <memory>
#include <vector>

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
	int m_graphH;		// �摜�n���h��
	int m_stageClearTime;	// �X�e�[�W�̃N���A�^�C��
	bool m_isSceneEnd;	// �V�[�����I���������ǂ���
	bool m_isNextScene;	// ���̃V�[���Ɉړ��\���ǂ���

	std::vector<int> m_rank{};	// �����L���O
	Game::Stage m_stageKind;		// �X�e�[�W�̎��

	std::shared_ptr<StageSceneManager> m_pStageSceneManager;
	std::shared_ptr<Time> m_pImageDrawTime;
	std::shared_ptr<Result> m_pResult;
};

