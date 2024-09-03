#pragma once
#include "../Util/Game.h"

#include <memory>
#include <functional>

class Input;
class ObjectManager;
class CountTime;

class StageSceneManager
{
public:

	enum class SceneType
	{
		Counddown,		// �ŏ��̃J�E���g�_�E��
		Main,			// ���C��
		Clear,			// �N���A
	};
public:
	StageSceneManager(Game::Stage stageKind);
	virtual ~StageSceneManager();

	void Init();

	void Update(Input& input);
	void Draw();

	void AttachGameClear(std::function<void(void)> gameClear);

	void SetGameClear();

	/// <summary>
	/// �X�e�[�W�̎擾
	/// </summary>
	/// <returns>�X�e�[�W�̎��</returns>
	Game::Stage GetStageKind() const { return m_stageKind; }
	const std::shared_ptr<ObjectManager> GetObjectManager() { return m_pObjectManager; }
	/// <summary>
	/// �Q�[���N���A���Ԃ̎擾
	/// </summary>
	/// <returns></returns>
	int GetGameClearTime() const{return m_gameClearTime; }

private:	// �֐�
	/// <summary>
	/// �J�E���g�_�E���X�V
	/// </summary>
	void CountdownUpdate(Input& input);
	/// <summary>
	/// ���C���X�V
	/// </summary>
	void MainUpdate(Input& input);
	/// <summary>
	///	�N���A�X�V
	/// </summary>
	void ClearUpdate(Input& input);

	/// <summary>
	/// �J�E���g�_�E���`��
	/// </summary>
	void CountdownDraw();
	/// <summary>
	/// ���C���`��
	/// </summary>
	void MainDraw();
	/// <summary>
	/// �N���A�`��
	/// </summary>
	void ClearDraw();

private:	// �ϐ�
	int m_gameClearTime ;		// �N���A�^�C��
	bool m_isGameClear;			// �Q�[�����N���A�������ǂ���
	bool m_isPlayClearSE;			// �N���ASE���Ȃ炵�����ǂ���
	
	Game::Stage m_stageKind;	// �X�e�[�W�̎��

	SceneType m_sceneType;		// �V�[���^�C�v

	std::shared_ptr<ObjectManager> m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃|�C���^
	std::shared_ptr<CountTime> m_pCountTime;		// �b���J�E���g�̃|�C���^

	std::function<void(void)> m_gameClear = [] {};	// �Q�[���N���A���̊֐�(��̃����_��)
};

