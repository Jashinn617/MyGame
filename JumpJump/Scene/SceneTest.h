#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class StageTest;
class EnemyManager;

/// <summary>
/// ���C���V�[���N���X
/// </summary>
class SceneTest : public SceneBase
{
public:
	SceneTest();
	virtual ~SceneTest();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	virtual void End();

private:	// �֐�

	/// <summary>
	/// �f�o�b�O�\���p
	/// </summary>
	void DrawGrid();

private:	// �����o�֐��|�C���^
	
private:	// �ϐ�
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<StageTest> m_pStage;
	std::shared_ptr<EnemyManager> m_pEnemy;

	int m_back;


};