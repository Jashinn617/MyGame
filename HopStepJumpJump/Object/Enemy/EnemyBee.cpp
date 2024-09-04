#include "EnemyBee.h"

#include "../Circle.h"
#include "../Model.h"

#include "../../Util/CsvLoad.h"
#include "../../Util/Time.h"

#include "../../Shader/ToonShader.h"

namespace
{
	constexpr float kModelScalse = 0.3;	// ���f���X�P�[��
	constexpr float kEnemySize = 20;	// �T�C�Y
	constexpr float kHeight = 20.0f;	// ����
}

EnemyBee::EnemyBee(VECTOR pos, VECTOR direction, int turnTime, float speed)
{
	// �A�j���[�V�����̏�����
	CsvLoad::GetInstance().AnimLoad(m_animData, "Bee");

	m_info.pos = pos;
	// �T�C�Y
	m_objSize = kEnemySize;
	m_pCircle = std::make_shared<Circle>(m_info.pos, kEnemySize, kHeight);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);

	// �^�[������܂ł̎���
	m_turnTime = std::make_shared<Time>(turnTime);

	InitMoveSpeed(m_statusData.spd);
	m_moveSpeed = speed;
	m_moveDirectionVec = direction;
	m_moveDirectionVec = VScale(direction, m_moveSpeed);
}

EnemyBee::~EnemyBee()
{
	/*��������*/
}

void EnemyBee::Init()
{
	m_pModel = std::make_shared<Model>(m_modelH);
	m_pModel->SetAnim(m_animData.idle, true, true);
	m_pModel->SetScale(VGet(kModelScalse, kModelScalse, kModelScalse));
	m_pModel->SetRot(m_info.rot);
	m_pModel->SetPos(m_info.pos);
}

void EnemyBee::MoveDirectionUpdate()
{
	// �w�莞�Ԍo�߂���������𔽓]����
	if (m_turnTime->Update())
	{
		m_moveDirectionVec = VScale(m_moveDirectionVec, -1);
		m_turnTime->Reset();
	}
	// Y�����Ȃ�
	m_moveDirectionVec.y = 0.0f;
}

VECTOR EnemyBee::MoveUpdate()
{
	// �ړ������̍X�V
	MoveDirectionUpdate();
	// �p�x�X�V
	AngleUpdate();

	return m_moveDirectionVec;
}