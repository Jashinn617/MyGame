#pragma once
#include "../Game.h"
#include "../util/Vec2.h"
#include "../util/Rect.h"

#include <memory>
#include <vector>

class Camera;
class Player;
class GameOverScene;
class StopEnemy;
class WalkEnemy;
class FlyEnemy;
class RecoveryItem;
class Input;
class UI;
class Door;
class Stage_01
{
public:
	// ���̃V�[��
	enum NextScene
	{
		kStage02,	// �X�e�[�W2
		kGameOver	// �Q�[���I�[�o�[
	};
public:
	Stage_01();
	~Stage_01();

	// ������
	void Init();
	// �X�V
	void Update(Input& input);
	// �`��
	void Draw();
	// �V�[���I�����̏���
	void End();
	// �V�[�����I���������ǂ���
	bool IsSceneEnd() const;
	// ���X�^�[�g���̏�����
	void RestartInit();
	// �G�L�����N�^�[�̏�����
	void EnemyInit();
	// �A�C�e���̏�����
	void ItemInit();
	// �G�L�����N�^�[�̍X�V
	void EnemyUpdate();
	// �A�C�e���̍X�V
	void ItemUpdate();
	// �w�i�̕`��
	void BackDraw();
	// �}�b�v�`�b�v�̕`��
	void ChipDraw();
	// �G�L�����N�^�[�̕`��
	void EnemyDraw();
	// �A�C�e���̕`��
	void ItemDraw();
	// �v���C���[���~�X���������̉��o
	void OnMiss();

	/*�|�C���^�̐ݒ�*/
	// �v���C���[
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	// �J����
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// UI
	void SetUI(std::shared_ptr<UI> pUI) { m_pUI = pUI; }
	// �Q�[���I�[�o�[�V�[��
	void SetGameOver(std::shared_ptr<GameOverScene> pGameOver) { m_pGameOver = pGameOver; }
	// �ړ��p�̃h�A
	void SetDoor(std::shared_ptr<Door> pDoor) { m_pDoor = pDoor; }
	// �~�܂��Ă���G
	void SetStopEnemy(std::shared_ptr<StopEnemy> pStopEnemy, int i) { m_pStopEnemy[i] = pStopEnemy; }
	// �����Ă���G
	void SetWalkEnemy(std::shared_ptr<WalkEnemy> pWalkEnemy, int i) { m_pWalkEnemy[i] = pWalkEnemy; }
	// ���ł���G
	void SetFlyEnemy(std::shared_ptr<FlyEnemy> pFlyEnemy, int i) { m_pFlyEnemy[i] = pFlyEnemy; }
	// �񕜃A�C�e��
	void SetItem(std::shared_ptr<RecoveryItem> pRecoveryItem, int i) { m_pRecoveryItem[i] = pRecoveryItem; }

	/*���̃V�[���̐ݒ�*/
	// �ǂ̃V�[���ɍs�����擾����
	NextScene IsNextScene()const { return m_nextScene; }
	// ���̃V�[�����X�e�[�W2�ɐݒ肷��
	NextScene GetStage02() const { return kStage02; }
	// ���̃V�[�����Q�[���I�[�o�[�ɐݒ肷��
	NextScene GetGameOver() const { return kGameOver; }
private:
	/*�O���t�B�b�N*/
	// �Q�[�����
	int m_gameScreenHandle;
	// �w�i
	int m_backgroundHandle;
	// �}�b�v�`�b�v
	int m_chipHandle;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
	// �}�b�v�`�b�v�̔z�u���
	std::vector<std::vector<int>> m_chipData;

	/*BGM*/
	int m_bgmHandle;

	/*SE*/
	// �~�X���o
	int m_missSeHandle;
	// �~�X�������u��
	int m_missSeHandle2;
	// �X�e�[�W�ړ���
	int m_moveSeHandle;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;
	int m_backAlpha;
	// �~�X�������ۂ̃t�F�[�h
	bool m_ismissFade;
	
	/* �~�X���������̉�ʗh��*/
	int m_shakeFrame;

	// ���̃V�[��
	NextScene m_nextScene;

	// �~�X���������ǂ���
	bool m_isMiss;

	// �V�[�����I�����Ă��邩�ǂ���
	bool m_isSceneEnd;

	/*�|�C���^*/
	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// �J����
	std::shared_ptr<Camera> m_pCamera;
	// UI
	std::shared_ptr<UI> m_pUI;
	// �Q�[���I�[�o�[�V�[��
	std::shared_ptr<GameOverScene> m_pGameOver;
	// �h�A
	std::shared_ptr<Door> m_pDoor;
	/*�G�l�~�[*/
	// �~�܂��Ă���G
	std::vector<std::shared_ptr<StopEnemy>> m_pStopEnemy;
	// �����G
	std::vector < std::shared_ptr<WalkEnemy>> m_pWalkEnemy;
	// ��ԓG
	std::vector<std::shared_ptr<FlyEnemy>> m_pFlyEnemy;
	// �񕜃A�C�e��
	std::vector<std::shared_ptr<RecoveryItem>> m_pRecoveryItem;
};

