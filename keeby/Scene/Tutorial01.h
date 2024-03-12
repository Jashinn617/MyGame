#pragma once
#include "../util/Vec2.h"
#include "../util/Rect.h"

#include <memory>
#include <vector>

class Player;
class Camera;
class Input;
class UI;
class Door;
class Tutorial01
{
public:
	Tutorial01();
	~Tutorial01();

	// ������
	void  Init();
	// �X�V
	void Update(Input& input);
	// �`��
	void Draw();
	// �}�b�v�`�b�v�̕`��
	void ChipDraw();
	// �w�i�̕`��
	void BackDraw();
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

private:
	/*�O���t�B�b�N*/
	// �O�i
	int m_fgHandle;
	// �w�i
	int m_bgHandle;
	// �}�b�v�`�b�v
	int m_chipHandle;
	// �{�^��
	int m_buttonHandle;
	// �����p�E�B���h�E
	int m_windowTextHandle[7];
	// ���
	int m_arrowHandle;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
	// �}�b�v�`�b�v�̔z�u���
	std::vector<std::vector<int>> m_chipData;

	// �{�^���̃A�j���[�V����
	int m_buttonAnimFrame;
	// ���̓_�ŃA�j���[�V����
	int m_blinkingArrowAnimFrame;

	/*BGM*/
	int m_bgmHandle;

	/*SE*/
	// �{�^�����������Ƃ�
	int m_pushSeHandle;
	// �X�e�[�W�ړ���
	int m_moveSeHandle;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;

	// �E�B���h�E�̃J�E���g
	int m_tutorialCount;

	// �w�i�̃X�N���[��
	float m_scrollX;
	int m_backW;
	int m_backH;

	// ����ł��邩�ǂ���
	bool m_isOperation;
	// �h�A�����݂��Ă��邩�ǂ���
	bool m_isDoor;
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
};

