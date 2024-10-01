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
class DamageShader;

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
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	void Draw2D() override final;

	void StageClear() override final;

	void GameEnd() override final;

	/// <summary>
	/// �U�����󂯂�
	/// </summary>
	/// <param name="targetPos"></param>
	void OnDamage(VECTOR targetPos) override final;

	/// <summary>
	/// �U��������
	/// </summary>
	void OnAttack() override final;

	/// <summary>
	/// �W�����v��Ԃ̏I��
	/// </summary>
	void EndJump() override final;	

	/// <summary>
	/// �W�����v�͂̐ݒ�
	/// </summary>
	/// <param name="jumpPower"></param>
	void SetJumpPower(float jumpPower) { m_jumpPower = jumpPower; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns></returns>
	const VECTOR& GetPos()const { return m_info.pos; }

	/// <summary>
	/// �����蔻��̎�ނ̎擾
	/// </summary>
	/// <returns></returns>
	ColType GetColType()const { return ColType::Player; }

	/// <summary>
	/// �J�����̎擾
	/// </summary>
	/// <returns></returns>
	const std::shared_ptr<Camera> GetCamera() const { return m_pCamera; }

private:	// �֐�
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
	void JumpInit();
	void KnockBackInit() {};
	void StageClearInit() {};

	/*�e��Ԃ̍X�V*/
	void IdleUpdate();
	void WalkUpdate();
	void DashUpdate();
	void JumpUpdate();
	void KnockBackUpdate();
	void StageClearUpdate();

private:	// �ϐ�
	float m_walkSpeed;	// �ړ����x
	float m_dashSpeed;	// �_�b�V�����̑��x
	float m_acc;	// �����x

	bool m_isStageClear;	// �X�e�[�W���N���A�������ǂ���

	VECTOR m_moveDirectVec;	// �ړ������x�N�g��
	VECTOR m_cameraToPlayerVec;	// �v���C���[����J�����܂ł̋���


	std::shared_ptr<PlayerState> m_pState;		// ��Ԃ̃|�C���^
	std::shared_ptr<Time> m_pInvincibleTime;	// �U����H�������̖��G����
	std::shared_ptr<Camera> m_pCamera;			// �J�����|�C���^�̎擾
};

