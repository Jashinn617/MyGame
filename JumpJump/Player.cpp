#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Stage/StageTest.h"
#include "Util/Input.h"

#include <math.h>
#include <cassert>

/// <summary>
/// �萔��`
/// </summary>
namespace
{
	constexpr float kMoveSpeed = 1.0f;			// �ړ����x
	constexpr float kAngleSpeed = 0.2f;			// ��]���x
	constexpr float kJunpPower = 8.5f;			// �W�����v��
	constexpr float kFallUpPower = 0.6f;		// ���𓥂݊O�����Ƃ��̃W�����v��
	constexpr float kGravity = 0.5f;			// �d��
	constexpr float kPlayAnimSpeed = 0.5f;	// �A�j���[�V�����̑��x
	constexpr float kAnimBlendSpeed = 0.1f;		// �A�j���[�V�����̃u�����h���̕ω����x

}

Player::Player():
	m_pos{0.0f,0.0f,0.0f},
	m_targetDir{1.0f,0.0f,0.0f},
	m_angle(0.0f),
	m_nowJunpPower(0.0f),
	m_modelHandle(-1),
	m_state(State::Idle),
	m_nowPlayAnim(1),
	m_prevPlayAnim(1),
	m_nowAnimCount(0.0f),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f),
	m_isMove(false)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/Player/Knight.mv1");
	assert(m_modelHandle != -1);
}

Player::~Player()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	MV1SetScale(m_modelHandle, VGet(3, 3, 3));

}

void Player::Update(const Input& input, const Camera& camera, StageTest& stage)
{
	// ���[�g�t���[����Z�������̈ړ��p�����[�^�[�𖳌��ɂ���
	//DisableRootFrameZMove();

	/* �ړ��p�����[�^�[�̐ݒ� */
	// ���{�^�����������Ƃ��̈ړ������x�N�g��
	VECTOR upMoveVec;
	// ���{�^�����������Ƃ��̈ړ������x�N�g��
	VECTOR leftMoveVec;
	// ���̃t���[���ł̈ړ��x�N�g��
	VECTOR moveVec;
	// ���݂̏��
	State prevState = m_state;
	m_state = UpdateMoveParamerer(input, camera, upMoveVec, leftMoveVec, moveVec);

	// �A�j���[�V�����X�e�[�g�̍X�V
	UpdateAnimationState(prevState);

	// �ړ������Ƀ��f�����߂Â���
	UpdateAngle();


	// �ړ��x�N�g�������ɓ����蔻����l�����Ȃ���v���C���[���ړ�������
	Move(moveVec,stage);

	//�A�j���[�V��������
	UpdateAnimation();

}

void Player::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "Playerx:%f,y:%f,z:%f",m_pos.x, m_pos.y, m_pos.z);

	MV1DrawModel(m_modelHandle);
}

void Player::End()
{

}

void Player::OnHitRoof()
{
	// Y�������̑��x�𔽓]������
	m_nowJunpPower = -m_nowJunpPower;

}

void Player::OnHitFloor()
{
	// Y�������̈ړ����x��0�ɂ���
	m_nowJunpPower = 0.0f;

	// �����W�����v���������ꍇ�͒��n��Ԃɂ���
	if (m_state == State::Jump)
	{
		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
		if (m_isMove)
		{
			// �ړ����Ă���ꍇ�͑����ԂɂȂ�
			m_state = State::Run;
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�͗����~�܂��ԂɂȂ�
			m_state = State::Idle;
		}

		// ���n���̓A�j���[�V�����̃u�����h���s��Ȃ�
		
	}

}

void Player::OnFall()
{
	if (m_state != State::Jump)
	{
		// �W�����v���ɂ���
		m_state = State::Jump;

		// ������Ƃ����W�����v����
		m_nowJunpPower = kFallUpPower;

		// �A�j���[�V�����𗎉����̂��̂ɂ���

	}
}

void Player::DisableRootFrameZMove()
{
	MATRIX localMatrix;

	// ���[�U�[�s�����������
	MV1ResetFrameUserLocalMatrix(m_modelHandle, 2);

	// ���݂̃��[�g�t���[���̍s����擾����
	localMatrix = MV1GetFrameLocalMatrix(m_modelHandle, 2);

	// Z�������̕��s�ړ������𖳌��ɂ���
	localMatrix.m[3][2] = 0.0f;

	// ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
	MV1SetFrameUserLocalMatrix(m_modelHandle, 2, localMatrix);


}

