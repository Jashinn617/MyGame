#include "DxLib.h"
#include "Player.h"
#include "PlayerState.h"
#include "Stamina.h"
#include "../Model.h"
#include "../Camera.h"
#include "../../Util/Input.h"
#include "../../Util/Time.h"
#include "../../Util/MoveDirectionVec.h"
#include "../ObjectManager.h"
#include "../ObjectBase.h"
#include "../../Shader/ToonShader.h"
#include "../../Shader/DamageShader.h"
#include "../Circle.h"


#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";	// �v���C���[���f���t�@�C����
	constexpr float kSize = 15.0f;	// �v���C���[�T�C�Y
	constexpr float kModelSize = 0.11f;	// �v���C���[���f���̃T�C�Y
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

	constexpr int kStageClearAnim = 65;				// �X�e�[�W�N���A�A�j���[�V����

	constexpr float kDrawDistance = 500.0f;			// �`��\����

	/*�A�j���[�V�������x*/
	enum kAnimSpeed
	{
		Idle = 2,
		Walk = 2,
		Dash = 1,
		Jump = 1,
		KnockBack = 1,
		StageClear = 1,
	};
}

Player::Player():
	m_walkSpeed(0),
	m_dashSpeed(0),
	m_acc(0),
	m_isStageClear(false),
	m_moveDirectVec{0,0,0},
	m_cameraToPlayerVec{0,0,0}	
{
	// �A�j���[�V�����̏�����

	/*�|�C���^�̍쐬*/
	m_pStamina = std::make_shared<Stamina>();
	m_pState = std::make_shared<PlayerState>(m_pStamina);
	m_pInvincibleTime = std::make_shared<Time>(kInvinvibleTime);
	m_pCamera = std::make_shared<Camera>();
	m_pCircle = std::make_shared<Circle>(m_info.pos, kSize, kHeight * 0.5f);
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pDamageShader = std::make_shared<DamageShader>();

	m_pModel->SetAnim(m_animData.idle, false, true);
	m_pModel->SetScale(VGet(kModelSize, kModelSize, kModelSize));

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
	/*��������*/
}

void Player::Init()
{
	/*��������*/
}

void Player::Update(Input& input)
{
	// �X�e�[�W�N���A��
	if (m_isStageClear)
	{
		// �J�������X�e�[�W�N���A�p�ɂ���
		m_pCamera->StageClearUpdate();

	}

	// ��ԍX�V
	m_pState->Update(input);

	// �X�^�~�i�̒l��ύX�����邩�ǂ���
	if (ChangeStaminaValue())
	{
		// �_�b�V�������W�����v�̎��ȊO�̓X�^�~�i���g��Ȃ�
		bool useStamina = (m_pState->GetState() == PlayerState::StateKind::Dash);

		// �X�^�~�i�X�V
		m_pStamina->Update(useStamina);
	}

	// �ړ��X�V
	m_info.vec = MoveUpdate(input);

	// �d�͂��l�������X�V
	GravityUpdate();

	// �U�����󂯂����̃V�F�[�_�̍X�V
	// ��ł���

	// �U�����󂯂���
	if (m_isDamage)
	{
		// ���G���Ԃ��v�����Ė��G���Ԃ��I�������_���[�W���󂯂��Ԃ���������
		if (m_pInvincibleTime->Update())
		{
			m_pInvincibleTime->Reset();
			m_isDamage = false;
		}
	}

	// �A�j���[�V�����̍X�V
	m_pModel->Update();

	// ���f���̍��W��ݒ肷��
	m_pModel->SetPos(m_info.pos);

	// ���f���̊p�x��ݒ肷��
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));

	// �J�����̍X�V
	CameraUpdate();

	// �v���C���[����J�����܂ł̋����̍X�V
	m_cameraToPlayerVec = VSub(m_info.pos, m_pCamera->GetPos());
}

void Player::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// ���f���̃t���[�����Ƃɕ`�������
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// �U�����󂯂����̓_���[�W�V�F�[�_��K������
		if (m_pDamageShader->GetUseShader())
		{
			int triangleType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

			m_pDamageShader->DrawFirst(triangleType);

			// �`��\�ȋ����𒴂��Ă��Ȃ����̂ݕ`�悷��
			if (VSize(m_cameraToPlayerVec) > kDrawDistance)
			{
				MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
			}

			// �V�F�[�_�����ɖ߂�
			m_pDamageShader->DrawEnd();
		}
		else	// �_���[�W��H����Ă��Ȃ��Ƃ��̓g�D�[���V�F�[�_���g��
		{
			for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
			{
				int triangleType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

				pToonShader->SetShader(triangleType);

				MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
			}
		}
	}
}

void Player::Draw2D()
{
	m_pStamina->Draw(m_info.pos);
#ifdef _DEBUG
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W�F%f,%f,%f",m_info.pos.x,m_info.pos.y,m_info.pos.z);
#endif // _DEBUG

}

void Player::StageClear()
{
	// ���W���S�[���̍��W�ɂ���
	m_info.pos = VGet(0.0f, 0.0f, 0.0f);

	// �p�x��ς���
	m_angle = 0.0f;
	m_isStageClear = true;
	m_pCamera->StageClear(m_angle, m_info.pos);
	m_pState->StageClear();
}

