#include "Player.h"
#include "PlayerState.h"

#include "../Model.h"
#include "../Camera.h"

#include "../../Shader/VertexShader.h"

#include "../../Utility/Sphere.h"


namespace
{
	const char* const kPlayerFileName = "Data/Model/Player/Player.mv1";	// �v���C���[���f���t�@�C���p�X

	constexpr float kMoveSpeedDashRate = 1.2f;	// �_�b�V�������x
	constexpr float kAccelerationRate = 0.5f;	// �����x
	constexpr float kJumpMaxSpeed = 8.0f;		// �W�����v���̍ő呬�x
	constexpr float kGravity = 0.8f;			// �d��
	constexpr float kFallMaxSpeed = -15.0f;		// �ő嗎�����x
	constexpr float kNowVecNum = 0.8f;			// ���݂̕���
	constexpr float kNextVecNum = 0.2f;			// �i�݂�������
	constexpr float kMinJumpRiseNum = 1.0f;		// �㏸���Ɣ��f�����Œ�l
	constexpr float kAngleSpeed = 0.02f;		// ��]���x

	constexpr float kHeight = 35.0f;			// ����
	constexpr float kSize = 15.0f;				// �T�C�Y
	constexpr VECTOR kScale = { 0.11f,0.11f,0.11f };				// �X�P�[��

	/// <summary>
	/// �A�j���[�V�������x
	/// </summary>
	enum kAnimSpeed
	{
		Idle=2,
		Walk=2,
		Dash=1,
		Jump=1,
		Damage=1,
	};

}

Player::Player():
	m_pState(std::make_shared<PlayerState>()),
	m_pCamera(std::make_shared<Camera>())
{
	/*�ړ����x������*/
	m_moveData.walkSpeed = m_statusData.spd;
	m_moveData.dashSpeed = m_statusData.spd * kMoveSpeedDashRate;
	m_moveData.acceleration = m_statusData.spd * kAccelerationRate;
	m_moveData.rotSpeed = kAngleSpeed;

	/*��񏉊���*/
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.modelH = -1;
	m_characterInfo.isExist = true;
	m_objSize = kSize;
	m_angle = 0.0f;

	// �����蔻��|�C���^�쐬
	m_pSphere = std::make_shared<Sphere>(m_characterInfo.pos, m_objSize, kHeight * 0.5f);

	// ���f���|�C���^�쐬
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	// ���f���X�P�[���ݒ�
	m_pModel->SetScale(kScale);
	// �A�j���[�V����������
	m_pModel->SetAnim(m_animData.idle, false, true);

	// �����X�e�C�g�̐ݒ�(�ҋ@��Ԃ���)
	m_pState->SetState(PlayerState::StateKind::Idle);

	// ���f���̒��_�^�C�v�̎擾
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// ���_�^�C�v�̎擾
		//m_vertexShaderType.push_back(MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i));

		// ���_�V�F�[�_�n���h���̎擾
		m_vertexShaderH.push_back(m_pVertexShader->
			SetVertexShaderH(MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i)));
	}
}

Player::~Player()
{
	/*��������*/
}

void Player::Update()
{
	// �X�e�C�g�X�V
	m_pState->Update();
	// �ړ��X�V
	m_characterInfo.vec = Move();
	// �d�͂ɂ�闎������
	UpdateGravity();

	// �_���[�W����


	// �A�j���[�V�����X�V
	m_pModel->Update();
	// ���f�����W�̐ݒ�
	m_pModel->SetPos(m_characterInfo.pos);
	// ���f����]�̐ݒ�
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));

	// �J�����X�V
	m_pCamera->Update(m_characterInfo.pos);

	
}

void Player::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// ���f�����t���[�����Ƃɕ`�悷��
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// �V�F�[�_�̐ݒ�

		// �`��
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// �V�F�[�_���g��Ȃ��ݒ�ɂ���

	// �����蔻��̋��̕`��
	m_pSphere->DebugDraw(0xff0000);
}

void Player::Draw2D()
{
	// �J����2D�����̕`��
	m_pCamera->Draw();

#ifdef _DEBUG
	// �f�o�b�O�p�`��
	DrawFormatString(0, 20, 0x000000, "�v���C���[���W�F%f,%f,%f"
		, m_characterInfo.pos.x, m_characterInfo.pos.y, m_characterInfo.pos.z);
	DrawFormatString(0, 100, 0x000000, "�W�����v�́F%f", m_jumpPower);
#endif // _DEBUG
}

void Player::OnDamage(VECTOR targetPos)
{
}

void Player::OnAttack()
{
}

void Player::EndJump()
{
	// �W�����v�t���O��false�ɂ���
	m_isJump = false;
	// �W�����v�͂�0�ɂ���
	m_jumpPower = 0.0f;

	// �X�e�[�W�N���A���͏������I������
	// if() return;

	// �X�e�C�g�̏I������
	m_pState->EndState();
}

void Player::UpdateAngle()
{
	// �_���[�W���͏��������Ȃ�

}

void Player::UpdateMoveDirection()
{
}

VECTOR Player::Move()
{
	return VECTOR();
}

void Player::InitState()
{
}

void Player::UpdateState()
{
}
