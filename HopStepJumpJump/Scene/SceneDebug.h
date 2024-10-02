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
		Title,			// �^�C�g��
		StageSelect,	// �X�e�[�W�Z���N�g
		Ranking,		// �����L���O
		Test,			// �e�X�g

		SceneNum,		// �V�[����
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneDebug();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneDebug();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() override final;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���݂̃V�[��</returns>
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
	/// �V�[����ނ̎擾
	/// </summary>
	/// <returns></returns>
	virtual SceneKind GetSceneKind()  override final { return SceneKind::Debug; }

private:	// �֐�
	/// <summary>
	/// �J�[�\���X�V
	/// </summary>
	void UpdateCursor();

	/// <summary>
	/// ���̃V�[���̍X�V
	/// </summary>
	/// <returns>���̃V�[��</returns>
	std::shared_ptr<SceneBase> UpdateNextScene();


private:	// �ϐ�
	int m_count;		// �J�[�\���̃J�E���g

	// �V�[���ړ��p�̕���
	std::array<std::string, static_cast<int>(SceneType::SceneNum)> m_sceneString;
};