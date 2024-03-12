#pragma once
#include "../util/Vec2.h"
#include "../util/Rect.h"

#include <memory>
#include <vector>

class Player;
class Camera;
class Input;
class GoalFlower;
class UI;
class Boss;
class LastStage
{
public:
	// ���̃V�[��
	enum NextScene
	{
		kClear,
		kGameOver
	};

public:
	LastStage();
	~LastStage();

	// ������
	void  Init();
	// �X�V
	void Update(Input& input);
	// �`��
	void Draw();
	// �I������
	void End();
	// �V�[�����I���������ǂ���
	bool IsSceneEnd() const;

	// ���X�^�[�g���̏�����
	void RestartInit();
	// �w�i�̕`��
	void BackDraw();
	// �}�b�v�`�b�v�̕`��
	void ChipDraw();
	// �v���C���[���~�X���������̉��o
	void OnMiss();
	// �N���A���̉��o
	void ClearPerformance();

	/*�|�C���^�̏�����*/
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	void SetUI(std::shared_ptr<UI> pUI) { m_pUI = pUI; }
	void SetFlower(std::shared_ptr<GoalFlower> pFlower) { m_pFlower = pFlower; }
	void SetBoss(std::shared_ptr<Boss> pBoss) { m_pBoss = pBoss; }

	/*���̃V�[���̐ݒ�*/
	// �ǂ̃V�[���ɍs�����擾����
	NextScene IsNextScene()const { return m_nextScene; }
	// ���̃V�[�����N���A�V�[���ɐݒ肷��
	NextScene GetClear() const { return kClear; }
	// ���̃V�[�����Q�[���I�[�o�[�V�[���ɐݒ肷��
	NextScene GetGameOver() const { return kGameOver; }

private:
	/*�O���t�B�b�N*/
	// �Q�[�����
	int m_gameScreenHandle;
	// �w�i
	int m_bgHandle;
	// �O�i
	int m_fgHandle;
	// �}�b�v�`�b�v
	int m_chipHandle;
	// �S�[���C�x���g
	int m_moveFlowerHandle;
	// �{�X�L�����N�^�[
	int m_bossHandle;

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
	// �Ԃł̈ړ�����SE
	int m_flowerMoveSeHandle;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;
	// �~�X�������ۂ̃t�F�[�h
	bool m_isMissFade;

	/*�{�X��*/
	bool m_isBossExist;

	/*�~�X���������̉�ʂ̗h��*/
	int m_shakeFrame;

	// ���̃V�[��
	NextScene m_nextScene;

	// �~�X���������ǂ���
	bool m_isMiss;
	
	/*�w�i�̃X�N���[��*/
	// �X�N���[���l
	float m_scrollX;
	// ����
	int m_backW;
	// �c��
	int m_backH;

	// �N���A�������ǂ���
	bool m_isClear;

	/*�S�[����̈ړ��C�x���g*/
	// �ړ��C�x���g�̈ړ��lX
	int m_moveEventX;
	// �ړ��C�x���g�̈ړ��lY
	int m_moveEventY;
	// �ړ��C�x���g�̃t���[����
	int m_moveEventFrame;
	// �g�嗦
	float m_extRate;

	// �V�[�����I�����Ă��邩�ǂ���
	bool m_isSceneEnd;

	// �|�C���^�̐ݒ�
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<UI> m_pUI;
	std::shared_ptr<GoalFlower> m_pFlower;
	std::shared_ptr<Boss> m_pBoss;
};

