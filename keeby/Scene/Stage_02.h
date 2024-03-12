#pragma once
#include "../Game.h"
#include "../util/Rect.h"
#include "../util/Vec2.h"

#include <memory>
#include <vector>

class Camera;
class Player;
class StopEnemy;
class WalkEnemy;
class FlyEnemy;
class Input;
class UI;
class Needle;
class RecoveryItem;
class Door;
class Stage_02
{
public:
	// ���̃V�[��
	enum NextScene
	{
		kLastStage,
		kGameOver
	};
	// �_���X�̐U��t��
	enum DanceChoreography
	{
		kRotate,
		kMove
	};
	// �_���X���̌���
	enum DanceDir
	{
		kDirLeft,
		kDirRight
	};
public:
	Stage_02();
	~Stage_02();

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
	
	/*�|�C���^�̐ݒ�*/
	// �v���C���[
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	// �J����
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// UI
	void SetUI(std::shared_ptr<UI> pUI) { m_pUI = pUI; }
	// �ړ��p�̃h�A
	void SetDoor(std::shared_ptr<Door> pDoor) { m_pDoor = pDoor; }
	// �~�܂��Ă���G
	void SetStopEnemy(std::shared_ptr<StopEnemy> pStopEnemy, int i) { m_pStopEnemy[i] = pStopEnemy; }
	// �����Ă���G
	void SetWalkEnemy(std::shared_ptr<WalkEnemy> pWalkEnemy, int i) { m_pWalkEnemy[i] = pWalkEnemy; }
	// ���ł���G
	void SetFlyEnemy(std::shared_ptr<FlyEnemy> pFlyEnemy, int i) { m_pFlyEnemy[i] = pFlyEnemy; }
	// �j
	void SetNeedle(std::shared_ptr<Needle> pNeedle, int i) { m_pNeedle[i] = pNeedle; }
	// �񕜃A�C�e��
	void SetItem(std::shared_ptr<RecoveryItem> pRecoveryItem, int i) { m_pRecoveryItem[i] = pRecoveryItem; }

	/*���̃V�[���̐ݒ�*/
	// �ǂ̃V�[���ɍs�����擾����
	NextScene IsNextScene()const { return m_nextScene; }
	// ���̃V�[�����N���A�V�[���ɐݒ肷��
	NextScene GetLastStage() const { return kLastStage; }
	// ���̃V�[�����Q�[���I�[�o�[�V�[���ɐݒ肷��
	NextScene GetGameOver() const { return kGameOver; }
private:
	// ���X�^�[�g���̏�����
	void RestartInit();
	// �G�L�����N�^�[�̏�����
	void EnemyInit();
	// �j�̏�����
	void NeedleInit();
	// �A�C�e���̏�����
	void ItemInit();
	// �G�L�����N�^�[�̍X�V
	void EnemyUpdate();
	// �j�̍X�V
	void NeedleUpdate();
	// �A�C�e���̍X�V
	void ItemUpdate();
	// �w�i�̕`��
	void BackDraw();
	// �}�b�v�`�b�v�̕`��
	void ChipDraw();
	// �G�L�����N�^�[�̕`��
	void EnemyDraw();
	// �j�̕`��
	void NeedleDraw();
	// �A�C�e���̕`��
	void ItemDraw();
	// ���ʐݒ�
	void VolumeSetting();
	// �v���C���[���~�X���������̉��o
	void OnMiss();
private:
	/*�O���t�B�b�N*/
	// �Q�[�����
	int m_gameScreenHandle;
	// �w�i
	int m_background;
	// �O�i
	int m_foreground;
	// �}�b�v�`�b�v
	int m_chipHandle;
	// �S�[���C�x���g
	int m_moveFlowerHandle;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
	// �}�b�v�`�b�v�̔z�u���
	std::vector<std::vector<int>> m_chipData;

	/*BGM*/
	// �X�e�[�W��BGM
	int m_bgmHandle;

	/*SE*/
	// �~�X���o
	int m_missSeHandle;
	// �~�X�������u��
	int m_missSeHandle02;
	// �S�[���̋߂��ŗ���Ă���SE
	int m_goalSeHandle;
	// �X�e�[�W�ړ���
	int m_moveSeHandle;
	// SE�̉���
	int m_goalSeVolume;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;
	// �~�X�������ۂ̃t�F�[�h
	bool m_isMissFade;

	/*�~�X���������̉�ʂ̗h��*/
	int m_shakeFrame;

	// ���̃V�[��
	NextScene m_nextScene;

	// �~�X���������ǂ���
	bool m_isMiss;

	/*�O�i�̃X�N���[��*/
	// �X�N���[���l
	float m_scrollX;
	// ����
	int m_fgW;
	// �c��
	int m_fgH;

	// �S�[���������ǂ���
	bool m_isGoal;	

	/*�S�[����̈ړ��C�x���g*/
	// �ړ��C�x���g�̈ړ��lX
	int m_moveEventX;
	// �ړ��C�x���g�̈ړ��lY
	int m_moveEventY;
	// �ړ��C�x���g�̃t���[����
	int m_moveEventFrame;
	// �g�嗦
	float m_ExtRate;

	// �V�[�����I�����Ă��邩�ǂ���
	bool m_isSceneEnd;

	/*�|�C���^*/
	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// �J����
	std::shared_ptr<Camera> m_pCamera;
	// UI
	std::shared_ptr<UI> m_pUI;
	// �h�A
	std::shared_ptr<Door> m_pDoor;
	/*�G�l�~�[*/
	// �~�܂��Ă���G
	std::vector<std::shared_ptr<StopEnemy>> m_pStopEnemy;
	// �����G
	std::vector < std::shared_ptr<WalkEnemy>> m_pWalkEnemy;
	// ��ԓG
	std::vector<std::shared_ptr<FlyEnemy>> m_pFlyEnemy;
	/*�I�u�W�F�N�g*/
	// �j
	std::vector < std::shared_ptr <Needle>> m_pNeedle;
	// �񕜃A�C�e��
	std::vector<std::shared_ptr<RecoveryItem>> m_pRecoveryItem;
};

