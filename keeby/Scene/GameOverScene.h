#pragma once
#include "../util/Input.h"
#include <memory>

class Player;
class GameOverScene
{
public:
	enum NextScene
	{
		kStage01,
		kTitle
	};

public:
	GameOverScene();
	~GameOverScene();

	// ������
	void Init();
	// �X�V
	void Update(Input& input);
	// �`��
	void Draw();
	// �V�[���I�����̏���
	void End();
	// �V�[�����I���������ǂ���
	bool IsSceneEnd();
	// ���̃V�[��
	NextScene IsNextScene() const { return m_nextScene; }
	// ���̃V�[����ύX����
	void ChangeNextScene(NextScene nextScene) { m_nextScene = nextScene; }
	NextScene GetTitle() const { return kTitle; }
	NextScene GetStage01() const { return kStage01; }

	// �v���C���[�̃|�C���^��ݒ肷��
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
private:
	/*�O���t�B�b�N*/
	int m_gameOverBg;
	int m_gameEndLogo;
	int m_gameOverLogo;
	int m_continueLogo;
	int m_cursor;
	int m_gameOverChara;

	/*BGM*/
	int m_bgmHandle;

	/*SE*/
	int m_gameEndSeHandle;
	int m_continueSeHandle;

	// �摜�̃T�C�Y
	int m_endW;
	int m_endH;
	int m_continueW;
	int m_continueH;
	int m_gameOverW;
	int m_gameOverH;

	// �摜�̈ʒu
	float m_gameOverX;
	float m_gameOverY;
	float m_continueX;
	float m_continueY;
	float m_endX;
	float m_endY;
	float m_cursorX;
	float m_cursorY;

	// �摜�̃X�P�[���l
	float m_continueScale;
	float m_endScale;

	// �J�[�\���ړ��p�̃J�E���g
	int m_cursorCount;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;
	// ���̃V�[���̐ݒ�
	NextScene m_nextScene;

	// �|�C���^�̎擾
	std::shared_ptr<Player> m_pPlayer;

	// �V�[�����I���������ǂ���
	bool m_isSceneEnd;
};

