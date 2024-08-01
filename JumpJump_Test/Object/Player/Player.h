#pragma once
#include "DxLib.h"
#include "../../Util/CharacterData.h"
#include "../CharacterBase.h"

#include <array>
#include <memory>
#include <vector>

class Input;
class Camera;
class StageTest;

class Model;
class Circle;
class PlayerState;
class Stamina;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update() override final;
	virtual void Draw();

private:	// �֐�
	/// <summary>
	/// �X�^�~�i��ω������邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool ChangeStaminaValue();

	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	void CameraUpdate();

	/// <summary>
	/// �p�x�̍X�V
	/// </summary>
	void AngleUpdate();

	/// <summary>
	/// �ړ������̍X�V
	/// </summary>
	void MoveDirectionUpdate();

	/// <summary>
	/// �ړ�
	/// </summary>
	/// <returns></returns>
	VECTOR MoveUpdate();

private:	// �����o�֐��p�֐�

	/*�e��Ԃ̏�����*/
	void IdleInit() {};
	void WalkInit() {};
	void DashInit() {};
	void JumpInit() {};
	void KnockBackInit() {};

	/*�e��Ԃ̍X�V*/
	void IdleUpdate();
	void WalkUpdate();
	void DashUpdate();
	void JumpUpdate();
	void KnockBackUpdate();

private:	// �ϐ�
	float m_walkSpeed;	// �ړ����x
	float m_dashSpeed;	// �_�b�V�����̑��x
	float m_acc;	// �����x

	bool m_isStageClear;	// �X�e�[�W���N���A�������ǂ���

	VECTOR m_moveDirectVec;	// �ړ������x�N�g��
	VECTOR m_cameraToPlayer;	// �v���C���[����J�����܂ł̋���

	std::shared_ptr<PlayerState> m_pState;		// ��Ԃ̃|�C���^
	std::shared_ptr<Stamina> m_pStamina;		// �X�^�~�i�̃|�C���^
	std::shared_ptr<Time> m_pInvincibleTime;	// �U����H�������̖��G����
	std::shared_ptr<Camera> m_pCamera;			// �J�����|�C���^�̎擾
};

