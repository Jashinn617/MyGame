#include "EnemyBase.h"

#include "../Player/Player.h"

#include "../ObjectBase.h"
#include "../Model.h"
#include "../Circle.h"

#include "../../Util/Time.h"
#include "../../Util/Input.h"

#include "../../Shader/ToonShader.h"

#include <assert.h>

using namespace CharacterData;

namespace
{
	constexpr int kDeadExistTime = 60;	// ����ł��犮�S�ɏ�����܂ł̎���
	constexpr float kColHeight = -10.0f;	// �����蔻��̍���
}

EnemyBase::EnemyBase():
	m_colHeight(0),
	m_moveDirectionVec{0,0,0},
	m_enemyToPlayerVec{0,0,0},
	m_deadTime(0)
{
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 10;
	m_objSize = 0.0f;

	// ����ł���̎���
	m_deadTime = std::make_shared<Time>(kDeadExistTime);

	// ���S���V�F�[�_
}

EnemyBase::EnemyBase(VECTOR pos, float speed) :
	m_colHeight(0),
	m_moveDirectionVec{ 0,0,0 },
	m_enemyToPlayerVec{ 0,0,0 },
	m_deadTime(0)
{
	m_info.pos = pos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 10;
	m_objSize = 0.0f;

	// ����ł���̎���
	m_deadTime = std::make_shared<Time>(kDeadExistTime);

	// ���S���V�F�[�_
}

EnemyBase::EnemyBase(VECTOR pos, VECTOR direction, int turnTime, float speed) :
	m_colHeight(0),
	m_moveDirectionVec{ 0,0,0 },
	m_enemyToPlayerVec{ 0,0,0 },
	m_deadTime(0)
{
	m_info.pos = pos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 10;
	m_objSize = 0.0f;

	// ����ł���̎���
	m_deadTime = std::make_shared<Time>(kDeadExistTime);

	// ���S���V�F�[�_
}


EnemyBase::~EnemyBase()
{
	/*��������*/
}

void EnemyBase::Init()
{
	/*��������*/
}

void EnemyBase::Update(Input& input)
{
	// �ړ��x�N�g���̌v�Z
	m_info.vec = MoveUpdate();

	// ���f���X�V
	m_pModel->Update();

	// �ړ��x�N�g�������ݍ��W�ɑ���
	m_info.pos = VAdd(m_info.pos, m_info.vec);

	// ���W�̐ݒ�
	m_pModel->SetPos(m_info.pos);

	// �p�x�X�V
	m_pModel->SetRot(VGet(0.0f, m_angle * DX_PI_F, 0.0f));

	// �V�F�[�_�X�V

}

void EnemyBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	/*��������*/
}

void EnemyBase::StageClear()
{
	OnDead();
}

void EnemyBase::OnDamage(VECTOR targetPos)
{
	// �v���C���[��Y�ʒu�������̈ʒu���Ⴉ�����ꍇ
	if (targetPos.y <= m_info.pos.y) return;

	OnDead();
}

void EnemyBase::OnDead()
{
	m_isDead = true;

	m_info.isExist = false;
}

void EnemyBase::InitMoveSpeed(float moveSpeed)
{
	// �ړ����x�̏�����
	m_moveData.walkSpeed = moveSpeed;
	m_moveData.runSpeed = 0.0f;
	m_moveData.acceleration = 0.0f;
}

void EnemyBase::AngleUpdate()
{
	//������������
	float nextAngle = atan2(m_moveDirectionVec.x, m_moveDirectionVec.z);

	//���炩�Ɏw�肵�������Ɍ������߂̊֐�
	SmoothAngle(m_angle, nextAngle);
}

void EnemyBase::MoveDirectionUpdate()
{
	/*��������*/
}

VECTOR EnemyBase::MoveUpdate()
{
	return VGet(0.0f, 0.0f, 0.0f);
}