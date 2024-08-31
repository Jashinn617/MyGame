#pragma once
#include "DxLib.h"
#include "../CharacterBase.h"
#include "../../Util/CharacterData.h"

#include <array>
#include <memory>
#include <vector>

class Input;
class Camera;

class Model;
class Circle;

class Player_ : public CharacterBase
{
public:
	// ���
	enum class State : int
	{
		Idle = 0,		// �ҋ@
		Walk = 1,		// ����
		Dash = 2,		// �_�b�V��
		Jump = 3,		// �W�����v
		KnockBack = 4,	// �m�b�N�o�b�N
	};

public:
	Player_();
	~Player_();

	void Init();
	void Update(Input& input) override final;
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	void Draw2D() override final;

	void StageClear() override final;

	/// <summary>
	/// �U�����󂯂�
	/// </summary>
	/// <param name="targetPos"></param>
	void OnDamage(VECTOR targetPos) override final;

	/// <summary>
	/// �U��������
	/// </summary>
	void OnAttack() override final;

	void EndJump() override final;

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

private:
	void AngleUpdate();

	State UpdateMoveParamerer(VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);

	VECTOR MoveUpdate(Input& input);

	/// <summary>
	/// �ړ������̍X�V
	/// </summary>
	void MoveDirectionUpdate(Input& input);

	/// <summary>
	/// �A�j���[�V�����X�e�[�g�̍X�V
	/// </summary>
	/// <param name="prevState"></param>
	void UpdateAnimState(State prevState);

private:
	float m_walkSpeed;	// �ړ����x
	float m_dashSpeed;	// �_�b�V�����̑��x
	float m_acc;		// �����x

	bool m_isMove;	// ���̃t���[���œ��������ǂ���
	bool m_isDash;	// �_�b�V�������ǂ���

	VECTOR m_moveDirectVec;	// �ړ������x�N�g��
	VECTOR m_cameraToPlayerVec;	// �v���C���[����J�����܂ł̋���

	State m_currentState;		// ���݂̏��

	std::shared_ptr<Time> m_pInvincibleTime;	// ���G����
	std::shared_ptr<Camera> m_pCamera;			// �J�����|�C���^

};

