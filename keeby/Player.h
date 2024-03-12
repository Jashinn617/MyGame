#pragma once
#include "util/Vec2.h"
#include "util/Rect.h"

#include <memory>
#include <vector>

class Vomit;
class Inhale;
class AirBullet;
class Input;
class Camera;
class StopEnemy;
class WalkEnemy;
class Player
{
public:
	// �v���C���[�̌���
	enum Dir
	{
		kDirRight,	// �E
		kDirLeft	// ��
	};
	// �v���C���[�̏��
	enum Condition
	{
		kMove,		// �ړ�
		kInhale,	// ��������
		kVomit,		// �f���o��
		kGulp,		// �ق��΂�
		kJump,		// �W�����v
		kHovering,	// �z�o�����O
		kFall,		// ����
		kMiss,		// �~�X
		kDance		// �_���X
	};
	// �_���X�̐U��t��
	enum DanceChoreography
	{
		kRotate,		// ��]
		kLateralMove	// ���ړ�
	};

public:
	Player();
	~Player();

	// ������
	void Init();
	// �`��
	void Draw();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	/// <param name="mapData">�}�b�v�`�b�v�̔z�u���</param>
	/// <param name="chipNumX">�}�b�v�`�b�v�̉��̔z�u��</param>
	/// <param name="chipNumY">�}�b�v�`�b�v�̏c�̔z�u��</param>
	/// <param name="chipWidth">�}�b�v�`�b�v��̉���</param>
	/// <param name="chipHeight">�}�b�v�`�b�v��̏c��</param>
	void Update(Input& input,
		std::vector<std::vector<int>> mapData,
		int chipNumX, int chipNumY,
		int chipWidth, int chipHeight);
	/// <summary>
	/// �}�b�v�`�b�v�Ƃ̓����蔻��̎擾
	/// </summary>
	/// <param name="mapData">�}�b�v�`�b�v�̔z�u���</param>
	/// <param name="chipNumX">�}�b�v�`�b�v�̉��̔z�u��</param>
	/// <param name="chipNumY">�}�b�v�`�b�v�̏c�̔z�u��</param>
	/// <param name="chipWidth">�}�b�v�`�b�v��̉���</param>
	/// <param name="chipHeight">�}�b�v�`�b�v��̏c��</param>
	/// <param name="playerRect">�v���C���[�̓����蔻��̋�`</param>
	/// <param name="chipRect">�}�b�v�`�b�v�̓����蔻��̋�`</param>
	/// <returns>�}�b�v�`�b�v�Ɠ������Ă��邩�ǂ���</returns>
	bool IsMapCollision(std::vector<std::vector<int>> mapData,
		int chipNumX, int chipNumY,
		int chipWidth, int chipHeight,
		Rect playerRect,
		Rect& chipRect);
	// �_���X�̕`��
	void DanceDraw();
	// �z������
	void AttackInhale(Input& input);
	// �f���o��
	void AttackVomit(Input& input);
	// ��C�e
	void AttackAirBullet(Input& input);
	// �����蔻��̎擾
	Rect GetColRect()const { return m_colRect; }
	// �����蔻��̋�`���(�}�b�v�`�b�v)
	Rect GetRect();
	// �����蔻��̋�`���(�}�b�v�`�b�v�ȊO)
	Rect GetColRect();

	// �������W�̐ݒ�
	void SetStartPos(float posX, float posY);	
	// �J�����̃|�C���^�̐ݒ�
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }

	// �U���̃|�C���^�̐ݒ�
	// ��������
	void SetInhale(std::shared_ptr<Inhale> pInhale) { m_pInhale = pInhale; }
	// �f���o��
	void SetVomit(std::shared_ptr<Vomit> pVomit) { m_pVomit = pVomit; }
	// ��C�e
	void SetAirBullet(std::shared_ptr<AirBullet>pAriBullet) { m_pAirBullet = pAriBullet; }

	// �c�@�����炷
	void DeleteLives() { --m_remainingLives; }
	// �v���C���[�̎c�@��S������
	void CompleteRecoveryLives();
	// HP��S������
	void CompleteRecoveryHp();
	// HP���񕜂���
	void RecoveryHp2();
	// �d�͂����Z�b�g����
	void GravityReset() { m_move.y = 0; }
	// ���̂��z�����񂾎��ɏ�Ԃ��ق��΂��Ԃɂ���
	void OnGlup() { m_condition = kGulp; m_isGlup = true; }
	// �_���[�W���󂯂�
	void OnDamage();
	// �_���[�W�����ǂ���
	bool IsDamege()const { return m_isDamage; }
	// �~�X������
	void OnMiss();
	// �v���C���[�̃~�X���o�p�̃t���[�����̎擾
	int GetMissFrame()const { return static_cast<int>(m_missFrame); }
	/*�ǂ̂悤�Ƀ~�X��������*/
	// �����ă~�X������
	void FellMiss() { m_isFellMiss = true; }
	// HP���[���ɂȂ��ă~�X������
	void DamageMiss() { m_isDamageMiss = true; }
	// �N���A���o�̃_���X
	void OnDance();

	/*�����蔻��̎擾(�}�b�v�`�b�v)*/
	float GetLeft()const { return m_pos.x - m_w * 0.5f; }
	float GetRight() const { return m_pos.x + m_w * 0.5f; }
	float GetTop() const { return m_pos.y - m_h; }
	float GetBottom()const { return m_pos.y; }
	/*�����蔻��̎擾(�}�b�v�`�b�v�ȊO)*/
	float GetColLect()const;
	float GetColRight()const;
	float GetColTop()const;
	float GetColBottom()const;
	// �����̎擾
	int GetW()const { return m_w; }
	// �c���̎擾
	int GetH()const { return m_h; }
	// �ʒu�̎擾
	float GetX()const { return m_pos.x; }
	float GetY()const { return m_pos.y; }
	// HP�̎擾
	int GetHp()const { return m_hp; }
	// �c�@�̎擾
	int GetRemainingLives() const { return m_remainingLives; }
	// �����̎擾
	Dir GetDir()const { return m_dir; }
	Dir GetDirLeft()const { return kDirLeft; }
	Dir GetDirRight()const { return kDirRight; }
	// �Ԃł̈ړ������ǂ���
	bool IsFlowerMove()const { return m_isFlowerMove; }

	bool IsMiss()const { return m_isMiss; }
	

