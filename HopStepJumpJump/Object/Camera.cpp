#include "Camera.h"

#include "Circle.h"
#include "Model.h"
#include "ObjectBase.h"

#include "Player/Player.h"


#include "../Util/Input.h"
#include "../Util/Time.h"
#include "../Util/Easing.h"

namespace
{
	/*�ʏ펞*/
	constexpr float kNear = 10.0f;	// �J������near
	constexpr float kFar = 7000.0f;	// �J������far
	constexpr int kMaxInputNum = 1000;	// �A�i���O���͏�ԍő�l

	constexpr float kCameraAngleSpeedX = 0.1f;	// �J�����̐���X�s�[�hX
	constexpr float kCameraAngleSpeedY = 0.05f;	// �J�����̐���X�s�[�hY
	
	constexpr float kCameraAngleVMax = DX_PI_F / 2.0f - 0.8f;	// �J�����̍ő�p�x
	constexpr float kCameraAngleVMin = -DX_PI_F / 2.0f + 0.6f;	// �J�����̍ŏ��p�x
	
	constexpr float kCameraPlayerTargetHeight = 65.0f;		// �J�����̒����_(�v���C���[���W����̍���)
	
	constexpr float kCameraToPlayerLenghtMax = 175.0f;		// �J��������v���C���[�܂ł̍ő勗��
	constexpr float kCameraToPlayerLenghtMin = 0.0f;		// �J��������v���C���[�܂ł̍ŏ�����
	
	constexpr float kCameraToPlayerLenghtSpeed = 5.0f;		// �J�����̋�����ς���X�s�[�h
	
	constexpr float kSize = 10.0f;							// �J�����̃T�C�Y(�����蔻��p)
	
	constexpr int kMaxColHitTryNum = 50;					// �J�����̉����o�����s��
	
	/*�J�����̂��Ă��鑬�x*/
	constexpr float kCameraFollowSpeed = 0.2f;
	constexpr float kPrevCameraFollowSpeed = 1.0f - kCameraFollowSpeed;
	
	/*�J�����̒����_��ǂ������鑬�x*/
	constexpr float kCameraTargetFollowSpeed = 0.2f;
	constexpr float kPrevCameraTargetFollowSpeed = 1.0f - kCameraTargetFollowSpeed;

	/*�X�e�[�W�N���A��*/
	constexpr float kStageClearStartAngleH = 0.0f;	// �X�e�[�W�N���A���̍ŏ��̃J�����̊p�xH
	constexpr float kStageClearStartAngleV = 0.15f;	// �X�e�[�W�N���A���̍ŏ��̃J�����̊p�xV
	constexpr float kStageClearEndAngleH = DX_TWO_PI_F + DX_PI_F + DX_PI_F * 2.0f;	// �X�e�[�W�N���A���̍Ō�̃J�����̊p�xH
	constexpr float kStageClearEndAngleV = -0.35;	// �X�e�[�W�N���A���̍Ō�̃J�����̊p�xV
	constexpr float kEasingTime = 80.0f;	// �C�[�W���O�ɂ����鎞��
	constexpr float kStageClearCameraTargtHeight = kCameraPlayerTargetHeight * 0.5f;	// �X�e�[�W�N���A���̒����_�̍���
	constexpr float kStageClearTargetMoveLength = 43.0f;	// �X�e�[�W�N���A���̃^�[�Q�b�g�̈ړ���
	constexpr float kStageClearTargetStartMoveTime = 200.0f;	// �X�e�[�W���N���A���Ă���^�[�Q�b�g�������o���܂ł̎���
	constexpr float kStageClearTargetLength = 80.0f;		// �X�e�[�W�N���A���̃J��������^�[�Q�b�g�܂ł̋���
	
	/*�X�e�[�W�N���A���̃C�[�W���O�ɂ����鎞��*/
	constexpr float kStageClearEasingTime =  650.0f;
	constexpr float kStageClearTargetMoveTime = 600.0f;
}

