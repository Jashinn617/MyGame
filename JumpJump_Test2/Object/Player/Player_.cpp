#include "Player_.h"

#include "../ObjectBase.h"
#include "../ObjectManager.h"
#include "../Model.h"
#include "../Camera.h"
#include "../Circle.h"

#include "../../Util/Input.h"
#include "../../Util/Pad.h"
#include "../../Util/Time.h"
#include "../../Util/MoveDirectionVec.h"
#include "../../Util/CsvLoad.h"

#include "../../Shader/ToonShader.h"

#include <math.h>
#include <cassert>

namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Character.mv1";
	constexpr float kSize = 15.0f;
	constexpr float kModelScale = 0.11f;
	constexpr float kFallBackPosY = -800.0f;
	/*�X�s�[�h�֌W*/
	constexpr float kMoveSpeedDashRate = 1.2f;
	constexpr float kAccelerationRate = 0.5f;
	/*�W�����v�֌W*/
	constexpr float kJumpMaxSpeed = 8.0f;
	constexpr float kGravity = 0.8f;
	constexpr float kFallMaxSpeed = -15.0f;
	constexpr float kAttackHitJumpSpeed = 3.0f;

	constexpr float kPlayerAngleSpeed = 0.02f;			// �v���C���[�̉�]���x
	constexpr int kInvinvibleTime = 60;					// ���G����
	constexpr float kKnockBackSpeed = 10.0f;			// �m�b�N�o�b�N�̃X�s�[�h
	constexpr float kKnockBackSpeedDecrease = 0.2f;		// �m�b�N�o�b�N�X�s�[�h������
	constexpr float kHeight = 35.0f;					// ����

	/*�ړ��̕⊮�l*/
	constexpr float kNowVecNum = 0.8f;
	constexpr float kNextVecNum = 0.2f;

	constexpr float kDrawDistance = 50.0f;				// �`��\����

	constexpr float kEnemyHeadPos = 20;					// �G�̓��̈ʒu

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

Player_::Player_():
	m_walkSpeed(0),
	m_dashSpeed(0),
	m_acc(0),
	m_isMove(false),
	m_isDash(false),
	m_moveDirectVec{0,0,0},
	m_cameraToPlayerVec{0,0,0},
	m_currentState(State::Idle)
{
	// �A�j���[�V�����̏�����
	CsvLoad::GetInstance().AnimLoad(m_animData, "Player");

	/*�ړ��X�s�[�h�̏�����*/
	m_walkSpeed = m_statusData.spd;
	m_dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_acc = m_statusData.spd * kAccelerationRate;

	/*��񏉊���*/
	m_info.pos = VGet(0.0f, 0.0f, 0.0f);
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;

	/*���f���֌W������*/
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pModel->SetAnim(m_animData.idle, false, true);
	m_pModel->SetScale(VGet(kModelScale, kModelScale, kModelScale));

	/*�|�C���^�쐬*/
	m_pInvincibleTime = std::make_shared<Time>(kInvinvibleTime);
	m_pCamera = std::make_shared<Camera>();
	m_pCircle = std::make_shared<Circle>(m_info.pos, kSize, kHeight * 0.5f);
}

Player_::~Player_()
{
	/*��������*/
}

void Player_::Init()
{
	/*��������*/
}

void Player_::Update(Input& input)
{
	/*�ړ��p�����[�^�̐ݒ�*/
	VECTOR upMoveVec;
	VECTOR leftMoveVec;
	VECTOR moveVec;

	/*���݂̏�ԍX�V*/
	// �O�t���[���̏�Ԃ������
	State prevState = m_currentState;
	// ���݂̏�Ԃ������
	m_currentState = UpdateMoveParamerer(upMoveVec, leftMoveVec, moveVec);

	// �A�j���[�V�����̍X�V
	m_pModel->Update();

	// �J�����̍X�V
	m_pCamera->Update(m_info.pos);
	// �v���C���[����J�����܂ł̏����̍X�V
	m_cameraToPlayerVec = VSub(m_info.pos, m_pCamera->GetPos());

	// �������珉���ʒu�ɖ߂�
	if (m_info.pos.y <= kFallBackPosY)
	{
		m_info.pos = VGet(0.0f, 0.0f, 0.0f);
		EndJump();
	}

}

void Player_::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	//���f���̃t���[�����Ƃɕ`�������
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		pToonShader->SetShader(shaderType);

		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	pToonShader->ShaderEnd();

	// �f�o�b�O�p�����蔻��̋�
	m_pCircle->DebugDraw();
}

