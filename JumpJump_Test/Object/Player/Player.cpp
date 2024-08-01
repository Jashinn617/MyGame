#include "DxLib.h"
#include "Player.h"
#include "PlayerState.h"
#include "Stamina.h"
#include "../Camera.h"
#include "../../Util/Input.h"

#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";	// �v���C���[���f���t�@�C����
	constexpr float kSize = 15.0f;	// �v���C���[�T�C�Y
	constexpr float kModelSize = 20.0f;	// �v���C���[���f���̃T�C�Y
	/*�X�s�[�h�֌W*/
	constexpr float kMoveSpeedDashRate = 2.2f;	// �����Ă���Ƃ��̃X�s�[�h
	constexpr float kAccelerationRate = 0.5f;	// �����x
	/*�W�����v�֌W*/
	constexpr float kJumpMaxSpeed = 8.0f;		// �W�����v���̍ő呬�x
	constexpr float kGravity = 0.8f;			// �d��
	constexpr float kFallMaxSpeed = -15.0f;		// �����ő呬�x
	/*�W�����v���̃A�j���[�V�����ύX�p�ϐ�*/
	constexpr float kJumpRise = 1.0f;
	constexpr float kJumpIdleNum = -5.0f;
	constexpr float kJumpDown = -15.0f;

	constexpr float kPlayerAngleSpeed = 0.2f;		// �v���C���[�̉�]���x
	constexpr int kInvinvibleTime = 60;				// ���G����
	constexpr float kKnockBackSpeed = 3.0f;			// �m�b�N�o�b�N�̃X�s�[�h
	constexpr float kKnockBackSpeedDecrease = 0.2f;	// �m�b�N�o�b�N�X�s�[�h������
	constexpr float kHeight = 35.0f;				// ����

	/*�ړ��̕⊮�l*/
	constexpr float kNowVecNum = 0.8f;
	constexpr float kNextVecNum = 0.2f;

	/*�A�j���[�V�������x*/
	enum kAnimSpeed
	{
		Idle = 2,
		Walk = 2,
		Dash = 1,
		KnockBack = 1
	};
}

Player::Player():
	m_walkSpeed(0),
	m_dashSpeed(0),
	m_acc(0),
	m_isStageClear(false),
	m_moveDirectVec{0,0,0},
	m_cameraToPlayer{0,0,0}	
{
	/*�|�C���^�̍쐬*/
	m_pStamina = std::make_shared<Stamina>();
	m_pState = std::make_shared<PlayerState>(m_pStamina);
	m_pInvincibleTime = std::make_shared<Time>(kInvinvibleTime);
	m_pCamera = std::make_shared<Camera>();

	/*��Ԃ̒ǉ�*/
	// �ҋ@
	m_pState->AddState([=] {IdleInit(); },
		[=] {IdleUpdate(); },
		PlayerState::StateKind::Idle);
	// ����
	m_pState->AddState([=] {WalkInit(); },
		[=] {WalkUpdate(); },
		PlayerState::StateKind::Walk);
	// �_�b�V��
	m_pState->AddState([=] {DashInit(); },
		[=] {DashUpdate(); },
		PlayerState::StateKind::Dash);
	// �W�����v
	m_pState->AddState([=] {JumpInit(); },
		[=] {JumpUpdate(); },
		PlayerState::StateKind::Jump);
	// �m�b�N�o�b�N
	m_pState->AddState([=] {KnockBackInit(); },
		[=] {KnockBackUpdate(); },
		PlayerState::StateKind::KnockBack);

	// ������Ԃ̐ݒ�
	// �����͑ҋ@��Ԃ���n�܂�
	m_pState->SetState(PlayerState::StateKind::Idle);
	
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	// �X�e�[�W�N���A��
	if (m_isStageClear)
	{
		// �J�������X�e�[�W�N���A�p�ɂ���

	}
}

void Player::Draw()
{
}