Player::State Player::UpdateMoveParamerer(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	State nextState = m_state;

	// �v���C���[�̈ړ������̃x�N�g�����Z�o����
	// ���{�^�����������Ƃ��̃v���C���[�̈ړ��x�N�g���́A
	// �J�����̎�����������Y�����𔲂�������
	upMoveVec = VSub(camera.GetTarget(), camera.GetPos());
	upMoveVec.y = 0.0f;

	// ���{�^�����������Ƃ��̃v���C���[�̈ړ��x�N�g���́A
	// ����������Ƃ��̕����x�N�g����Y���̃v���X�����̃x�N�g���ɐ����ȕ���
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// ��̃x�N�g���𐳋K������
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// ���̃t���[���ł̈ړ��x�N�g��������������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �ړ��������̃t���O��������Ԃł�false�ɂ���
	bool isMove = false;

	// ���{�^�������͂��ꂽ��J�����̌��Ă���������猩�č��Ɉړ�����
	if (input.IsPressing("left"))
	{
		// �ړ��x�N�g���ɍ������͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, leftMoveVec);

		// �ړ��t���O��true�ɂ���
		isMove = true;
	}
	// �E�{�^�������͂��ꂽ��J�����̌��Ă���������猩�ĉE�Ɉړ�����
	else if(input.IsPressing("right"))
	{
		// �ړ��x�N�g���ɍ������͂��ꂽ���̈ړ��x�N�g���𔽓](�}�C�i�X)�����������Z����
		moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));

		// �ړ��t���O��true�ɂ���
		isMove = true;
	}

	// ��{�^�������͂��ꂽ��J�����̌��Ă�������Ɉړ�����
	if (input.IsPressing("up"))
	{
		// �ړ��x�N�g���ɏオ���͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, upMoveVec);

		// �ړ��t���O��true�ɂ���
		isMove = true;
	}
	// ���{�^�������͂��ꂽ��J�����̕����Ɉړ�����
	else if (input.IsPressing("down"))
	{
		// �ړ��x�N�g���ɏオ���͂��ꂽ���̈ړ��x�N�g���𔽓](�}�C�i�X)�����������Z����
		moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));

		// �ړ��t���O��true�ɂ���
		isMove = true;
	}

	// �W�����v���Ă��Ȃ���Ԃ�A�{�^����������Ă����ꍇ�̓W�����v������
	if (m_state != State::Jump && (input.IsTriggered("A")))
	{
		// Y�������̑��x���Z�b�g����
		m_nowJunpPower = kJunpPower;

		// ��Ԃ��W�����v�ɂ���
		nextState = State::Jump;
	}

	// �W�����v���Ă����Ԃ������ꍇ�͏d�͂�K�p����
	if (m_state == State::Jump)
	{
		m_nowJunpPower -= kGravity;
	}

	if (isMove)// �ړ��{�^����������Ă����ꍇ
	{
		if (m_state == State::Idle)	// ���̏�Ԃ������~�܂��Ă����Ԃ������ꍇ
		{
			// ���̏�Ԃ𑖂��Ԃɂ���
			nextState = State::Run;
		}

		// �ړ��x�N�g���𐳋K���������̂��v���C���[�����������Ƃ��ĕۑ�����
		m_targetDir = VNorm(moveVec);

		// �v���C���[�������Ă�������̃x�N�g���ɃX�s�[�h���|�������̂��ړ��x�N�g���ɂ���
		moveVec = VScale(m_targetDir, kMoveSpeed);
	}
	else
	{
		// ���̃t���[���ő����Ă����Ԃ������ꍇ
		if (m_state == State::Run)
		{
			// �����~�܂��Ԃɂ���
			nextState = State::Idle;
		}
	}

	// �ړ��x�N�g����y������y�������̑��x�ɂ���
	moveVec.y = m_nowJunpPower;

	return nextState;
}

void Player::Move(const VECTOR& moveVec, StageTest& stage)
{
	// �ړ�������0.01�����̏ꍇ�͏������ړ����ăo�O�邽�߁A
	// 0.01�ȏ�ړ����Ă����ꍇ�͈ړ��������̃t���O��true�ɂ��Ă���
	// fabs�Ffloat�̐�Βl(abs����int�^�ɂȂ�)
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	m_pos = stage.CheckCollision(*this, moveVec);

	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(m_modelHandle, m_pos);
}

