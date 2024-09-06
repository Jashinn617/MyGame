#include "ItemBase.h"

#include "../Player/Player.h"

#include "../ObjectBase.h"
#include "../Model.h"
#include "../Circle.h"

#include "../../Util/Time.h"
#include "../../Util/Input.h"
#include "../../Util/SoundManager.h"

#include "../../Shader/ToonShader.h"

#include "../../Effect/Effekseer3DManager.h"

#include <assert.h>

using namespace CharacterData;

namespace
{
	constexpr int kDeadExistTime = 60;	// ����ł��犮�S�ɏ�����܂ł̎���
	constexpr float kColHeight = -10.0f;	// �����蔻��̍���
}

ItemBase::ItemBase():
	m_moveDirectionVec{0,0,0},
	m_createTime(0),
	m_colHeight(kColHeight)
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

ItemBase::ItemBase(VECTOR pos):
	m_moveDirectionVec{ 0,0,0 },
	m_createTime(0),
	m_colHeight(kColHeight)
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

ItemBase::~ItemBase()
{
	/*��������*/
}

void ItemBase::Init()
{
	/*��������*/
}

void ItemBase::Update(Input& input)
{
	// �ړ��x�N�g���̌v�Z
	m_info.vec = MoveUpdate();

	// ���f���X�V
	m_pModel->Update();

	// �ړ��x�N�g�������ݍ��W�ɑ���
	m_info.pos = VAdd(m_info.pos, m_info.vec);

	// ���W�̐ݒ�
	m_pModel->SetPos(m_info.pos);

	// �V�F�[�_�X�V
}

void ItemBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// ���_���Ƃɕ`�悷��
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		pToonShader->SetShader(shaderType);
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	pToonShader->ShaderEnd();

	m_pCircle->DebugDraw();
}

void ItemBase::OnGet()
{
	// �G�t�F�N�g�𗬂�
	Effekseer3DManager::GetInstance().Add("ItemGet",
		Effekseer3DManager::PlayType::Normal, this, m_info.pos);
	// �A�C�e���̎擾����炷
	SoundManager::GetInstance().Play("ItemGet");
	m_isDead = true;
	// ���݂�����
	m_info.isExist = false;
}

void ItemBase::GameEnd()
{
	m_isGameEnd = true;
}

void ItemBase::InitMoveSpeed(float moveSpeed)
{
	// �ړ����x�̏�����
	m_moveData.walkSpeed = moveSpeed;
	m_moveData.runSpeed = 0.0f;
	m_moveData.acceleration = 0.0f;
}

void ItemBase::MoveDirectionUpdate()
{
	/*��������*/
}

VECTOR ItemBase::MoveUpdate()
{
	return VGet(0.0f,0.0f,0.0f);
}
