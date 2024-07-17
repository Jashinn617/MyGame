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
	constexpr float kMoveSpeed = 1.0f;				// �ړ����x
	constexpr float kDashSpeed = 2.0f;				// �_�b�V�����̈ړ����x
	constexpr float kLackStaminaSpeed = 0.1f;		// �X�^�~�i�s����Ԏ��̈ړ����x
	constexpr float kAngleSpeed = 0.2f;				// ��]���x
	constexpr float kJunpPower = 5.0f;				// �W�����v��
	constexpr float kFallUpPower = 2.0f;			// ���𓥂݊O�����Ƃ��̃W�����v��
	constexpr float kGravity = 0.3f;				// �d��
	constexpr float kPlayAnimSpeed = 0.5f;			// �A�j���[�V�����̑��x
	constexpr float kAnimBlendSpeed = 0.1f;			// �A�j���[�V�����̃u�����h���̕ω����x
	constexpr float kModelScale = 0.02f;				// ���f���̃X�P�[��
	constexpr float kFall = 3.0f;					// �������肪���鍂��
	constexpr float kMaxStamina = 100.0f;			// �X�^�~�i�̍ő�l
	constexpr float kDecreaseStaminaSpeed = 0.5f;	// �X�^�~�i�����鑬�x
	constexpr float kIncreaseStaminaSpeed = 0.5f;	// �X�^�~�i�������鑬�x
	constexpr float kDecreaseJumpStamina = 30.0f;	// �W�����v�Ō���X�^�~�i�̗�
	constexpr float kRadius = 2.5f;					// ���a
	

	// �A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	static constexpr float kAnimChangeFrame = 8.0f;
	// �A�j���[�V������؂�ւ��鑬�x
	static constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

}

Player::Player() :
	m_pos{ 0.0f,100.0f,0.0f },
	m_targetDir{ 1.0f,0.0f,0.0f },
	m_angle(0.0f),
	m_nowJunpPower(0.0f),
	m_stamina(kMaxStamina),
	m_modelHandle(-1),
	m_currentState(State::Idle),
	m_currentAnimNo(-1),
	m_prevAnimNo(-1),
	m_nowAnimCount(0.0f),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f),
	m_isMove(false),
	m_isLackStamina(false),
	m_isDash(false)
{
	/*��������*/
}

Player::~Player()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
	// �V�F�[�_�̃f���[�g
	InitShader();
}

void Player::Init()
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/Player/Character.mv1");
	assert(m_modelHandle != -1);
	// �V�F�[�_�̃��[�h
	m_psHs.push_back(LoadPixelShader("MV1PixelShader.pso"));
	assert(m_psHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader4Frame.vso"));
	assert(m_vsHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader8Frame.vso"));
	assert(m_vsHs.back() != -1);

	// ���f���̃X�P�[���̐ݒ�
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));

	// �����̃A�j���[�V�����̐ݒ�
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, static_cast<int>(AnimKind::Idle), -1, false);

	// ���f���̃g���C�A���O�����X�g���ɑΉ�����V�F�[�_��ݒ肷��
	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		switch (MV1GetTriangleListVertexType(m_modelHandle, i))
		{
		case DX_MV1_VERTEX_TYPE_4FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(0);
			break;
		case DX_MV1_VERTEX_TYPE_8FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(1);
			break;
		default:
			m_pixelShaderNumbers.push_back(-1);
			m_vertexShaderNumbers.push_back(-1);
			break;
		}
	}
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
	LoopAnim(m_currentAnimNo);

	// �ړ������Ƀ��f�����߂Â���
	UpdateAngle();

	// �ړ��x�N�g�������ɓ����蔻����l�����Ȃ���v���C���[���ړ�������
	Move(moveVec, stage);

	Stamina();
}

void Player::Draw()
{
	// �v���C���[�̈ʒu�ƃX�^�~�i�̃f�o�b�O�\��
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "PlayerPos x:%f,y:%f,z:%f	Stamina %f", m_pos.x, m_pos.y, m_pos.z, m_stamina);

	DrawSphere3D(VAdd(m_pos, VGet(0, kRadius, 0)), kRadius, 32, 0x00ffff, 0x00ffff, false);
