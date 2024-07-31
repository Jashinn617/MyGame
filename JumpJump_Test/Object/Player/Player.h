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
	void JumpInit();
	void KnockBackUpdate();

private:	// �ϐ�
	float m_walkSpeed;	// �ړ����x
	float m_dashSpeed;	// �_�b�V�����̑��x
	float m_acc;	// �����x

	VECTOR m_moveDirectVec;	// �ړ������x�N�g��
	VECTOR m_cameraToPlayer;	// �v���C���[����J�����܂ł̋���

	std::shared_ptr<PlayerState> m_pState;		// ��Ԃ̃|�C���^
	std::shared_ptr<Stamina> m_pStamina;		// �X�^�~�i�̃|�C���^
	std::shared_ptr<Time> m_pInvincibleTime;	// �U����H�������̖��G����
	std::shared_ptr<Camera> m_pCamera;			// �J�����|�C���^�̎擾





















//public:
//	// ���
//	enum class State : int
//	{
//		Idle = 0,		// �����~�܂�
//		Walk = 1,		// ����
//		Run = 2,		// ����
//		Jump = 3,		// �W�����v
//	};
//
//	// �A�j���[�V�������
//	enum class AnimKind :int
//	{
//		None = -1,		// ����
//		Unknown = 0,	// �s��
//		Walk = 14,		// ����
//		Run = 11,		// ����
//		Jump = 6,		// �W�����v
//		Fall = 7,		// ����
//		Idle = 3,		// �����~�܂�
//	};
//
//public:
//	Player();
//	~Player();
//
//	/// <summary>
//	/// ����������
//	/// </summary>
//	void Init();
//
//	/// <summary>
//	/// �X�V����
//	/// </summary>
//	/// <param name="input">����</param>
//	/// <param name="camera">�J����</param>
//	/// <param name="stage">���݂̏��</param>
//	void Update(const Input& input, const Camera& camera, StageTest& stage);
//
//	/// <summary>
//	/// �`�揈��
//	/// </summary>
//	void Draw();
//
//	/// <summary>
//	/// �I������
//	/// </summary>
//	void End();
//
//	/// <summary>
//	/// �ʒu�̎擾
//	/// </summary>
//	/// <returns>���݈ʒu</returns>
//	const VECTOR& GetPos()const { return m_pos; }
//
//	/// <summary>
//	/// ���݈ړ������̎擾
//	/// </summary>
//	/// <returns>���݈ړ�����</returns>
//	bool GetIsMove() const { return m_isMove; }
//
//	/// <summary>
//	/// ��Ԃ̎擾
//	/// </summary>
//	/// <returns>���݂̏��</returns>
//	State GetState()const { return m_currentState; }
//
//	/// <summary>
//	/// �W�����v�̍����̎擾
//	/// </summary>
//	/// <returns>�W�����v�̍���</returns>
//	float GetJumpPower()const { return m_nowJunpPower; }
//
//	/// <summary>
//	/// �V��ɓ����������̏���
//	/// </summary>
//	void OnHitRoof();
//
//	/// <summary>
//	/// ���ɓ����������̏���
//	/// </summary>
//	void OnHitFloor();
//
//	/// <summary>
//	/// ��������
//	/// </summary>
//	void OnFall();
//
//private:	// �֐�
//
//	/// <summary>
//	/// ���[�g�t���[����Z�������̈ړ��p�����[�^�𖳌��ɂ���
//	/// �A�j���[�V������A�����蔻��ɕs����N���Ȃ��悤�ɂ��邽�߂Ɏg�p����
//	/// </summary>
//	void DisableRootFrameZMove();
//
//	/// <summary>
//	/// ���͂ɂ��p�����[�^��ݒ肷��
//	/// </summary>
//	/// <param name="input">����</param>
//	/// <param name="camera">�J����</param>
//	/// <param name="upMoveVec">������̈ړ��x�N�g��</param>
//	/// <param name="leftMoveVec">�������̈ړ��x�N�g��</param>
//	/// <param name="moveVec">�ړ��x�N�g��</param>
//	/// <returns>���݂̏��</returns>
//	State UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
//
//	/// <summary>
//	/// �ړ�
//	/// </summary>
//	/// <param name="moveVec">�ړ��x�N�g��</param>
//	/// <param name="stage">���݂̏��</param>
//	void Move(const VECTOR& moveVec, StageTest& stage);
//
//	/// <summary>
//	/// �X�^�~�i�̏���
//	/// </summary>
//	void Stamina();
//	
//	/// <summary>
//	/// ��]����
//	/// </summary>
//	void UpdateAngle();
//
//	/// <summary>
//	/// �A�j���[�V�����X�e�[�g�̍X�V
//	/// </summary>
//	/// <param name="prevState"></param>
//	void UpdateAnimationState(State prevState);
//
//	/// <summary>
//	/// �A�j���[�V�����̍X�V
//	/// </summary>
//	/// <param name="attachNo">���݂̃A�j���[�V�����ԍ�</param>
//	/// <returns>���[�v���Ă��邩�ǂ���</returns>
//	bool LoopAnim(int attachNo);
//
//	/// <summary>
//	/// �A�j���[�V�����̓���ւ�
//	/// </summary>
//	/// <param name="animIndex">����ւ���A�j���[�V�����̔ԍ�</param>
//	void ChangeAnim(int animIndex);
//
//
//
//private:	// �ϐ�
//	VECTOR m_pos;					// ���W
//	VECTOR m_targetDir;				// �������������̃x�N�g��
//	float m_angle;					// �����Ă���p�x
//	float m_nowJunpPower;			// �W�����v���̌��݂̑��x
//	float m_stamina;				// �X�^�~�i
//	int m_modelHandle;				// ���f���n���h��
//
//	std::vector<int> m_psHs;		// �s�N�Z���V�F�[�_�n���h��
//	std::vector<int> m_vsHs;		// ���_�V�F�[�_�n���h��
//	std::vector<int> m_pixelShaderNumbers;	// �ǂ̃s�N�Z���V�F�[�_���g����
//	std::vector<int> m_vertexShaderNumbers;	// �ǂ̒��_�V�F�[�_���g����
//
//	State m_currentState;				// ���݂̏��
//
//	int m_currentAnimNo;			// ���Đ����Ă���A�j���[�V�����̔ԍ�
//	int m_prevAnimNo;				// �O�̍Đ��A�j���[�V�����̔ԍ�
//	float m_nowAnimCount;			// �Đ����Ă���A�j���[�V�����̍Đ�����
//	float m_prevAnimCount;			// �O�̍Đ��A�j���[�V�����̍Đ�����
//	float m_animBlendRate;			// �O�ƍ��̃A�j���[�V�����̃u�����h��
//
//	bool m_isMove;					// ���̃t���[���œ��������ǂ���
//	bool m_isLackStamina;			// �X�^�~�i���s�����Ă��邩�ǂ���
//	bool m_isDash;					// �_�b�V�������ǂ���
};

