#pragma once
#include "DxLib.h"
#include <memory>

class Ranking;

/// <summary>
/// �e�V�[���̊��N���X
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	// �V�[���̎��
	enum class SceneKind
	{
		Debug,			// �f�o�b�O	
		Title,			// �^�C�g��
		Stage,			// �Q�[���X�e�[�W
		StageSelect,	// �X�e�[�W�Z���N�g
		Ranking,		// �����L���O
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneBase();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneBase();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���݂̃V�[��</returns>
	virtual std::shared_ptr<SceneBase> Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns></returns>
	virtual SceneKind GetSceneKind() = 0;

protected:	// �֐�
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

protected:
	std::shared_ptr<Ranking> m_pRanking;	// �����L���O

private:	// �ϐ�
	int m_fadeColor;		// �t�F�[�h�̐F
	int m_fadeBright;		// �t�F�[�h�̖��邳
	int m_fadeSpeed;		// �t�F�[�h�̃X�s�[�h
};
