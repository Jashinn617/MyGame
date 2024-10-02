#include "EnemyBase.h"

#include "../Player/Player.h"

#include "../ObjectBase.h"
#include "../Model.h"
#include "../Circle.h"

#include "../../Util/Time.h"
#include "../../Util/SoundManager.h"

#include "../../Effect/Effekseer3DManager.h"

#include "../../Shader/ToonShader.h"

#include <assert.h>

using namespace CharacterData;

namespace
{
	constexpr int kDeadExistTime = 60;		// ����ł��犮�S�ɏ�����܂ł̎���
	constexpr float kColHeight = -10.0f;	// �����蔻��̍���
	constexpr float kHeadPos = 20;			// �G�̓��̈ʒu
	constexpr float kEndTime = 80;			// �Q�[���I�����Ă���̎���
	constexpr float kEndDeadTime = 200;		// �Q�[���I����ɏ����Ă���̎���
}

EnemyBase::EnemyBase() :
	m_colHeight(0),
	m_isEnd(false),
	m_isEndDead(false),
	m_moveDirectionVec{ 0,0,0 },
	m_enemyToPlayerVec{ 0,0,0 },
	m_deadTime(std::make_shared<Time>(kDeadExistTime)),
	m_endTime(std::make_shared<Time>(kEndTime)),
	m_endDeadTime(std::make_shared<Time>(kEndDeadTime))
{
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 0.0f;
	m_objSize = 0.0f;
}

EnemyBase::EnemyBase(VECTOR pos, float speed) :
	m_colHeight(0),
	m_isEnd(false),
	m_isEndDead(false),
	m_moveDirectionVec{ 0,0,0 },
	m_enemyToPlayerVec{ 0,0,0 },
	m_deadTime(std::make_shared<Time>(kDeadExistTime)),
	m_endTime(std::make_shared<Time>(kEndTime)),
	m_endDeadTime(std::make_shared<Time>(kEndDeadTime))
{
	m_info.pos = pos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 0.0f;
	m_objSize = 0.0f;
}

EnemyBase::EnemyBase(VECTOR pos, VECTOR direction, int turnTime, float speed) :
	m_colHeight(0),
	m_isEnd(false),
	m_isEndDead(false),
	m_moveDirectionVec{ 0,0,0 },
	m_enemyToPlayerVec{ 0,0,0 },
	m_deadTime(std::make_shared<Time>(kDeadExistTime)),
	m_endTime(std::make_shared<Time>(kEndTime)),
	m_endDeadTime(std::make_shared<Time>(kEndDeadTime))
{
	m_info.pos = pos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 0.0f;
	m_objSize = 0.0f;
}


EnemyBase::~EnemyBase()
{
	/*��������*/
}

void EnemyBase::Init()
{
	/*��������*/
}

void EnemyBase::Update()
{
	if (m_isEnd)
	{
		// �ړ��l��0�ɂ���
		m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	}
	else
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
	}
}

void EnemyBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// ���f���̕`��
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// �V�F�[�_�̒��_�^�C�v�̎擾
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		pToonShader->SetShader(shaderType);
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	pToonShader->ShaderEnd();

	// �����蔻��̕`��
	m_pCircle->DebugDraw();
}

void EnemyBase::StageClear()
{
	/*��������*/
}

void EnemyBase::GameEnd()
{
	// �Q�[���̏I���t���O�𗧂Ă�
	m_isEnd = true;

	// ��莞�Ԃ������������
	if (m_endTime->Update())
	{
		// �G�t�F�N�g�𗬂�
		Effekseer3DManager::GetInstance().Add("GameEndDead", 
			Effekseer3DManager::PlayType::Normal, this, m_info.pos);

		// ���S����
		OnDead();

		// ����SE�����ĂȂ������ꍇ
		if(!SoundManager::GetInstance().IsDesignationCheckPlaySound("EnemyEndDead"))
		{
			// SE��炷
			SoundManager::GetInstance().Play("EnemyEndDead");
			
		}
		
		// �Q�[���I�����̏������I����
		m_isGameEnd = true;
	}	
}

void EnemyBase::OnDamage(VECTOR targetPos)
{
	if (m_isEnd) return;
	// �v���C���[��Y�ʒu�������̈ʒu���Ⴉ�����ꍇ
	if (targetPos.y <= m_info.pos.y + kHeadPos) return;

	// �U������炷
	SoundManager::GetInstance().Play("Attack");

	// �G�t�F�N�g�𗬂�
	Effekseer3DManager::GetInstance().Add("EnemyDead"
		, Effekseer3DManager::PlayType::Normal, this, m_info.pos);
	
	// ���S����
	OnDead();
}

void EnemyBase::OnDead()
{
	// ���S�����t���O�𗧂Ă�
	m_isDead = true;
	// ���݂�����
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
	// atan2�Ŋp�x�̌v�Z�������Z���𔽓]����
	float angleZ = m_moveDirectionVec.z * -1;
	//�������������̐ݒ�
	float nextAngle = atan2(m_moveDirectionVec.x, angleZ);

	//���炩�Ɏw�肵�������Ɍ���
	SmoothAngle(m_angle, nextAngle);
}

void EnemyBase::MoveDirectionUpdate()
{
	/*��������*/
}

VECTOR EnemyBase::MoveUpdate()
{
	/*��������*/
	return VGet(0.0f, 0.0f, 0.0f);
}