void Player::OnDamage(VECTOR targetPos)
{
	// �Q�[���N���A��Ԃ������牽�������ɏI������
	if (m_pObjectManager->IsGameClear())return;

	// �m�b�N�o�b�N�̃X�s�[�h�ƕ������v�Z����
	m_moveSpeed = kKnockBackSpeed;
	m_isDamage = true;
	
	m_pState->OnDamage();

	m_moveDirectVec = VNorm(VSub(
		VGet(m_info.pos.x, 0.0f, m_info.pos.z),
		VGet(targetPos.x, 0.0f, targetPos.z)));

	// �V�F�[�_��ON�ɂ���

	// �_���[�W����炷

}

void Player::EndJump()
{
	m_isJump = false;
	m_jumpPower = 0.0f;

	// �W�����v����炷

	// �X�e�[�W�N���A���͏������I������
	if (m_pState->GetState() == PlayerState::StateKind::StateClear) return;

	m_pState->EndState();
}

bool Player::ChangeStaminaValue()
{
	// �_�b�V�����̓X�^�~�i��ύX����
	if (m_pState->GetState() == PlayerState::StateKind::Dash) return false;

	// �ǂ̏����ɂ����Ă͂܂�Ȃ��ꍇ�̓X�^�~�i��ύX���Ȃ�
	return false;
}

void Player::CameraUpdate()
{
	m_pCamera->Update(m_info.pos);
	m_pCamera->Draw();
}

void Player::AngleUpdate()
{
	// �m�b�N�o�b�N���͏��������Ȃ�
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack) return;

	float nextAngle = atan2(m_moveDirectVec.z, m_moveDirectVec.x) +
		DX_PI_F * 0.5f + m_pCamera->GetCameraAngleX();

	SmoothAngle(m_angle, nextAngle);
	
}

void Player::MoveDirectionUpdate(Input& input)
{
	// �W�����v���A�m�b�N�o�b�N���͏����������ɏI������
	if (m_pState->GetState() == PlayerState::StateKind::Jump ||
		m_pState->GetState() == PlayerState::StateKind::KnockBack) return;

	// �ړ������x�N�g���N���X�𐶐�
	MoveDirectionVec moveVec;

	// �ړ������A�b�v�f�[�g
	moveVec.Update(input);
	
	// �i�݂��������ƍ��̕����̐��`�⊮
	m_moveDirectVec = VAdd(VScale(m_moveDirectVec, kNowVecNum),
		VScale(moveVec.GetDirectionVec(), kNextVecNum));

	// �i�݂���������Y�����Ȃ�
	m_moveDirectVec.y = 0.0f;
}

VECTOR Player::MoveUpdate(Input& input)
{
	// �ړ��X�s�[�h��0�̏ꍇ�͈ړ����Ȃ�
	if (m_moveSpeed == 0.0f)return VGet(0.0f, 0.0f, 0.0f);
	// �ړ������̍X�V
	MoveDirectionUpdate(input);
	// �p�x�̍X�V
	AngleUpdate();

	// �ړ��x�N�g������
	VECTOR move = VNorm(m_moveDirectVec);

	// �m�b�N�o�b�N���̏���
	if (m_pState->GetState() == PlayerState::StateKind::KnockBack)
	{
		move.x *= m_moveSpeed;
		move.z *= m_moveSpeed;

		return move;
	}

	// �ړ��x�N�g���ɃX�s�[�h��������
	// X���͔��]������
	move.x *= -m_moveSpeed;
	move.z *= m_moveSpeed;

	// �J�����̊p�x�ɂ���Đi�ޕ�����ς���
	MATRIX playerRotMtx = MGetRotY(m_pCamera->GetCameraAngleX());

	// �ړ��x�N�g���ƃJ�����p�x�s�����Z����
	move = VTransform(move, playerRotMtx);

	return move;
}

void Player::JumpInit()
{
	m_isJump = true;
	m_jumpPower = kJumpMaxSpeed;
	// �W�����v����炷

	m_pStamina->JumpUpdate();
}

void Player::IdleUpdate()
{
	m_moveSpeed = max(m_moveSpeed - m_acc, 0.0f);

	// �A�j���[�V������ҋ@��ԂɕύX����
	m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
}

void Player::WalkUpdate()
{
	// X�������̈ړ��x�N�g���ɕ����X�s�[�h��������
	m_moveSpeed = min(m_moveSpeed + m_acc, m_walkSpeed);

	// �A�j���[�V����������A�j���[�V�����ɕύX����
	m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);

	// ������炷

}

void Player::DashUpdate()
{
	m_moveSpeed = m_dashSpeed;

	// �A�j���[�V�������_�b�V�����[�V�����ɕύX����
	m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);

	// ������炷(�_�b�V����)

}

void Player::JumpUpdate()
{
	// �㏸��
	if (m_jumpPower > kJumpRise)
	{
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// �󒆂ɂƂǂ܂��Ă���A���~��
	else
	{
		m_pModel->ChangeAnim(m_animData.jumpIdle, false, false, kAnimSpeed::Jump);
	}
}

void Player::KnockBackUpdate()
{
	m_moveSpeed = max(m_moveSpeed - kKnockBackSpeedDecrease, 0.0f);
	m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	// �A�j���[�V�������I�������ҋ@��Ԃɖ߂�
	if (m_pModel->IsAnimEnd())
	{
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		m_pState->EndState();
	}
}

void Player::StageClearUpdate()
{
	m_moveSpeed = 0.0f;
	// ���f�����X�e�[�W�N���A��ԂɕύX����
	m_pModel->ChangeAnim(kStageClearAnim, true, false, kAnimSpeed::StageClear);
}