private:
	// ���W
	Vec2 m_pos;
	// �ړ��l
	Vec2 m_move;
	// �����蔻��p�̋�`
	Rect m_colRect;
	// ���݂̏��
	Condition m_condition;
	// �����Ă������
	Dir m_dir;
	// �X�N���[���p�̈ʒu
	float m_x;
	float m_y;
	// �v���C���[�̃T�C�Y
	int m_w;
	int m_h;

	/*�����G�̃n���h��*/
	// ����
	int m_walkHandle;
	// ��������
	int m_inhaleHandle;
	// �z�o�����O
	int m_hoveringHandle;
	// �ق��΂�
	int m_gulpHandle;
	// �W�����v
	int m_jumpHandle;
	// �~�X
	int m_missHandle;
	// �N���A��̃_���X1
	int m_danceHandle1;
	// �N���A��̃_���X2
	int m_danceHandle2;

	/*BGM�̃n���h��*/
	// �N���A��
	int m_clearBgmHandle;

	/*SE�̃n���h��*/
	// ��������
	int m_inhaleSeHandle;
	// �W�����v
	int m_jumpSeHandle;
	// �f���o���A��C�e
	int m_attackSeHandle;
	// �_���[�W
	int m_damageSeHandle;

	// �������x
	float m_fallSpeed;
	// �W�����v������(�z�o�����O�p)
	int m_jumpCount;
	// HP
	int m_hp;
	// �c�@
	int m_remainingLives;
	// �G���ق��΂��Ă��邩�ǂ���
	bool m_isGlup;
	// �G��f���o�������ǂ���
	bool m_isVomit;
	// �G��f���o���Ă���ǂ̂��炢�o������
	int m_vomitFrame;
	// �A�j���[�V����
	int m_animFrame;
	// �_���[�W���󂯂Ă���̃t���[����
	int m_damageFrame;
	// �_���[�W�����ǂ���
	bool m_isDamage;
	// �~�X���������ǂ���
	bool m_isMiss;
	// �~�X�����Ă���̃t���[����
	float m_missFrame;
	// ������Ƃ��̉�]
	float m_missRotate;

	/*�����̃~�X���_���[�W�̃~�X��*/
	// �������Ƃ�
	bool m_isFellMiss;
	// HP���[���ɂȂ����Ƃ�
	bool m_isDamageMiss;

	/*�N���A���o*/
	// �_���X�����ǂ���
	bool m_isDance;
	// �Ԃ��ړ����Ă��邩�ǂ���
	bool m_isFlowerMove;
	// �C�x���g���̃t���[����
	int m_eventFrame;
	// �_���X�̉�]�x
	float m_danceRotate;
	// �_���X�̉�]�p�^�[��
	int m_rotatePattern;
	// �_���X��Sin�̏c��
	float m_danceSinCount;
	// �_���X�̏c�̂ӂ蕝
	float m_danceAnimationPosY;
	// �_���X�̐U�t
	DanceChoreography m_choreography;
	// �_���X�̃A�j���[�V�����̃t���[����
	int m_danceAnimFrame;

	/*�S�[����̈ړ��C�x���g*/
	// �ړ��C�x���g�̈ړ��lX
	int m_moveEventX;
	// �ړ��C�x���g�̈ړ��lY
	int m_moveEventY;
	// �ړ��C�x���g�̃t���[����
	int m_moveEventFrame;	

	/*�e�|�C���^�̎擾*/
	// ��C�e
	std::shared_ptr<AirBullet> m_pAirBullet;
	// ��������
	std::shared_ptr<Inhale> m_pInhale;
	// �f���o��
	std::shared_ptr<Vomit> m_pVomit;
	// �J����
	std::shared_ptr<Camera> m_pCamera;

};

