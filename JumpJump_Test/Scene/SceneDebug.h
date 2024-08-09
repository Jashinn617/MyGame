#pragma once
#include "SceneBase.h"

#include <string>
#include <array>

class SceneDebug : public SceneBase
{
public:
	enum class SceneType
	{
		Debug,			// �f�o�b�O
		Stage1,			// �X�e�[�W1
		Stage2,			// �X�e�[�W2
		Option,			// �I�v�V����
		GameClear,		// �Q�[���N���A
		Title,			// �^�C�g��
		StageSelect,	// �X�e�[�W�Z���N�g
		Tutorial,		// �`���[�g���A��
		Ranking,		// �����L���O
		Test,			// �e�X�g

		SceneNum,		// �V�[����
	};

public:
	SceneDebug();
	virtual ~SceneDebug();

	virtual void Init() override final;

	virtual std::shared_ptr<SceneBase> Update(Input& input) override final;
	virtual void Draw() override final;
	virtual void End() override final;

	/// <summary>
	/// �V�[����ނ̎擾
	/// </summary>
	/// <returns></returns>
	virtual SceneKind GetSceneKind() { return SceneKind::Debug; }

private:	// �֐�
	/// <summary>
	/// �J�[�\���̃A�b�v�f�[�g
	/// </summary>
	void UpdateCursor(Input& input);

	/// <summary>
	/// ���̃V�[���̃A�b�v�f�[�g
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<SceneBase> UpdateNextScene();


private:	// �ϐ�
	int m_count;		// �J�[�\���̃J�E���g
	std::array<std::string, static_cast<int>(SceneType::SceneNum)> m_sceneString;	// �V�[���ړ��p�̕���
};