Camera::Camera() :
	m_angleH(0.0f),
	m_angleV(0.0f),
	m_cameraToTargetLenght(kCameraToPlayerLenghtMax),
	m_clearCameraToTargetLength(kStageClearTargetLength),
	m_stageClearEasingTime(0.0f),
	m_stageClearTargetEasingTime(0.0f),
	m_isStageClear(false),
	m_pos{0,0,0},
	m_nextPos{0,0,0},
	m_prevPos{0,0,0},
	m_targetPos{0,0,0},
	m_stageClearTargetStartPos{0,0,0},
	m_isMove(false),
	m_isHit(false),
	m_pPoly(nullptr)
{
	m_rotX = MGetRotX(m_angleV);
	m_rotY = MGetRotY(m_angleH);

	/*�|�C���^�̐���*/
	m_pCircle = std::make_shared<Circle>(m_nextPos, kSize, 0.0f);
	m_pClearTargetStartMoveTime = std::make_shared<Time>(kStageClearTargetStartMoveTime);
}

Camera::~Camera()
{
	/*��������*/
}

void Camera::Init()
{
	/*��������*/
}

void Camera::Update(VECTOR playerPos)
{
	// �X�e�[�W�N���A���͉������Ȃ�
	if (m_isStageClear) return;
	// �X�V�O�̍��W�̐ݒ�
	m_prevPos = m_nextPos;

	// �^�[�Q�b�g�̍��W�̐ݒ�
	VECTOR targetPos;
	targetPos = playerPos;
	targetPos.y += kCameraPlayerTargetHeight;

	// �p�x�X�V
	UpdateAngle();

	// ���W�X�V
	NormalUpdate(targetPos);
	
	// ���W�̊m��
	UpdatePos();
}

void Camera::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0x000000, "�J�������W�F%f,%f,%f", m_prevPos.x, m_prevPos.y, m_prevPos.z);
	DrawFormatString(0, 40, 0x000000, "�^�[�Q�b�g���W�F%f,%f,%f", m_targetPos.x, m_targetPos.y, m_targetPos.z);
	DrawFormatString(0, 120, 0x000000, "GetTargetPos:%f,%f,%f", GetCameraTarget().x, GetCameraTarget().y, GetCameraTarget().z);
#endif // _DEBUG

}

void Camera::ResetCamera()
{
	// �\���ꏊ�̐ݒ�
	SetCameraNearFar(kNear, kFar);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
}

void Camera::ColUpdate(ObjectBase* pField)
{
	// �J�����̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ���o����͈͈͂ړ��������l������
	m_hitDim = MV1CollCheck_Capsule(pField->GetModel()->GetModelHandle(), 
		-1, m_nextPos, m_prevPos,
		m_pCircle->GetRadius());

	if (m_hitDim.HitNum == 0)
	{
		// ���o�����v���C���[�̎��͂̃|���S�������J������
		MV1CollResultPolyDimTerminate(m_hitDim);

		m_cameraToTargetLenght = min(m_cameraToTargetLenght + kCameraToPlayerLenghtSpeed,
			kCameraToPlayerLenghtMax);

		// �J�����̍��W�����肷��
		UpdatePos();

		m_hitDim = MV1CollCheck_Capsule(pField->GetModel()->GetModelHandle(),
			-1, m_nextPos, m_prevPos,
			m_pCircle->GetRadius());
	}

	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		m_pPolyIndex[i] = &m_hitDim.Dim[i];
	}

	// �J�����̉����o������
	FixPosInternal();

	// ���o�����v���C���[�̎��͂̃|���S�������J������
	MV1CollResultPolyDimTerminate(m_hitDim);

	// �J�����̍��W�����肷��
	UpdatePos();

	// �J�����̏��𔽉f������
	m_pos = VAdd(VScale(m_prevPos, kPrevCameraFollowSpeed), VScale(m_nextPos, kCameraFollowSpeed));
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
}

