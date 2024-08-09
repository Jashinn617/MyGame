#pragma once
#include "SceneBase.h"

class Input;
class StageSceneManager;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(std::shared_ptr<StageSceneManager> pStageSceneManager);
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
	bool m_isSceneEnd;	// �V�[�����I���������ǂ���
	bool m_isNextScene;	// ���̃V�[���Ɉړ��\���ǂ���
};

