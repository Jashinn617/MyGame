#pragma once
#include "SceneBase.h"

#include <array>

class SceneSelect : public SceneBase
{
public:
	enum class NextScene
	{
		My,
		Stage1,
		Stage2,
		Ranking,
		End
	};

public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

	virtual SceneKind GetSceneKind() { return SceneKind::StageSelect; }

private:	// �֐�
	/// <summary>
	/// �Z���N�g�̍X�V
	/// </summary>
	void  SelectUpdate();

	/// <summary>
	/// �w�i�̕`��
	/// </summary>
	void BackDraw();

	/// <summary>
	/// �Z���N�g�{�b�N�X�̕`��
	/// </summary>
	void SelectBoxDraw();

private:	// �ϐ�
	int m_backgroundH;					// �w�i�摜�̃n���h��
	std::array<int, 4> m_SelectBoxH{};	// �Z���N�g�{�b�N�X�̃n���h��
	int m_scrollX;						// �w�i�̃X�N���[���l
	int m_backWidth;					// �摜�̉���
	int m_backHeight;					// �摜�̏c��
	bool m_isUp;						// �オ�I������Ă��邩�ǂ���
	bool m_isLeft;						// �����I������Ă��邩�ǂ���

	NextScene m_next;					// ���̃V�[��
};