#endif // _DEBUG	

	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		if (m_vertexShaderNumbers[i] && m_pixelShaderNumbers[i] == -1)
		{
			MV1SetUseOrigShader(false);
			SetUseVertexShader(-1);
			SetUsePixelShader(-1);
		}
		else
		{
			MV1SetUseOrigShader(true);
			SetUseVertexShader(m_vsHs[m_vertexShaderNumbers[i]]);
			SetUsePixelShader(m_psHs[m_pixelShaderNumbers[i]]);
		}
		MV1DrawTriangleList(m_modelHandle, i);
	}
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
			// �ړ����Ă���ꍇ�͕�����ԂɂȂ�
			m_currentState = State::Walk;
			ChangeAnim(static_cast<int>(AnimKind::Walk));
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�͗����~�܂��ԂɂȂ�
			m_currentState = State::Idle;
			ChangeAnim(static_cast<int>(AnimKind::Idle));
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
	m_isDash = input.IsPressing("B");

	// ���{�^�������͂��ꂽ��J�����̌��Ă���������猩�č��Ɉړ�����
	if (input.IsPressing("left"))
	{
		// �ړ��x�N�g���ɍ������͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, leftMoveVec);
		// �ړ��t���O��true�ɂ���
		isMove = true;
	}
	// �E�{�^�������͂��ꂽ��J�����̌��Ă���������猩�ĉE�Ɉړ�����
	else if (input.IsPressing("right"))
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


	if (isMove)// �ړ��{�^����������Ă����ꍇ
	{
		// �ړ��x�N�g���𐳋K���������̂��v���C���[�����������Ƃ��ĕۑ�����
		m_targetDir = VNorm(moveVec);

		if (m_currentState == State::Idle || m_currentState == State::Walk || m_currentState == State::Run)
		{
			moveVec = VScale(m_targetDir, m_isDash ? kDashSpeed : kMoveSpeed);
			nextState = m_isDash ? State::Run : State::Walk;
			if (m_isLackStamina)
			{
				moveVec = VScale(m_targetDir, kLackStaminaSpeed);
				nextState = State::Walk;
			}
		}
	}
	else
	{
		// ���̃t���[���ő����Ă��邩�����Ă����Ԃ������ꍇ
		if (m_currentState == State::Walk || m_currentState == State::Run)
		{
			// �����~�܂��Ԃɂ���
			nextState = State::Idle;
		}
	}


	// �W�����v���Ă��Ȃ���Ԃ�A�{�^����������Ă����ꍇ�̓W�����v������
	// �X�^�~�i�s����Ԃ������ꍇ�̓W�����v�͂ł��Ȃ�
	if (m_currentState != State::Jump && (input.IsTriggered("A")) && !m_isLackStamina)
	{
		// �X�^�~�i�����炷
		m_stamina -= kDecreaseJumpStamina;

		// Y�������̑��x���Z�b�g����
		m_nowJunpPower = kJunpPower;

		// ��Ԃ��W�����v�ɂ���
		nextState = State::Jump;
	}

	// �W�����v���Ă����Ԃ������ꍇ�͏d�͂�K�p����
	if (m_currentState == State::Jump)
	{
		m_nowJunpPower -= kGravity;

		if (isMove)
		{
			moveVec = VScale(m_targetDir, m_isDash ? kDashSpeed : kMoveSpeed);
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

void Player::Stamina()
{
	// �_�b�V�����̓X�^�~�i������
	if (m_currentState == State::Run && m_stamina > 0.0f)
	{
		m_stamina -= kDecreaseStaminaSpeed;
	}
	// �_�b�V�����o�Ȃ������ꍇ�̓X�^�~�i�͑�����
	else
	{
		m_stamina += kIncreaseStaminaSpeed;
	}

	// �X�^�~�i��0�ɂȂ����炵�΂炭�X�^�~�i�s����ԂɂȂ�
	if (m_stamina <= 0.0f)
	{
		m_isLackStamina = true;
	}

	// �X�^�~�i��max�l�ȏ�ɂȂ�Ȃ��悤�ɂ���
	if (m_stamina >= kMaxStamina)
	{
		m_stamina = kMaxStamina;

		// �X�^�~�i�s����Ԃ������ꍇ�͂����ŕs����Ԃ��畜�A����
		m_isLackStamina = false;
	}
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
	// �����~�܂��Ԃ��������Ԃɕς����
	if (prevState == State::Idle && m_currentState == State::Walk)
	{
		// ����A�j���[�V�����̍Đ�
		ChangeAnim(static_cast<int>(AnimKind::Walk));
	}
	// �����~�܂��Ԃ��瑖���ԂɂȂ���
	else if (prevState == State::Idle && m_currentState == State::Run)
	{
		ChangeAnim(static_cast<int>(AnimKind::Run));
	}
	// �����~�܂��Ԃ���W�����v��ԂɂȂ���
	else if (prevState == State::Idle && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// ������Ԃ��痧���~�܂��Ԃɕς����
	else if (prevState == State::Walk && m_currentState == State::Idle)
	{
		// �����~�܂�A�j���[�V�����̍Đ�
		ChangeAnim(static_cast<int>(AnimKind::Idle));
	}
	// ������Ԃ��瑖���ԂɂȂ���
	else if (prevState == State::Walk && m_currentState == State::Run)
	{
		ChangeAnim(static_cast<int>(AnimKind::Run));
	}
	// ������Ԃ���W�����v��ԂɂȂ���
	else if (prevState == State::Walk && m_currentState == State::Jump)
	{
		ChangeAnim(static_cast<int>(AnimKind::Jump));
	}
	// �����Ԃ��������ԂɂȂ���
	else if (prevState == State::Run && m_currentState == State::Walk)
	{
		ChangeAnim(static_cast<int>(AnimKind::Walk));
	}
	// �����Ԃ��痧���~�܂��ԂɂȂ���
	else if (prevState == State::Run && m_currentState == State::Idle)
	{
		ChangeAnim(static_cast<int>(AnimKind::Idle));
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
		if (m_nowJunpPower < kFall)
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