void Player::UpdateAngle()
{
	// �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
	float targetAngle;		// �ڕW�p�x
	float difference;		// �ڕW�p�x�ƌ��݂̊p�x�̍�

	// �ڕW�̕����x�N�g������p�x�l���o��
	// ���W����^���W�F���g���g���Ċp�x�����߂Ă���
	targetAngle = static_cast<float>(atan2(m_targetDir.x, m_targetDir.z));

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	// �ŏ��͈����Z�ŏo��
	difference = targetAngle - m_angle;

	// ����������炠���������180���ȏ�ɂȂ邱�Ƃ͖���
	// ���̂��߁A���̒l��180���ȏ�ɂȂ��Ă�����C�����Ă���
	if (difference < -DX_PI_F)// -180�ȉ���������360�𑫂�
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)// 180�ȏゾ������360������
	{
		difference -= DX_TWO_PI_F;
	}

	// �p�x�̍���0�ɋ߂Â���
	if (difference > 0.0f)// �����v���X�̏ꍇ�͈���
	{
		difference -= kAngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else// �����}�C�i�X�̏ꍇ�͑���
	{
		difference += kAngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// ���f���̊p�x���X�V����
	m_angle = targetAngle - difference;
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));

}

void Player::UpdateAnimationState(State prevState)
{
	// �����~�܂��Ԃ��瑖���Ԃɕς����
	if (prevState == State::Idle && m_state == State::Run)
	{
		// ����A�j���[�V�����̍Đ�
		PlayAnimation(AnimKind::Run);
	}
	// �����Ԃ��痧���~�܂��Ԃɕς����
	else if (prevState == State::Run && m_state == State::Idle)
	{
		// �����~�܂�A�j���[�V�����̍Đ�
		PlayAnimation(AnimKind::Stop);
	}
	// �W�����v��Ԃ������ꍇ
	else if (m_state == State::Jump)
	{
		// �������Ă��ăA�j���[�V�������㏸���p�̕��������ꍇ
		if (m_nowJunpPower < 0.0f)
		{
			bool isJumpAnim = MV1GetAttachAnim(m_modelHandle, m_nowPlayAnim) == static_cast<int>(AnimKind::Jump);
			// �������p�A�j���[�V�������Đ�����
			if (isJumpAnim)
			{
				PlayAnimation(AnimKind::Fall);
			}
		}
		else
		{
			PlayAnimation(AnimKind::Jump);
		}
	}
}

void Player::PlayAnimation(AnimKind nextPlayAnim)
{
	// ���O�ɍĐ����Ă����A�j���[�V�����Ƃ̓���ւ�������̂ŁA
	// 1�O�̃��[�V�������L���������ꍇ�̓f�^�b�`����
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
	m_prevPlayAnim = m_nowPlayAnim;
	m_prevAnimCount = m_nowAnimCount;

	// �V�����w�肵�����[�V���������f���ɃA�^�b�`���ăA�^�b�`�ԍ���ۑ�����
	m_nowPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(nextPlayAnim));

	// Prev���L���ł͂Ȃ��ꍇ��m_animBlendRate(�u�����h��)��1.0f�ɂ���
	m_animBlendRate = m_prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void Player::UpdateAnimation()
{
	// �Đ����Ă���A�j���[�V�����̑�����
	float animTotalTime;

	// �u�����h����1�ȉ��̏ꍇ��1�ɋ߂Â���
	if (m_animBlendRate < 1.0f)
	{
		m_animBlendRate += kAnimBlendSpeed;
		if (m_animBlendRate > 1.0f)
		{
			m_animBlendRate = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V����1�̏���
	if (m_nowPlayAnim != -1)	// ���݂̃A�j���[�V�����ԍ���-1(����)�łȂ��ꍇ
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_nowPlayAnim);

		// �Đ����Ԃ�i�߂�
		m_nowAnimCount += kPlayAnimSpeed;

		// ���[�v����
		if (m_nowAnimCount >= animTotalTime)
		{
			// ��](%)
			m_nowAnimCount = static_cast<float>(fmod(m_nowAnimCount, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(m_modelHandle, m_nowPlayAnim, m_nowAnimCount);

		// �A�j���[�V����1�̃��f���ɑ΂��锽�f�����Z�b�g����
		MV1SetAttachAnimBlendRate(m_modelHandle, m_nowPlayAnim, m_animBlendRate);
	}

	// �Đ����Ă���A�j���[�V����2�̏���
	if (m_prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_prevPlayAnim);

		// �Đ����Ԃ�i�߂�
		m_prevAnimCount += kPlayAnimSpeed;

		// ���[�v����
		if (m_prevAnimCount > animTotalTime)
		{
			m_prevAnimCount = static_cast<float>(fmod(m_prevAnimCount, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(m_modelHandle, m_prevPlayAnim, m_prevAnimCount);

		// �A�j���[�V����2�̃��f���̑΂��锽�f�����Z�b�g����
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevPlayAnim, 1.0f - m_animBlendRate);
	}


}
