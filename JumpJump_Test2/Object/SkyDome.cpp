#include "SkyDome.h"
#include "Model.h"

namespace
{
	constexpr float kRotSpeed = 0.0004f;	// ��]���x
	const char* const kSkyDomeFileName = "Data/Model/Sky/Dome.mv1";		// ���f���̃t�@�C���p�X
	const VECTOR kSkyDomeScale = VGet(35.0f, 35.0f, 35.0f);			// ���f���̃X�P�[��
}

SkyDome::SkyDome():
	m_rot(0.0f)
{
	// ���f���|�C���^�̐���
	m_pModel = std::make_shared<Model>(kSkyDomeFileName);

	// �X�J�C�h�[���̃X�P�[����ݒ肷��
	m_pModel->SetScale(kSkyDomeScale);
}

SkyDome::~SkyDome()
{
}

void SkyDome::Update(VECTOR pos)
{
	// ��]
	m_rot += kRotSpeed;

	// ���]������l�����Z�b�g����
	if (m_rot >= DX_PI_F)m_rot = 0.0f;

	// �X�J�C�h�[���̍X�V
	m_pModel->SetRot(VGet(0.0f, m_rot, 0.0f));
	m_pModel->SetPos(VGet(pos.x, 0.0f, pos.z));
}

void SkyDome::Draw()
{
	m_pModel->Draw();

}
