#pragma once
#include <memory>
#include "../util/Vec2.h"
#include "../util/Rect.h"

class Camera;
class Player;
class Inhale;
class Vomit;
class AirBullet;
class WalkEnemy
{
public:
	// ����
	enum Dir
	{
		kDirLeft,
		kDirRight
	};

public:
	WalkEnemy();
	~WalkEnemy();

	// ������
	// �����ʒu��ݒ肷�邽�߂̈�����n���Ă���
	void Init(float x, float y, int cycle);
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
	/*�v���C���[�̍U���Ƃ̓����蔻��*/
	// �z�����݂Ƃ̓����蔻��
	void InhaleCollision();
	// �f���o���Ƃ̓����蔻��
	void VomitCollision();
	// ��C�e�Ƃ̓����蔻��
	void AirBulletCollision();
	// ������
	void DeleteExist() { m_isExist = false; }

	/*�|�C���^�̐ݒ�*/
	// �J����
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// �v���C���[
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	// ��������
	void SetInhale(std::shared_ptr<Inhale> pInhale) { m_pInhale = pInhale; }
	// �f���o��
	void SetVomit(std::shared_ptr<Vomit> pVomit) { m_pVomit = pVomit; }
	// ��C�e
	void SetAirBullet(std::shared_ptr<AirBullet>pAriBullet) { m_pAirBullet = pAriBullet; }
private:
	/*�|�C���^�̎擾*/
		// �J����
	std::shared_ptr<Camera> m_pCamera;
	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// ��������
	std::shared_ptr<Inhale> m_pInhale;
	// �f���o��
	std::shared_ptr<Vomit> m_pVomit;
	// ��C�e
	std::shared_ptr<AirBullet> m_pAirBullet;

	// ���W
	Vec2 m_pos;
	// �X�N���[���p�̍��W
	int m_x;
	int m_y;
	// �G�l�~�[�̃T�C�Y
	int m_w;
	int m_h;
	// �����蔻��p�̋�`
	Rect m_colRect;
	// �G�l�~�[�̌���
	Dir m_dir;

	/*�O���t�B�b�N*/
	// �ʏ�
	int m_handle;
	// �������܂ꒆ
	int m_damageHandle;
	// �e�ɓ���������
	int m_damageEffectHandle;

	/*SE*/
	// �U���ɓ���������
	int m_hitSeHandle;

	/*�A�j���[�V����*/
	// �A�j���[�V�����̃t���[����
	int m_walkAnimFrame;
	// �܂�Ԃ��p�̃t���[����
	int m_walkFrame;
	// �܂�Ԃ��p�x
	int m_walkCycle;
	// �ړ��X�s�[�h
	int m_speed;

	/*������Ƃ��̉��o*/
	// �_���[�W���󂯂����ǂ���
	bool m_isDamage;
	// �_���[�W���󂯂Ă���̃t���[����
	int m_damageFrame;
	
	// ���݂��Ă��邩�̃t���O
	bool m_isExist;
	// �z�����܂�Ă��邩�ǂ���
	bool m_isInhale;	
};

