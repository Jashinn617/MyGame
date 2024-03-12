#pragma once
#include <memory>

class Input;
class Player;
class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Update(Input& input);
	void Draw();

	// �w�i�̃X�N���[������
	void BackDraw();

	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const;

	// �|�C���^��ݒ肷��
	void SetPlayer(std::shared_ptr<Player> pPlyer) { m_pPlayer = pPlyer; }


private:
	// �摜�̃n���h��
	int m_titleHandle;
	int m_endHandle;
	int m_startHandle;
	int m_cursorHandle;
	int m_backHandle;
	int m_animationPlayer;

	// �摜�̃T�C�Y
	int m_titleW;
	int m_titleH;
	int m_startW;
	int m_startH;
	int m_endW;
	int m_endH;

	// �摜�̈ʒu
	float m_titleX;
	float m_titleY;
	float m_startX;
	float m_startY;
	float m_endX;
	float m_endY;
	float m_cursorX;
	float m_cursorY;

	float m_playerX;
	float m_playerY;

	// �摜�̃X�P�[���l
	float m_startScale;
	float m_endScale;

	// �w�i�̃X�N���[��
	float m_scrollX;
	int m_backW;
	int m_backH;

	// �J�[�\���ړ�
	int m_cursorCount;

	// BGM�̃n���h��
	int m_bgmHandle;
	// SE�̃n���h��
	int m_selectHandle;
	int m_startSeHandle;

	// �J�[�\���A�j���[�V����
	float m_cursorSinCount;
	float m_cursorAnimationPosX;

	// �v���C���[�̃A�j���[�V����
	int m_animFrame;
	float m_playerSinCount;
	float m_playerAnimationPosY;

	// �t�F�[�h�C���E�A�E�g
	int m_fadeAlpha;

	bool m_isSceneEnd;	// �V�[���I���t���O(true�̏ꍇ�̓V�[�����I������)

	std::shared_ptr<Player> m_pPlayer;
};

