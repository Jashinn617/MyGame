#pragma once
#include "../Utility/Game.h"

#include <memory>

class SceneBase;

/// <summary>
/// �e�V�[���̊Ǘ����s���N���X
/// </summary>
class SceneManager
{
public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneManager();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���̃V�[�������݂��Ă��邩�ǂ���</returns>
	bool Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

private:	// �ϐ�
	float m_updateTime;		// �X�V�ɂ����鎞��
	float m_drawTime;		// �`��ɂ����鎞��

	std::shared_ptr<SceneBase> m_pScene;	// ��������V�[���̃|�C���^
};

