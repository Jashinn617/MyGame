#pragma once
#include "DxLib.h"
#include <memory>

class Input;
class Ranking;

/// <summary>
/// �e�V�[���̊��N���X
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	// �V�[���J�ڎ��̏���
	enum class Transition
	{
		Leave,		// �c��
		Delete,		// �폜
	};

	// �V�[���̎��
	enum class SceneKind
	{
		Debug,			// �f�o�b�O	
		Title,			// �^�C�g��
		GameClear,		// �Q�[���N���A	
		Stage,			// �Q�[���X�e�[�W
		Option,			// �I�v�V����
		StageSelect,	// �X�e�[�W�Z���N�g
		Tutorial,		// �`���[�g���A��
		Ranking,		// �����L���O
	};

public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns></returns>
	virtual SceneKind GetSceneKind() = 0;

	/// <summary>
	/// �t�F�[�h�̍X�V
	/// </summary>
	void UpdateFade();

	/// <summary>
	/// �t�F�[�h�̕`��
	/// </summary>
	void DrawFade();

	/// <summary>
	/// �t�F�[�h�C���̃X�L�b�v
	/// </summary>
	void SkipFadeIn();

	/// <summary>
	/// �t�F�[�h�A�E�g�̃X�L�b�v
	/// </summary>
	void SkipFadeOut();

	/// <summary>
	/// �t�F�[�h�C������
	/// </summary>
	/// <returns></returns>
	bool IsFadeIn() const;

	/// <summary>
	/// �t�F�[�h�A�E�g����
	/// </summary>
	/// <returns></returns>
	bool IsFadeOut() const;

	/// <summary>
	/// �t�F�[�h����
	/// </summary>
	/// <returns></returns>
	bool IsFade()const { return IsFadeIn() || IsFadeOut(); }

	/// <summary>
	/// �t�F�[�h�A�E�g�̊J�n
	/// </summary>
	void StartFadeOut();

	/// <summary>
	/// �t�F�[�h�̖��邳�̎擾
	/// </summary>
	/// <returns></returns>
	int GetFadeBright()const { return m_fadeBright; }

	/// <summary>
	/// �V�[���J�ڎ��̏����̎�ނ̎擾
	/// </summary>
	/// <returns></returns>
	virtual Transition GetTransitionType() { return m_transition; }

protected:
	std::shared_ptr<Ranking> m_pRanking;

private:
	int m_fadeColor;		// �t�F�[�h�̐F
	int m_fadeBright;		// �t�F�[�h�̖��邳
	int m_fadeSpeed;		// �t�F�[�h�̃X�s�[�h

	Transition m_transition;	// �V�[���J�ڂ̎��
};