void Player_::Draw2D()
{
	m_pCamera->Draw();

#ifdef _DEBUG
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W�F%f,%f,%f"
		, m_info.pos.x, m_info.pos.y, m_info.pos.z);
	DrawFormatString(0, 100, 0x000000, "�W�����v�́F%f", m_jumpPower);
#endif // _DEBUG
}

void Player_::StageClear()
{
}

void Player_::OnDamage(VECTOR targetPos)
{
	// �Q�[���N���A��Ԃ������牽�������ɏI������
	if (m_pObjectManager->IsGameClear())return;
	// �G��Y�ʒu�������̈ʒu���Ⴉ�����ꍇ�͉������Ȃ�
	if (targetPos.y <= m_info.pos.y - kEnemyHeadPos)return;
	// ���݂̏�Ԃ��m�b�N�o�b�N�̎��͉������Ȃ�
	if (m_currentState == State::KnockBack) return;

	// ���݂̏�Ԃ��m�b�N�o�b�N��Ԃɂ���
	m_currentState = State::KnockBack;

	// �m�b�N�o�b�N�̃X�s�[�h�ƕ������v�Z����
	m_moveSpeed = kKnockBackSpeed;
	m_isDamage = true;	

	m_moveDirectVec = VNorm(VSub(
		VGet(m_info.pos.x, 0.0f, m_info.pos.z),
		VGet(targetPos.x, 0.0f, targetPos.z)));

	// �V�F�[�_��ON�ɂ���

	// �_���[�W����炷
}

void Player_::OnAttack()
{
	// �U������炷


	m_jumpPower = kAttackHitJumpSpeed;
	m_currentState = State::Jump;
}

void Player_::EndJump()
{
	m_isJump = false;
	m_jumpPower = 0.0f;
	// ���n����炷

	// �����W�����v���������ꍇ�͒��n��Ԃɂ���
	if (m_currentState == State::Jump)
	{
		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
		if (m_isMove)	// �ړ����Ă����ꍇ
		{
			// ������ԂɂȂ�
			m_currentState = State::Walk;
			m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
		}
		else // �ړ����Ă��Ȃ������ꍇ
		{
			// �ҋ@��ԂɂȂ�
			m_currentState = State::Idle;
			m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		}
	}

}

void Player_::AngleUpdate()
{
}

Player_::State Player_::UpdateMoveParamerer(VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	// ���̏��
	State nextState = m_currentState;

	// �v���C���[�̈ړ������̃x�N�g�����Z�o����
	// ���{�^�����������Ƃ��̃v���C���[�̈ړ��x�N�g���́A
	// �J�����̎�����������Y�����𔲂�������
	upMoveVec = VSub(m_pCamera->GetTarget(), m_pCamera->GetPos());
	upMoveVec.y = 0.0f;
	// ���{�^�����������Ƃ��̃v���C���[�̈ړ��x�N�g���́A
	// ����������Ƃ��̕����x�N�g����Y���̃v���X�����̃x�N�g���ɐ����ȕ���
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));
	// ��̃x�N�g���𐳋K������
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);
	// ���̃t���[���ł̈ړ��x�N�g��������������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �ړ��������ǂ����̃t���O�����
	bool isMove = false;
	// �_�b�V�������ǂ���
	m_isDash = Pad::isPress(PAD_INPUT_1);

	// �ړ��{�^�����������牟����Ă����ꍇ
	if (Pad::isPress(PAD_INPUT_LEFT) || Pad::isPress(PAD_INPUT_RIGHT) ||
		Pad::isPress(PAD_INPUT_UP) || Pad::isPress(PAD_INPUT_DOWN))
	{
		isMove = true;
	}

	// �ړ��{�^����������Ă����ꍇ
	if (isMove)
	{
		if (m_currentState == State::Idle ||
			m_currentState == State::Walk ||
			m_currentState == State::Dash)
		{
			// �_�b�V���{�^����������Ă�����_�b�V����Ԃɂ���
			nextState = m_isDash ? State::Dash : State::Walk;
		}
	}
	else
	{
		// ���̃t���[���œ����Ă����Ԃ������ꍇ
		if (m_currentState == State::Walk || m_currentState == State::Dash)
		{
			// �ҋ@��Ԃɂ���
			nextState = State::Idle;
		}
	}

	// �W�����v��ԂłȂ���ԂŃW�����v�{�^����������Ă�����W�����v��ԂɂȂ�
	if (m_currentState != State::Jump && Pad::isTrigger(PAD_INPUT_2))
	{
		// �W�����v��Ԃɂ���
		nextState = State::Jump;
		m_isJump = true;
		m_jumpPower = kJumpMaxSpeed;
		// �W�����v����炷

	}

	return nextState;
}

