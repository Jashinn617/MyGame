#include "CharacterBase.h"
#include "Circle.h"
#include "../Util/Input.h"

#include "Item/ItemBase.h"


namespace
{
	constexpr int kMaxColHitPolyNum = 2000;	// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;	// �ǂɉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;	// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kGravity = 0.8f;	// �d��
	constexpr float kFallMaxSpeed = -15.0f;	// �ő嗎�����x
	constexpr float kChangeAngleSpeed = 0.25f;	// ���炩�Ɋp�x���ړ������鑬�x
	constexpr float kAngleDiffMax = DX_PI_F + 0.3f;	// �p�x�̍ő卷
	constexpr float kAngleDiffMin = -DX_PI_F - 0.3f;	// �p�x�̍ŏ���
	constexpr float kSlideLength = 10.0f;	// �����o���̑傫��	
}

CharacterBase::CharacterBase():
	m_moveData{},
	m_animData{},
	m_jumpPower(0.0f),
	m_isJump(false),
	m_isDead(false)
{
	/*��������*/
}

CharacterBase::~CharacterBase()
{
	/*��������*/
}

void CharacterBase::Init()
{
	/*��������*/
}

void CharacterBase::Update(Input& input)
{
	/*��������*/
}

void CharacterBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	/*��������*/
}

void CharacterBase::OnDamage(VECTOR targetPos)
{
	/*��������*/
}

void CharacterBase::MoveCollCharacterUpdate(CharacterBase* pTarget)
{
	// �������^�[�Q�b�g������ł���Ƃ��͔�������Ȃ�
	if (m_isDead || pTarget->IsDead())
	{
		return;
	}

	// �I�u�W�F�N�g���m�̓����蔻��
	if (!GetCircle()->IsCollide(pTarget->GetCircle())) return;

	// �ړ��O�̍��W�̐ݒ�
	VECTOR prevPos = VSub(m_info.pos, m_info.vec);

	// �ړ���̍��W
	VECTOR nextPos;

	// �^�[�Q�b�g�̃I�u�W�F�N�g���l�����Ĉړ�����
	VECTOR slideVec;

	// �i�s�����ƃ^�[�Q�b�g�̍��W���玩���̍��W���������x�N�g���ɐ����ȃx�N�g�����o��
	slideVec = VCross(m_info.vec, VNorm(VSub(m_info.pos, pTarget->GetInfo().pos)));

	// ���ŏo�����x�N�g���ƃ^�[�Q�b�g�̍��W����
	// �����̍��W���������x�N�g���ɐ����ȃx�N�g�����o����
	// ���̈ړ���������^�[�Q�b�g�I�u�W�F�N�g�̕����̈ړ������𔲂����x�N�g�����o��
	slideVec = VCross(VNorm(VSub(m_info.pos, pTarget->GetInfo().pos)), slideVec);

	// �Ǖ����̈ړ������𔲂����x�N�g���𑫂�
	nextPos = VAdd(prevPos, slideVec);

	// �����o������������
	for (int i = 0; i < kMaxColHitTryNum; i++)
	{
		// �I�u�W�F�N�g�Ɠ������Ă��Ȃ������珈���𔲂���
		if (!GetCircle()->IsCollide(pTarget->GetCircle())) break;

		VECTOR move = VSub(m_info.pos, pTarget->GetInfo().pos);

		float vecSize = VSize(move);

		move = VScale(move, (1.0f / (vecSize * kSlideLength)));

		// �������Ă�����K�苗�����v���C���[��G�Ɣ��΂̕����Ɉړ�������
		nextPos = VAdd(nextPos, move);

		m_info.pos = nextPos;
	}
	// �V�������W��ۑ�����
	m_info.pos = nextPos;
}

void CharacterBase::AttackPlayerCollEnemy(CharacterBase* pEnemy)
{
	// �G������ł����画������Ȃ�
	if (pEnemy->IsDead()) return;
	// �I�u�W�F�N�g���m�̓����蔻��
	if (!GetCircle()->IsCollide(pEnemy->GetCircle())) return;

	OnAttack();
	pEnemy->OnDamage(m_info.pos);
}

void CharacterBase::AttackEnemyCollPlayer(CharacterBase* pPlayer)
{
	// �v���C���[���U����H����Ă���Œ��������ꍇ�͔�������Ȃ�
	if (pPlayer->IsDamage()) return;
	// �I�u�W�F�N�g���m�̓����蔻��
	if (!GetCircle()->IsCollide(pPlayer->GetCircle())) return;

	pPlayer->OnDamage(m_info.pos);
}

void CharacterBase::PlayerToItem(CharacterBase* pItem)
{
	// �I�u�W�F�N�g���m�̓����蔻��
	if (!GetCircle()->IsCollide(pItem->GetCircle())) return;

	// �A�C�e�����Q�b�g����
	dynamic_cast<ItemBase*>(pItem)->OnGet();
}

void CharacterBase::EndJump()
{
	m_isJump = false;
	m_jumpPower = 0.0f;
}

void CharacterBase::HitGroundUpdate()
{
	m_jumpPower = 0.0f;
}

void CharacterBase::GravityUpdate()
{
	// �ړ��ʂ̍X�V
	// �����鑬�x���ő嗎�����x�𒴂��Ȃ��悤�ɂ���
	m_jumpPower = max(m_jumpPower - (kGravity * 0.5f), kFallMaxSpeed);

	// ����
	m_info.vec.y = m_jumpPower;
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

	// �p�x�̍���180�x�ȏゾ�����ꍇ
	if (angleDiff > kAngleDiffMax)
	{
		// �p�x�̍����������Ȃ肷���Ȃ��悤��360�x����
		nowAngle -= DX_TWO_PI_F;
	}
	// �ȉ��������ꍇ
	else if (angleDiff < kAngleDiffMin)
	{
		// �p�x�̍����p�x���傫���Ȃ肷���Ȃ��悤��360�x����
		nowAngle += DX_TWO_PI_F;
	}

	// �p�x�̍������Ȃ��ꍇ�͉��������ɂ��̂܂܎��̊p�x��Ԃ�
	if (angleDiff < kChangeAngleSpeed && 
		angleDiff > -kChangeAngleSpeed)
	{
		nowAngle = nextAngle;
		return;
	}
	// ����ȊO�̏ꍇ�͏������p�x��ω�������
	// �p�x�̍����傫������kChangeAngleSpeed������
	else if (angleDiff > kChangeAngleSpeed)
	{
		nowAngle -= kChangeAngleSpeed;
		return;
	}
	// �p�x�̍����������Ƃ���kChangeAngleSpeed�𑫂�
	else if (angleDiff < kChangeAngleSpeed)
	{
		nowAngle += kChangeAngleSpeed;
		return;
	}
}