void Camera::StageClearUpdate()
{
	// �X�e�[�W�̃N���A���Ԃ����ȏ�o�߂�����C�[�W���O����������
	if (m_pClearTargetStartMoveTime->Update())
	{
		// �C�[�W���O�𗘗p���Čv�Z����
		m_targetPos.x = Easing::EaseOutCubic(m_stageClearTargetEasingTime, m_stageClearTargetStartPos.x,
			m_stageClearTargetEndPos.x, kStageClearTargetMoveTime);
		m_targetPos.y = Easing::EaseOutCubic(m_stageClearTargetEasingTime, m_stageClearTargetStartPos.y,
			m_stageClearTargetEndPos.y, kStageClearTargetMoveTime);
		m_targetPos.z = Easing::EaseOutCubic(m_stageClearTargetEasingTime, m_stageClearTargetStartPos.z,
			m_stageClearTargetEndPos.z, kStageClearTargetMoveTime);
	}
	m_stageClearEasingTime = min(m_stageClearEasingTime + 1.0f, kStageClearEasingTime);

	// �X�e�[�W�N���A���̃J�����p�x�̍X�V
	m_angleH = Easing::EaseOutCubic(m_stageClearEasingTime, kStageClearStartAngleH,
		kStageClearEndAngleH, kStageClearEasingTime);
	m_angleV = Easing::EaseOutCubic(m_stageClearEasingTime, kStageClearStartAngleV,
		kStageClearEndAngleV, kStageClearEasingTime);

	// �X�e�[�W�N���A���̃J��������^�[�Q�b�g�܂ł̋����̍X�V
	m_cameraToTargetLenght = Easing::EaseOutCubic(m_stageClearEasingTime, kCameraToPlayerLenghtMax,
		m_clearCameraToTargetLength, kStageClearEasingTime);

	// �J�������W�̍X�V
	NormalUpdate(m_targetPos);
	UpdatePos();

	// �X�V����O�̍��W��O�t���[�����W�ɑ��
	m_pos = m_nextPos;
}

void Camera::StageClear(float angle, VECTOR targetPos)
{
	// �N���A�t���O��true�ɂ���
	m_isStageClear = true;

	/*�����_�̐ݒ�*/
	m_targetPos = targetPos;
	// �^�[�Q�b�g��菭�������ʒu�ɒ����_��u��
	m_targetPos.y += kStageClearCameraTargtHeight;

	// �p�x�̏�����
	m_angleH = kStageClearStartAngleH;
	m_angleV = kStageClearStartAngleV;

	NormalUpdate(m_targetPos);

	// �J�����̍��W�̍X�V
	UpdatePos();

	// �������x�N�g���̎Z�o
	m_leftVec = VNorm(VCross(VGet(0.0f, 1.0f, 0.0f),
		VNorm(VSub(VGet(m_targetPos.x, 0.0f, m_targetPos.z),
			VGet(m_nextPos.x, 0.0f, m_nextPos.z)))));

	// �X�e�[�W�N���A���̃J�����̍��W�̐ݒ�
	m_stageClearTargetStartPos = m_targetPos;
	// �J�����̍ŏI���W�̐ݒ�
	m_stageClearTargetEndPos = VAdd(m_targetPos, VScale(m_leftVec, kStageClearTargetLength));
	// �����Ă�������̌X���ɍŏI���W�����킹��
	MATRIX RotY = MGetRotY(kStageClearEndAngleH);
	m_stageClearTargetEndPos = VTransform(m_stageClearTargetEndPos, RotY);
	// ���]������
	m_stageClearTargetEndPos.x *= -1.0f;
	m_stageClearTargetEndPos.z *= -1.0f;
}

void Camera::UpdateAngle()
{
	// �p�b�h�̃A�i���O���̎擾
	DINPUT_JOYSTATE input;

	// ���͏��̏�����
	input.Rx = 0;
	input.Ry = 0;

	// ���͏��̎擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	// ��]��1�`1000����0.001�`1�͈̔͂ɂ���
	// ��ŃJ�������x���p�ӂ���(��U3�ɂ��Ă���)
	float rotX = 0.00020f * input.Rx * 3;
	float rotY = 0.00017f * input.Ry * 3;

	// �J�����̉�]�X�s�[�h��������
	rotX *= kCameraAngleSpeedX;
	rotY *= kCameraAngleSpeedY;

	m_angleH += rotX;
	if (input.Rx < 0.0f)
	{
		// -180���ȉ��ɂȂ�����p�x�n���傫���Ȃ肷���Ȃ��悤��360���𑫂�
		if (m_angleH < -DX_PI_F)
		{
			m_angleH += DX_TWO_PI_F;
		}
	}
	if (input.Rx > 0.0f)
	{
		// 180���ȏ�ɂȂ�����p�x�n���傫���Ȃ肷���Ȃ��悤��360��������
		if (m_angleH > DX_PI_F)
		{
			m_angleH -= DX_TWO_PI_F;
		}
	}

	m_angleV -= rotY;
	// ���p�x�ȉ��ɂɂ͂Ȃ�Ȃ��悤�ɂ���
	if (m_angleV < kCameraAngleVMin)
	{
		m_angleV = kCameraAngleVMin;
	}
	// ���p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (m_angleV > kCameraAngleVMax)
	{
		m_angleV = kCameraAngleVMax;
	}
}

