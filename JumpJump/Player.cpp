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
	constexpr float kPlayAnimSpeed = 0.5f;		// �A�j���[�V�����̑��x
	constexpr float kAnimBlendSpeed = 0.1f;		// �A�j���[�V�����̃u�����h���̕ω����x
	constexpr float kModelScale = 3;

	// �A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	static constexpr float kAnimChangeFrame = 8.0f;
	// �A�j���[�V������؂�ւ��鑬�x
	static constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

}

Player::Player():
	m_pos{0.0f,0.0f,0.0f},
	m_targetDir{1.0f,0.0f,0.0f},
	m_angle(0.0f),
	m_nowJunpPower(0.0f),
	m_modelHandle(-1),
	m_currentState(State::Idle),
	m_currentAnimNo(-1),
	m_prevAnimNo(-1),
	m_nowAnimCount(0.0f),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f),
	m_isMove(false)
{
	/*��������*/
}

Player::~Player()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/Player/Mage.mv1");
	assert(m_modelHandle != -1);

	// ���f���̃X�P�[���̐ݒ�
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));

	// �����̃A�j���[�V�����̐ݒ�
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, static_cast<int>(AnimKind::Stop), -1, false);

}

void Player::Update(const Input& input, const Camera& camera, StageTest& stage)
{
	// ���[�g�t���[����Z�������̈ړ��p�����[�^�[�𖳌��ɂ���
	DisableRootFrameZMove();

	/* �ړ��p�����[�^�[�̐ݒ� */
	// ���{�^�����������Ƃ��̈ړ������x�N�g��
	VECTOR upMoveVec;
	// ���{�^�����������Ƃ��̈ړ������x�N�g��
	VECTOR leftMoveVec;
	// ���̃t���[���ł̈ړ��x�N�g��
	VECTOR moveVec;
	// ���݂̏�Ԃ̍X�V
	State prevState = m_currentState;
	m_currentState = UpdateMoveParamerer(input, camera, upMoveVec, leftMoveVec, moveVec);

	// �A�j���[�V�����̐؂�ւ�
	if (m_prevAnimNo != -1)
	{
		// 8�t���[���ŃA�j���[�V������؂�ւ���
		m_animBlendRate += kAnimChangeRateSpeed;
		if (m_animBlendRate >= 1.0f) m_animBlendRate = 1.0f;

		// �ύX��̃A�j���[�V����������ݒ肷��
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);
	}

	// �A�j���[�V�����̍X�V
	UpdateAnimationState(prevState);
	// �A�j���[�V������i�߂�
	bool isLoop = LoopAnim(m_currentAnimNo);

	// �ړ������Ƀ��f�����߂Â���
	UpdateAngle();

	// �ړ��x�N�g�������ɓ����蔻����l�����Ȃ���v���C���[���ړ�������
	Move(moveVec,stage);
}

void Player::Draw()
{
	// �v���C���[�̈ʒu�̃f�o�b�O�\��
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Playerx:%f,y:%f,z:%f", m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG	

	// �v���C���[���f���̕`��
	MV1DrawModel(m_modelHandle);
}

void Player::End()
{
	/*��������*/
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
	if (m_currentState == State::Jump)
	{
		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
		if (m_isMove)
		{
			// �ړ����Ă���ꍇ�͑����ԂɂȂ�
			ChangeAnim(static_cast<int>(AnimKind::Run));
			m_currentState = State::Run;
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�͗����~�܂��ԂɂȂ�
			ChangeAnim(static_cast<int>(AnimKind::Stop));
			m_currentState = State::Idle;
		}
		// ���n���̓A�j���[�V�����̃u�����h���s��Ȃ�
		m_animBlendRate = 1.0f;
	}
}

void Player::OnFall()
{
	// ���݂̏�Ԃ��W�����v������Ȃ������Ƃ�
	if (m_currentState != State::Jump)
	{
		// �W�����v���ɂ���
		m_currentState = State::Jump;

		// ���������W�����v����
		m_nowJunpPower = kFallUpPower;

		// �A�j���[�V�����𗎉����̂��̂ɂ���
		ChangeAnim(static_cast<int>(AnimKind::Fall));
	}
}

