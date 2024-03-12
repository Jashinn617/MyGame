#pragma once
#include <memory>
#include "../util/Vec2.h"
#include "../util/Rect.h"

class Camera;
class Player;
class Inhale;
class RecoveryItem
{
public:
	RecoveryItem();
	~RecoveryItem();

	// ������
	// �����ʒu��ݒ肷�邽�߂̈�����n���Ă���
	void Init(float x, float y);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ��`���̎擾
	Rect GetRect();
	// �����蔻��̎擾
	float GetLeft()const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom()const;
	// �v���C���[�Ƃ̓����蔻��
	void PlayerCollision();
	// �z�����݂Ƃ̓����蔻��
	void InhaleCollision();
	// ������
	void DeleteExist() { m_isExist = false; }
	/*�|�C���^�̐ݒ�*/
		// �J����
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// �v���C���[
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	// ��������
	void SetInhale(std::shared_ptr<Inhale> pInhale) { m_pInhale = pInhale; }
private:
	/*�|�C���^�̎擾*/
	// �J����
	std::shared_ptr<Camera> m_pCamera;
	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// ��������
	std::shared_ptr<Inhale> m_pInhale;

	// ���W
	Vec2 m_pos;
	// �X�N���[���p�̈ʒu
	int m_x;
	int m_y;
	// �T�C�Y
	int m_w;
	int m_h;
	// �����蔻��p�̋�`
	Rect m_colRect;

	/*�O���t�B�b�N*/
	int m_handle;

	/*SE*/
	int m_hitSeHandle;
	
	/*�A�j���[�V����*/
	// �A�j���[�V�����p��Sin�̃J�E���g
	float m_sinCount;
	// �A�j���[�V�����̏c��
	float m_animationHeight;	

	// ���݂��Ă��邩�̃t���O
	bool m_isExist;
	// �z�����܂�Ă��邩�ǂ���
	bool m_isInhale;
};

