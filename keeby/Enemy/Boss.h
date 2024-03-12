#pragma once
#include <memory>
#include "../util/Vec2.h"
#include "../util/Rect.h"


class Camera;
class Player;
class Inhale;
class Vomit;
class Boss
{
public:
	Boss();
	~Boss();

	// ������
	// �����ʒu��ݒ肷�邽�߂̈�����n���Ă���
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ��`���̎擾
	Rect GetRect();
	Rect GetLeftFlowerRect();
	Rect GetRightFlowerRect();

	// �����蔻��̎擾
	float GetLeft()const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom()const;

	// ����ɗ�����Ԃ̓����蔻��̎擾
	// ���̉�
	float GetLeftFlowerLeft()const;
	float GetLeftFlowerRight()const;
	float GetLeftFlowerTop()const;
	float GetLeftFlowerBottom()const;
	// �E�̉�
	float GetRightFlowerLeft()const;
	float GetRightFlowerRight()const;
	float GetRightFlowerTop()const;
	float GetRightFlowerBottom()const;

	// �v���C���[�Ƃ̓����蔻��
	void PlayerCollision();
	void PlayerToLeftFlowerCollision();
	void PlayerToRightFlowerCollision();
	/*�v���C���[�̍U���̓����蔻��*/
	// �f���o���Ƃ̓����蔻��
	void VomitCollision();
	void InhaleToLeftFlowerCollision();
	void InhaleToRightFlowerCollision();

	// ������
	void DeleteExist() { m_isExist = false; }
	// ���E�̉Ԃ̕`��
	void FlowerDraw();

	/*�U��*/
	// �����ɗ�����W�����v
	void JumpCenterFellAttack();
	// �����ɗ�����W�����v
	void JumpLeftFellAttack();
	// �E���ɗ�����W�����v
	void JumpRightFellAttack();
	/*�|�C���^�̐ݒ�*/
	// �J����
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// �v���C���[
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	// �f���o��
	void SetVomit(std::shared_ptr<Vomit> pVomit) { m_pVomit = pVomit; }
	// �z������
	void SetInhale(std::shared_ptr<Inhale> pInhale) { m_pInhale = pInhale; }

	// �{�X�킪�I����Ă��邩�ǂ���
	bool IsBossEnd()const { return m_isBossEnd; }

	// ���݂��Ă��邩�ǂ���
	bool IsExist()const { return m_isExist; }

private:
	/*�|�C���^�̎擾*/
	// �J����
	std::shared_ptr<Camera> m_pCamera;
	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// �f���o��
	std::shared_ptr<Vomit> m_pVomit;
	// �z������
	std::shared_ptr<Inhale> m_pInhale;

	// ���W
	Vec2 m_pos;
	// �X�N���[���p�̍��W
	float m_x;
	float m_y;
	// ���̉Ԃ̍��W
	Vec2 m_leftFlowerPos;
	// �X�N���[���p�̍��W
	float m_leftFlowerX;
	float m_leftFlowerY;
	// �E�̉Ԃ̍��W
	Vec2 m_rightFlowerPos;
	// �X�N���[���p�̍��W
	int m_rightFlowerX;
	int m_rightFlowerY;
	// �T�C�Y
	float m_w;
	float m_h;
	// �����蔻��p�̋�`
	Rect m_colRect;
	Rect m_leftFlowerColRect;
	Rect m_rightFlowerColRect;

	/*�O���t�B�b�N*/
	// �ʏ�
	int m_normalHandle;
	// �e�ɓ���������
	int m_damageHandle;
	// �W�����v�̏���
	int m_preparationHandle;
	// ���E�ɗ������
	int m_flowerHandle;

	/*SE*/
	// �e�ɓ���������
	int m_hitSeHandle;
	// �n�ʂɒ��n�����Ƃ�
	int m_landingSeHandle;
	// ������Ƃ�
	int m_fellSeHandle;
	// ������
	int m_preparationSeHandle;
	// �|�ꂽ��
	int m_endSeHandle;

	/*�A�j���[�V����*/
	// �A�j���[�V�����p��Sin�̃J�E���g
	float m_sinCount;
	// �A�j���[�V�����̏c��
	float m_animationHeight;

	/*�Z���o*/
	// �ҋ@�����ǂ���
	bool m_isStandBy;
	// �U�����o�̃t���[����
	float m_attackIntervalFrame;

	/*�W�����v*/
	// �W�����v�����ǂ���
	// ����
	bool m_isCenterJump;
	// ��
	bool m_isLeftJump;
	// �E
	bool m_isRightJump;
	// ��A�̓����̃t���[����
	int m_jumpFrame;
	// ���������ǂ���
	bool m_isJumpPreparation;
	// �㏸�����ǂ���
	bool m_isJumpRise;
	// ���������ǂ���
	bool m_isJumpFell;
	// ��ʒu�ɖ߂��Ă���r�����ǂ���
	bool m_isJumpFixedPos;
	// ��ʒu�ɖ߂������ǂ���
	bool m_isJumpFixedEndPos;
	// �Ԃ����݂��Ă��邩�ǂ���
	bool m_isLeftFlower;
	bool m_isRightFlower;
	// �Ԃ����݂���t���[����
	int m_flowerFrame;
	// �Ԃ��z���Ă����Ԃ�
	bool m_isFlowerInhale;
	// �Ԃ̉�]
	float m_flowerRotate;

	/*�_���[�W���o*/
	// �_���[�W���󂯂����ǂ���
	bool m_isDamage;
	// �_���[�W���󂯂Ă���̃t���[����
	int m_damageFrame;

	// HP
	int m_hp;

	// �{�X�킪�I��������ǂ���
	bool m_isBossEnd;
	// �{�X�킪�I����Ă���̃t���[����
	int m_BossEndFrame;

	bool m_isEndSe;

	float m_bossRotate;

	// ���݂��Ă��邩�̃t���O
	bool m_isExist;

	// ��
	unsigned int m_Color;
};