void Player::DisableRootFrameZMove()
{
	// ���[�g�t���[���̍s�������ϐ�
	MATRIX localMatrix;

	// ���[�U�[�s�������(���Z�b�g)����
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
	// ���̏��
	State nextState = m_currentState;

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
	if (m_currentState != State::Jump && (input.IsTriggered("A")))
	{
		// Y�������̑��x���Z�b�g����
		m_nowJunpPower = kJunpPower;

		// ��Ԃ��W�����v�ɂ���
		nextState = State::Jump;
	}

	// �W�����v���Ă����Ԃ������ꍇ�͏d�͂�K�p����
	if (m_currentState == State::Jump)
	{
		m_nowJunpPower -= kGravity;
	}

	if (isMove)// �ړ��{�^����������Ă����ꍇ
	{
		if (m_currentState == State::Idle)	// ���̏�Ԃ������~�܂��Ă����Ԃ������ꍇ
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
		if (m_currentState == State::Run)
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

	// ���݈ʒu�ɃX�e�[�W�Ƃ̓����蔻����s�������ʂ𔽉f����
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
	if (prevState == State::Idle && m_currentState == State::Run)
	{
		// ����A�j���[�V�����̍Đ�
		ChangeAnim(static_cast<int>(AnimKind::Run));
	}
	// �����Ԃ��痧���~�܂��Ԃɕς����
	else if (prevState == State::Run && m_currentState == State::Idle)
	{
		// �����~�܂�A�j���[�V�����̍Đ�
		ChangeAnim(static_cast<int>(AnimKind::Stop));
	}
	// �����~�܂��Ԃ���W�����v��ԂɂȂ���
	else if (prevState == State::Idle && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// �����Ԃ���W�����v��ԂɂȂ���
	else if (prevState == State::Run && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// �W�����v��Ԃ������ꍇ
	else if (m_currentState == State::Jump)
	{
		// �������Ă���
		if (m_nowJunpPower < 0.0f)
		{
			// �A�j���[�V�������㏸���p�̕��ł���
			bool isJumpAnim = MV1GetAttachAnim(m_modelHandle, m_currentAnimNo) 
				== static_cast<int>(AnimKind::Jump);			
			if (isJumpAnim)
			{
				// �������p�A�j���[�V�������Đ�����
				ChangeAnim(static_cast<int>(AnimKind::Fall));
			}
		}
	}
}

bool Player::LoopAnim(int attachNo)
{
	// �A�j���[�V�������ݒ肳��Ă��Ȃ����߁A�I������
	if (attachNo == -1)return false;

	// �A�j���[�V���������[�v���Ă��邩�ǂ���
	bool isLoop = false;

	/*�A�j���[�V������i�s������*/
	// ���݂̍Đ��J�E���g
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);
	// �A�j���[�V������i�߂�
	now += kPlayAnimSpeed;

	// ���ݍĐ����̃A�j���[�V�����̑��J�E���g
	float total = MV1GetAttachAnimTotalTime(m_modelHandle, attachNo);


	// �A�j���[�V���������[�v������
	while (now >= total)
	{
		now -= total;

		isLoop = true;
	}

	// �A�j���[�V������i�߂����Ԃɐݒ肷��
	MV1SetAttachAnimTime(m_modelHandle, attachNo, now);

	return isLoop;
}

void Player::ChangeAnim(int animIndex)
{
	// �O�ɃA�j���[�V�������A�^�b�`����Ă����ꍇ�͂��̎��_�ō폜���Ă���
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevAnimNo);
	}

	// ���ݍĐ����̃A�j���[�V�����͕ύX�O�̃A�j���[�V�����ɂ���
	m_prevAnimNo = m_currentAnimNo;

	// �ύX��̃A�j���[�V������ݒ肷��
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, animIndex, -1, false);

	// �؂�ւ��̏u�Ԃ͕ύX�O�̃A�j���[�V�������Đ�������Ԃɂ���
	m_animBlendRate = 0.0f;

	// �ύX�O�̃A�j���[�V����100%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	// �ύX��̃A�j���[�V����0%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);
}
