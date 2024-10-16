#include "CharacterBase.h"
#include "../Utility/Sphere.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;				// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;				// �ǂɉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;			// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kGravity = 0.8f;					// �d��
	constexpr float kFixGravity = 0.5f;					// �d�͂��}���ɑ��x��ς��Ȃ��悤�ɒ������鐔
	constexpr float kFallMaxSpeed = -15.0f;				// �ő嗎�����x
	constexpr float kChangeAngleSpeed = 0.25f;			// ���炩�Ɋp�x���ړ������鑬�x
	constexpr float kAngleDiffMax = DX_PI_F + 0.3f;		// �p�x�̍ő卷
	constexpr float kAngleDiffMin = -DX_PI_F - 0.3f;	// �p�x�̍ŏ���
	constexpr float kSlideLength = 10.0f;				// �����o���̑傫��	
}

CharacterBase::CharacterBase():
	m_jumpPower(0.0f),
	m_isJump(false),
	m_isDead(false),
	m_pSphere(nullptr)
{
	/*��������*/
}

CharacterBase::~CharacterBase()
{
	/*��������*/
}

void CharacterBase::EndJump()
{
	// �W�����v�����Ă��Ȃ���Ԃɖ߂�
	m_isJump = false;
	// �W�����v��0�ɂ���
	m_jumpPower = 0.0f;
}

void CharacterBase::MoveCollCharacter(CharacterBase* pTarget)
{
	// ���������肪���S��Ԃ̎��͔�������Ȃ�
	if (m_isDead || pTarget->IsDead())return;

	// �I�u�W�F�N�g���m�̓����蔻�������
	// �I�u�W�F�N�g���m���������Ă��Ȃ������ꍇ�͉������Ȃ�
	if (!GetSphere()->IsCollide(pTarget->GetSphere()))return;

	// �ړ��O�̍��W��ۑ�����(���W - �ړ��x�N�g��)
	VECTOR prevPos = VSub(m_characterInfo.pos, m_characterInfo.vec);

	VECTOR nextPos;		// �ړ���̍��W
	VECTOR slideVec;	// ����̃I�u�W�F�N�g���l�����Ĉړ�������W

	// �ړ������Ƒ���̍��W���玩���̍��W���������x�N�g���ɐ����ȃx�N�g�����v�Z����
	slideVec = VCross(m_characterInfo.vec,
		VNorm(VSub(m_characterInfo.pos, pTarget->GetInfo().pos)));

	// ��ŏo�����x�N�g�����g���āA��������ւ̈ړ�����������
	slideVec = VCross(VNorm(VSub(m_characterInfo.pos, pTarget->GetInfo().pos)),
		slideVec);

	// ��������ւ̈ړ��������������x�N�g���𑫂�
	nextPos = VAdd(prevPos, slideVec);

	// �����o������
	for (int i = 0; i < kMaxColHitTryNum; i++)
	{
		// ����Ɠ������Ă��Ȃ�������I���
		if (!GetSphere()->IsCollide(pTarget->GetSphere()))return;

		// ����Ƃ̃x�N�g���̌v�Z
		VECTOR move = VSub(m_characterInfo.pos, pTarget->GetInfo().pos);
		// ��ŏo�����x�N�g�����g���đ���Ƃ̋������擾����
		float vecSize = VSize(move);
		// �x�N�g���𐳋K�����ăX���C�h�����鋗���𒲐�����
		move = VScale(move, (1.0f / (vecSize * kSlideLength)));

		// ��������ւ̈ړ��������������x�N�g���ɃX���C�h���鋗���𑫂�
		nextPos = VAdd(nextPos, move);

		// ���W��ۑ�����
		m_characterInfo.pos = nextPos;
	}

	// �V�������W��ۑ�����
	m_characterInfo.pos = nextPos;
}

void CharacterBase::HitGround()
{
	// �W�����v�͂�0�ɂ���
	m_jumpPower = 0.0f;
}

void CharacterBase::UpdateGravity()
{
	// �����鑬�x���ő嗎�����x�𒴂��Ȃ��悤�ɂ���
	m_jumpPower = max(m_jumpPower - (kGravity * kFixGravity), kFallMaxSpeed);

	// ��������
	m_characterInfo.vec.y = m_jumpPower;
}

void CharacterBase::SmoothAngle(float& nowAngle, float nextAngle)
{
	// -180�x�ȉ��ɂȂ�����p�x���傫���Ȃ肷���Ȃ��悤��360�x����
	if (nextAngle < -DX_PI_F)
	{
		nextAngle += DX_TWO_PI_F;
	}
	// 180�x�ȏ�ɂȂ�����p�x���������Ȃ肷���Ȃ��悤��360�x����
	if (nextAngle > DX_PI_F)
	{
		nextAngle -= DX_TWO_PI_F;
	}

	// �p�x�̍������߂�
	float angleDiff = nowAngle - nextAngle;

	// �p�x�̍����ő卷���傫�������ꍇ
	if (angleDiff > kAngleDiffMax)
	{
		// �p�x�̍����������Ȃ肷���Ȃ��悤��360�x����
		nowAngle -= DX_TWO_PI_F;
	}
	// �p�x�̍����ő卷��菬���������ꍇ
	else if (angleDiff < kAngleDiffMin)
	{
		// �p�x�̍����p�x���傫���Ȃ肷���Ȃ��悤��360�x����
		nowAngle += DX_TWO_PI_F;
	}

	// �p�x�̍����������ꍇ�͉��������ɂ��̂܂܎��̊p�x��Ԃ�
	if (angleDiff < kChangeAngleSpeed && angleDiff > -kChangeAngleSpeed)
	{
		nowAngle = nextAngle;
		return;
	}

	/*����ȊO�̏ꍇ�͏������p�x��ω�������*/
	else if (angleDiff > kChangeAngleSpeed)
	{
		nowAngle -= kChangeAngleSpeed;
		return;
	}
	else if (angleDiff < kChangeAngleSpeed)
	{
		nowAngle += kChangeAngleSpeed;
		return;
	}
}
