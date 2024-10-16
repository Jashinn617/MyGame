#include "Camera.h"

#include "ObjectBase.h"
#include "Model.h"

#include "../Utility/Sphere.h"

namespace
{
	constexpr int kMaxInputNum = 1000;													// �A�i���O���͏�ԍő�l
	constexpr int kMaxColHitTryNum = 50;												// �J�����̉����o�����s��
	constexpr float kNear = 10.0f;														// �J�����̈�ԋ߂��`�拗��
	constexpr float kFar = 7000.0f;														// �J�����̈�ԉ����`�拗��
	constexpr float kCameraAngleSpeedX = 0.1f;											// �J�����̐��񑬓xX
	constexpr float kCameraAngleSpeedY = 0.05f;											// �J�����̐��񑬓xY
	constexpr float kCameraAngleVMax = DX_PI_F / 2.0f - 0.8f;							// �J�����̍ő吂���p�x
	constexpr float kCameraAngleVMin = -DX_PI_F / 2.0f + 0.6f;							// �J�����̍ŏ������p�x
	constexpr float kCameraViewpointHeight = 65.0f;										// �^�[�Q�b�g���璍���_�܂ł̍���
	constexpr float kCameraToTargetLenghtMax = 175.0f;									// �J��������^�[�Q�b�g�܂ł̍ő勗��
	constexpr float kCameraToTargetLenghtMin = 0.0f;									// �J��������^�[�Q�b�g�܂ł̍ŏ�����
	constexpr float kCameraToTargetLenghtSpeed = 5.0f;									// �J��������^�[�Q�b�g�܂ł̋�����ς��鑬�x
	constexpr float kSize = 10.0f;														// �����蔻��p�̃J�����̃T�C�Y
	constexpr float kCameraFollowSpeed = 0.2f;											// �J�������t���Ă��鑬�x
	constexpr float kPrevCameraFollowSpeed = 1.0f - kCameraFollowSpeed;					// �J�����̏����x
	constexpr float kCameraTargetFollowSpeed = 0.2f;									// �J�����������_��ǂ������鑬�x
	constexpr float kPrevCameraTargetFollowSpeed = 1.0f - kCameraTargetFollowSpeed;		// �J�����������_��ǂ������鏉���x
}

Camera::Camera():
	m_angleH(0.0f),
	m_angleV(0.0f),
	m_cameraToTargetLenght(0.0f),
	m_pos{0.0f,0.0f,0.0f},
	m_nextPos{0.0f,0.0f,0.0f},
	m_prevPos{0.0f,0.0f,0.0f},
	m_targetPos{0.0f,0.0f,0.0f},
	m_rotX(MGetRotX(m_angleV)),
	m_rotY(MGetRotY(m_angleH)),
	m_pSphere(std::make_shared<Sphere>(m_nextPos,kSize,0.0f)),
	m_isMove(false),
	m_isPolyHit(false),
	m_pPoly(nullptr)
{
	/*��������*/
}

Camera::~Camera()
{
	/*��������*/
}

void Camera::Init()
{
	/*��������*/
}

void Camera::Update(VECTOR targetPos)
{
	// �ړ��O�̍��W��ۑ�����
	m_prevPos = m_nextPos;

	// �����_���W��ݒ肷��
	VECTOR viewpointPos;
	viewpointPos = targetPos;
	// �^�[�Q�b�g���W�ɒ����_�̍����𑫂�
	viewpointPos.y += kCameraViewpointHeight;

	// �p�x�X�V
	UpdateAngle();
	// �ʏ펞�X�V
	NormalUpdate(viewpointPos);
	// ���W�̊m��
	UpdatePos();
}

