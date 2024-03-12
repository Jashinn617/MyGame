#pragma once
#include <vector>
#include <memory>

class Player;
class UI
{
public:
	UI();
	~UI();

	// ������
	void Init();
	// �`��
	void Draw();
	// �X�V
	void Update();
	// �v���C���[�̃|�C���^�̐ݒ�
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

private:
	// �v���C���[��HP
	int m_playerHp;
	// �v���C���[�̎c�@
	int m_playerRemainingLives;
	/*UI�̉摜�̃n���h��*/
	// HP(�O)
	int m_hpHandle0;
	// HP(��)
	int m_hpHandle1;
	// UI(���O�A�~)
	int m_UIHandle0;
	// UI(�L�[�r�B)
	int m_UIHandle1;
	// UI(�o�[)
	int m_UIHandle2;
	/* UI�̃T�C�Y*/
	int m_w;
	int m_h;
	// UI�̈ʒu
	int m_UIX;
	int m_UIY;
	// �A�j���[�V�����p�̃t���[��
	int m_animationFrame;
	// �オ���Ă��邩�ǂ���
	bool m_isUp;
	/*�t�H���g�̃n���h��*/
	// �O
	int m_fontHandle;
	// ��
	int m_fontBackHandle;
	// �|�C���^�̎擾
	std::shared_ptr<Player> m_pPlayer;
};