void Camera::NormalUpdate(VECTOR targetPos)
{
	m_targetPos.x = (m_targetPos.x * kPrevCameraTargetFollowSpeed) + (targetPos.x * kCameraTargetFollowSpeed);
	m_targetPos.y = (m_targetPos.y * kPrevCameraTargetFollowSpeed) + (targetPos.y * kCameraTargetFollowSpeed);
	m_targetPos.z = (m_targetPos.z * kPrevCameraTargetFollowSpeed) + (targetPos.z * kCameraTargetFollowSpeed);
}

void Camera::UpdatePos()
{
	// ���������̉�](X��)
	MATRIX RotX = MGetRotX(m_angleV);
	// ���������̉�](Y��)
	MATRIX RotY = MGetRotY(m_angleH);

	// �J�����̍��W�̌v�Z
	// (X���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	// ����������]��������ɐ���������]����
	// ����ɒ����_�̍��W�𑫂�)
	m_nextPos = VAdd(VTransform(VTransform(VGet(0.0f, 0.0f, m_cameraToTargetLenght), RotX),RotY),m_targetPos);
}

void Camera::FixPos()
{
	// �ǂɓ����������ǂ����̃t���O��false�ɂ��Ă���
	m_isHit = false;

	// �ړ��������ǂ���
	if (m_isMove)
	{
		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_hitDim.HitNum; i++)
		{
			// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|�`�S���|�C���^�z�񂩂�擾
			m_pPoly = m_pPolyIndex[i];

			// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
			if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pCircle->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1],
				m_pPoly->Position[2]) == false) continue;

			// �����ɗ����瓖�����Ă���
			m_isHit = true;

			// �J�������������Ă���Ƃ�
			while (m_isHit)
			{
				m_cameraToTargetLenght = max(m_cameraToTargetLenght--, kCameraToPlayerLenghtMin);
				// �J�����̍��W�X�V
				UpdatePos();

				// �|���S���ƃv���C���[���������Ă��Ȃ������烋�[�v���甲����
				if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pCircle->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1],
					m_pPoly->Position[2]) == false)
				{
					m_isHit = false;
				}
			}

			// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
			bool isHitWallPolygom = false;
			for (int j = 0; j < m_hitDim.HitNum; j++)
			{
				// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_pPoly = m_pPolyIndex[j];

				// �������Ă����烋�[�v���甲����
				if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pCircle->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]) == false)
				{
					isHitWallPolygom = true;
					break;
				}
			}

			// ���ׂẴ|���S���Ɠ������Ă��Ȃ������烋�[�v���甲����
			if (!isHitWallPolygom)
			{
				m_isHit = false;
				break;
			}
		}
	}
	else // �ړ����Ă��Ȃ������ꍇ
	{
		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_hitDim.HitNum; i++)
		{
			// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_pPoly = m_pPolyIndex[i];

			// �|���S���ɓ������Ă�����r���������t���O�𗧂Ă������Ń��[�v���甲����
			if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pCircle->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]) == false)
			{
				m_isHit = true;
				break;
			}
		}
	}
}

void Camera::FixPosInternal()
{
	// �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
	for (int i = 0; i < kMaxColHitTryNum; i++)
	{
		// ������\���̂���ǃ|���S�������ׂČ���
		bool isHitWall = false;

		// �ǃ|���S���̐������J��Ԃ�
		for (int j = 0; j < m_hitDim.HitNum; j++)
		{
			// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_pPoly = m_pPolyIndex[j];

			m_cameraToTargetLenght = max(m_cameraToTargetLenght--, kCameraToPlayerLenghtMin);

			// �J�����̍��W�X�V
			UpdatePos();

			// �ړ����������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
			for (int k = 0; k < m_hitDim.HitNum; k++)
			{
				// ���������烋�[�v���甲����
				m_pPoly = m_pPolyIndex[k]; if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pCircle->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]) == false)
				{
					isHitWall = true;
					break;
				}
			}

			// ���ׂẴ|���S���Ɠ������Ă��Ȃ������烋�[�v���甲����
			if (!isHitWall) break;
		}
		// ���[�v�I��
		if (!isHitWall)break;
	}
}