void Camera::Draw()
{
#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0x000000, "�J�������W�F%f,%f,%f", m_prevPos.x, m_prevPos.y, m_prevPos.z);
	DrawFormatString(0, 40, 0x000000, "�^�[�Q�b�g���W�F%f,%f,%f", m_targetPos.x, m_targetPos.y, m_targetPos.z);
	DrawFormatString(0, 120, 0x000000, "GetTargetPos:%f,%f,%f", GetCameraTarget().x, GetCameraTarget().y, GetCameraTarget().z);
#endif // _DEBUG
}

void Camera::ResetCamera()
{
	// �J�����̕\���ݒ�
	SetCameraNearFar(kNear, kFar);
	// ���W�ݒ�
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
}

void Camera::ColUpdate(ObjectBase* pField)
{
	// �J�����̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ���o����͈͈͂ړ��������l������
	m_hitDim = MV1CollCheck_Capsule(pField->GetModel()->GetModelHandle(),
		-1, m_nextPos, m_prevPos,
		m_pSphere->GetRadius());

	if (m_hitDim.HitNum == 0)
	{
		// ���o�����v���C���[�̎��͂̃|���S�������J������
		MV1CollResultPolyDimTerminate(m_hitDim);

		m_cameraToTargetLenght = min(m_cameraToTargetLenght + kCameraToTargetLenghtSpeed,
			kCameraToTargetLenghtMax);

		// �J�����̍��W�����肷��
		UpdatePos();

		m_hitDim = MV1CollCheck_Capsule(pField->GetModel()->GetModelHandle(),
			-1, m_nextPos, m_prevPos,
			m_pSphere->GetRadius());
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
	// �^�[�Q�b�g���W�X�V
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

	/*�J�����̍��W�̌v�Z
	(X���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	����������]��������ɐ���������]����
	����ɒ����_�̍��W�𑫂�)*/
	m_nextPos = VAdd(VTransform(VTransform(VGet(0.0f, 0.0f, m_cameraToTargetLenght), RotX), RotY), m_targetPos);
}

void Camera::FixPos()
{
	// �ǂɓ����������ǂ����̃t���O��false�ɂ��Ă���
	m_isPolyHit = false;

	// �ړ��������ǂ���
	if (m_isMove)
	{
		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_hitDim.HitNum; i++)
		{
			// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|�`�S���|�C���^�z�񂩂�擾
			m_pPoly = m_pPolyIndex[i];

			// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
			if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pSphere->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1],
				m_pPoly->Position[2]) == false) continue;

			// �����ɗ����瓖�����Ă���
			m_isPolyHit = true;

			// �J�������������Ă���Ƃ�
			while (m_isPolyHit)
			{
				m_cameraToTargetLenght = max(m_cameraToTargetLenght--, kCameraToTargetLenghtMin);
				// �J�����̍��W�X�V
				UpdatePos();

				// �|���S���ƃv���C���[���������Ă��Ȃ������烋�[�v���甲����
				if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pSphere->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1],
					m_pPoly->Position[2]) == false)
				{
					m_isPolyHit = false;
				}
			}

			// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
			bool isHitWallPolygom = false;
			for (int j = 0; j < m_hitDim.HitNum; j++)
			{
				// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_pPoly = m_pPolyIndex[j];

				// �������Ă����烋�[�v���甲����
				if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pSphere->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]) == false)
				{
					isHitWallPolygom = true;
					break;
				}
			}

			// ���ׂẴ|���S���Ɠ������Ă��Ȃ������烋�[�v���甲����
			if (!isHitWallPolygom)
			{
				m_isPolyHit = false;
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
			if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pSphere->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]) == false)
			{
				m_isPolyHit = true;
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

			m_cameraToTargetLenght = max(m_cameraToTargetLenght--, kCameraToTargetLenghtMin);

			// �J�����̍��W�X�V
			UpdatePos();

			// �ړ����������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
			for (int k = 0; k < m_hitDim.HitNum; k++)
			{
				// ���������烋�[�v���甲����
				m_pPoly = m_pPolyIndex[k]; if (HitCheck_Capsule_Triangle(m_nextPos, m_prevPos, m_pSphere->GetRadius(),
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