VECTOR Player_::MoveUpdate(Input& input)
{
	// �ړ�������0.01�����̏ꍇ�͏������ړ����ăo�O�邽�߁A
	// 0.01�ȏ�ړ����Ă����ꍇ�͈ړ��������̃t���O��true�ɂ��Ă���
	// fabs�Ffloat�̐�Βl(abs����int�^�ɂȂ�)
	if (fabs(m_moveSpeed) > 0.01f || fabs(m_moveSpeed) > 0.01f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}
	if (!m_isMove) return VGet(0.0f,0.0f,0.0f);

	// �ړ������̍X�V
	MoveDirectionUpdate(input);
	// �p�x�̍X�V
	AngleUpdate();

	// �ړ��x�N�g���̐���
	VECTOR move = VNorm(m_moveDirectVec);

	// �m�b�N�o�b�N���̏���
	if (m_currentState == State::KnockBack)
	{
		move.x *= m_moveSpeed;
		move.z *= m_moveSpeed;

		return move;
	}

	/*��Ԃ��Ƃ̃X�s�[�h�̌v�Z*/
	if (m_currentState == State::Idle)
	{
		m_moveSpeed = max(m_moveSpeed - m_acc, 0.0f);
	}
	else if (m_currentState == State::Walk)
	{
		m_moveSpeed = min(m_moveSpeed + m_acc, m_walkSpeed);
	}
	else if (m_currentState == State::Dash)
	{
		m_moveSpeed = m_dashSpeed;
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

void Player_::MoveDirectionUpdate(Input& input)
{
	// �m�b�N�o�b�N���͏����������ɏI������
	if (m_currentState == State::KnockBack) return;

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

void Player_::UpdateAnimState(State prevState)
{
	/*�ҋ@����*/
	// �ҋ@����������
	if (prevState == State::Idle && m_currentState == State::Walk)
	{
		// �����A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
	}
	// �ҋ@���瑖����
	else if (prevState == State::Idle && m_currentState == State::Dash)
	{
		// ����A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);
	}
	// �ҋ@����W�����v
	else if (prevState == State::Idle && m_currentState == State::Jump)
	{
		// �W�����v�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// �ҋ@����m�b�N�o�b�N
	else if (prevState == State::Idle && m_currentState == State::KnockBack)
	{
		// �m�b�N�o�b�N�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	}

	/*��������*/
	// ��������ҋ@
	else if (prevState == State::Walk && m_currentState == State::Idle)
	{
		// �ҋ@�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
	}
	// �������瑖��
	else if (prevState == State::Walk && m_currentState == State::Dash)
	{
		// ����A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.run, true, false, kAnimSpeed::Dash);
	}
	// ��������W�����v
	else if (prevState == State::Walk && m_currentState == State::Jump)
	{
		// �W�����v�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// ��������m�b�N�o�b�N
	else if (prevState == State::Walk && m_currentState == State::KnockBack)
	{
		// �m�b�N�o�b�N�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	}

	/*���肩��*/
	// ���肩��ҋ@
	else if (prevState == State::Dash && m_currentState == State::Idle)
	{
		// �ҋ@�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
	}
	// ���肩�����
	else if (prevState == State::Dash && m_currentState == State::Walk)
	{
		// �����A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.walk, true, false, kAnimSpeed::Walk);
	}
	// ���肩��W�����v
	else if (prevState == State::Dash && m_currentState == State::Jump)
	{
		// �W�����v�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.jumpStart, false, false, kAnimSpeed::Jump);
	}
	// ���肩��m�b�N�o�b�N
	else if (prevState == State::Dash && m_currentState == State::KnockBack)
	{
		// �m�b�N�o�b�N�A�j���[�V�����̍Đ�
		m_pModel->ChangeAnim(m_animData.knockBack, false, false, kAnimSpeed::KnockBack);
	}

	// �m�b�N�o�b�N��Ԃ������ꍇ
	else if (m_currentState == State::KnockBack)
	{
		// �A�j���[�V�������I�������ҋ@��Ԃɖ߂�
		if (m_pModel->IsAnimEnd())
		{
			m_pModel->ChangeAnim(m_animData.idle, true, false, kAnimSpeed::Idle);
		}
	}

	// �W�����v��Ԃ������ꍇ
	else if (m_currentState == State::Jump)
	{
		if (m_pModel->IsAnimEnd())
		{
			m_pModel->ChangeAnim(m_animData.jumpIdle, true, false, kAnimSpeed::Jump);
		}
	}

}
