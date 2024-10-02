#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneTitle();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneTitle();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���̃V�[��</returns>
	virtual std::shared_ptr<SceneBase> Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	virtual void End();

	/// <summary>
	/// �V�[���̎�ނ̎擾
	/// </summary>
	/// <returns>�V�[���̎��</returns>
	virtual SceneKind GetSceneKind() { return SceneKind::Title; }

private:	// �ϐ�
	int m_titleLogoH;		// �^�C�g�����S�摜�n���h��
	int m_textH;			// �e�L�X�g�摜�n���h��
	int m_movieH;			// ����n���h��
	int m_titlePosY;		// �^�C�g���ʒu
	bool m_isPlayFallSE;	// �^�C�g���������������Ƃ���SE��炵�����ǂ���
};

