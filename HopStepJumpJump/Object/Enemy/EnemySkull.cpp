#include "EnemySkull.h"

#include "../Circle.h"
#include "../Model.h"
#include "../ObjectManager.h"

#include "../Player/Player.h"

#include "../../Util/CsvLoad.h"
#include "../../Util/Time.h"

#include "../../Shader/ToonShader.h"

namespace
{
	constexpr float kModelScalse = 0.3;	// ���f���X�P�[��
	constexpr float kEnemySize = 20;	// �T�C�Y
	constexpr float kHeight = 20.0f;	// ����
}

EnemySkull::EnemySkull(VECTOR pos, float speed)
{
	// �A�j���[�V�����̏�����
	CsvLoad::GetInstance().AnimLoad(m_animData, "Skull");

	m_info.pos = pos;
	// �T�C�Y
	m_objSize = kEnemySize;
	m_pCircle = std::make_shared<Circle>(m_info.pos, kEnemySize, kHeight);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);

	InitMoveSpeed(m_statusData.spd);
	m_moveSpeed = speed;
}

EnemySkull::~EnemySkull()
{
	/*��������*/
}

void EnemySkull::Init()
{
	m_pModel = std::make_shared<Model>(m_modelH);
	m_pModel->SetAnim(m_animData.idle, true, true);
	m_pModel->SetScale(VGet(kModelScalse, kModelScalse, kModelScalse));
	m_pModel->SetRot(m_info.rot);
	m_pModel->SetPos(m_info.pos);
}

void EnemySkull::MoveDirectionUpdate()
{
	// �v���C���[�̂�������ɐi��
	m_enemyToPlayerVec = VSub(m_pObjectManager->GetPlayer()->GetInfo().pos, m_info.pos);
	m_moveDirectionVec = VNorm(m_enemyToPlayerVec);
}

VECTOR EnemySkull::MoveUpdate()
{
	// �ړ������̍X�V
	MoveDirectionUpdate();
	// �p�x�̍X�V
	AngleUpdate();

	// �ړ��x�N�g���̐���
	VECTOR move = VNorm(m_moveDirectionVec);

	move.x *= m_moveSpeed;
	move.z *= m_moveSpeed;

	return move;
}
