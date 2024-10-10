#include "SceneManager.h"
#include "SceneDebug.h"

#include "../Utility/Pad.h"
#include "../Utility/Game.h"

#include <cassert>

namespace
{
	constexpr float kBarPosX = 0;									// �����o�[�̍��WX
	constexpr float kStringPosX = 10;								// �o�[�̐����p������̍��WX
	constexpr float kUpdateBarPosY = Game::kScreenHeight * 0.8f;	// �X�V�����o�[�̍��WY
	constexpr float kDrawBarPosY = Game::kScreenHeight * 0.9f;		// �`�揈���o�[�̍��WY

	constexpr unsigned int kUpdateBarColor = 0x0000ff;				// �X�V�����o�[�̐F
	constexpr unsigned int kDrawBarColor = 0xff0000;				// �`�揈���o�[�̐F
	constexpr unsigned int kStringColor = 0xffffff;					// �����F
}

SceneManager::SceneManager():
	m_pScene(nullptr),
	m_updateTime(0),
	m_drawTime(0)
{
	/*��������*/
}

SceneManager::~SceneManager()
{
	/*��������*/
}

void SceneManager::Init()
{
	/*�ŏ��̃V�[���̃��������m�ۂ���*/
#ifdef _DEBUG
	// �f�o�b�O�p�V�[���ɔ��
	m_pScene = std::make_shared<SceneDebug>();
#else
	// �^�C�g���V�[���ɔ��
	m_pScene = std::make_shared<SceneDebug>();
#endif // DEBUG

	// �V�[���̏�����
	m_pScene->Init();
}

bool SceneManager::Update()
{
#ifdef _DEBUG
	// �X�V�O���[�f�B���O���Ԏ擾
	LONGLONG start = GetNowHiPerformanceCount();
#endif // _DEBUG

	// �V�[����nullptr�������ꍇ�͎~�܂�
	assert(m_pScene);

	// �p�b�h���̍X�V����
	Pad::Update();

	// ���̃V�[���̎擾�A�V�[���̍X�V����
	std::shared_ptr<SceneBase> pNext = m_pScene->Update();

	// ���̃V�[�������݂��Ă��Ȃ������ꍇ
	if (!pNext)
	{
		// ���ݏ������̃V�[���̏I���������s��
		m_pScene->End();
		// false��Ԃ�
		return false;
	}

#ifdef _DEBUG
	// LB�������ꂽ�ꍇ
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		// �f�o�b�O�V�[���ɔ��
		pNext = std::make_shared<SceneDebug>();
	}
#endif

	// ���̃V�[�������݂̃V�[���ł͖��������ꍇ
	if (pNext != m_pScene)
	{
		// ���ݏ������̃V�[���̏I���������s��
		m_pScene->End();

		// �V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Init();
	}

#ifdef _DEBUG
	// LB�������ꂽ�ꍇ
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		// �f�o�b�O�p�X�e�[�W�ɔ��
		pNext = std::make_shared<SceneDebug>();
	}

	// �X�V���̏������x�𑪂�
	m_updateTime = static_cast<float>(GetNowHiPerformanceCount() - start);
#endif // _DEBUG

	// �����܂ŗ�����V�[���͑��݂��邽�߁Atrue��Ԃ�
	return true;
}

void SceneManager::Draw()
{
#ifdef _DEBUG
	// �`��̃��[�f�B���O���Ԏ擾
	LONGLONG start = GetNowHiPerformanceCount();
#endif // _DEBUG

	// �V�[����nullptr�������ꍇ�͎~�܂�
	assert(m_pScene);

	// �`�揈��
	m_pScene->Draw();

#ifdef _DEBUG
	// �`�掞�̏������x�𑪂�
	m_drawTime = static_cast<float>(GetNowHiPerformanceCount() - start);

	/*�����o�[�̕`��*/
	// �`�揈���o�[
	float rate = (m_updateTime + m_drawTime) / Game::kStandardTimePer1Frame;
	float width = Game::kScreenWidth * rate;
	// �`��
	DrawBox(kBarPosX, kDrawBarPosY, static_cast<int>(width), Game::kScreenHeight, kDrawBarColor, true);
	DrawFormatString(kStringPosX, kDrawBarPosY, kStringColor, "�`�揈��");
	// �X�V�����o�[
	rate = m_updateTime / Game::kStandardTimePer1Frame;
	width = Game::kScreenWidth * rate;
	// �`��
	DrawBox(kBarPosX, kUpdateBarPosY, static_cast<int>(width), Game::kScreenHeight, kUpdateBarColor, true);
	DrawFormatString(kStringPosX, kUpdateBarPosY, kStringColor, "�X�V����");
#endif // _DEBUG
}

void SceneManager::End()
{
	// �V�[����nullptr�������ꍇ�͎~�߂�
	assert(m_pScene);
	// �I������
	m_pScene->End();
}