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
	StageSceneManager(Game::Stage stageKind);
	virtual ~StageSceneManager();

	void Init();

	void Update(Input& input);
	void Draw();

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

	/// <summary>
	/// �Q�[���N���A���ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsGameClear()const { return m_isGameClear; }

private:	// �ϐ�
	int m_gameClearTime ;		// �N���A�^�C��
	bool m_isGameClear;			// �Q�[�����N���A�������ǂ���
	
	Game::Stage m_stageKind;	// �X�e�[�W�̎��

	std::shared_ptr<ObjectManager> m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃|�C���^
	std::shared_ptr<CountTime> m_pCountTime;		// �b���J�E���g�̃|�C���^
};

