#include "SceneManager.h"
#include "SceneDebug.h"
#include "SceneTitle.h"

#include "../Util/Pad.h"
#include "../Util/Game.h"

#include <assert.h>

namespace
{
	constexpr int kBarPosX = 0;								// �����o�[�̍��WX
	constexpr int kBarPosY = Game::kScreenHeight - 48;		// �����o�[�̍��WY
	constexpr int kUpdateBarColor = 0x0000ff;					// �X�V�̏����o�[�̐F
	constexpr int kDrawBarColor = 0xff0000;						// �`��̏����o�[�̐F
}

SceneManager::SceneManager() :
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
#ifdef _DEBUG
	// �ŏ��̃V�[���̃��������m�ۂ���
	// �f�o�b�O�p�V�[���ɔ��
	m_pScene = std::make_shared<SceneDebug>();
#else
	// �ŏ��̃V�[���̃��������m�ۂ���
	// �^�C�g���V�[���ɔ��
	m_pScene = std::make_shared<SceneTitle>();
#endif // _DEBUG

	// �V�[���̏�����
	m_pScene->Init();
}

bool SceneManager::Update()
{
#ifdef _DEBUG
	// �X�V�O���[�f�B���O���Ԃ̎擾
	LONGLONG start = GetNowHiPerformanceCount();
#endif // _DEBUG

	// �V�[����null�������ꍇ�͎~�܂�
	assert(m_pScene);

	// �p�b�h���̍X�V
	Pad::Update();

	// ���̃V�[���̎擾
	std::shared_ptr<SceneBase> pNext = m_pScene->Update();

	// ���̃V�[�������݂��Ă��Ȃ������ꍇ
	if (!pNext)
	{
		// ���ݏ������̃V�[���̏I������
		m_pScene->End();
		// null�ŏI��
		return false;
	}

	// ���̃V�[�������݂̃V�[���ł͖��������ꍇ
	if (pNext != m_pScene)
	{
		// ���ݏ������̃V�[���̏I������
		m_pScene->End();

		// Update���Ԃ����V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Init();
	}

#ifdef _DEBUG
	// �X�V���̏������x�𑪂�
	m_updateTime = static_cast<float>(GetNowHiPerformanceCount() - start);
#endif // _DEBUG

	return true;
}

void SceneManager::Draw()
{
#ifdef _DEBUG
	// �`��O���[�f�B���O���Ԃ̎擾	
	LONGLONG start = GetNowHiPerformanceCount();
#endif // _DEBUG

	// �V�[����null�������ꍇ�͎~�܂�
	assert(m_pScene);
	// �`��
	m_pScene->Draw();

#ifdef _DEBUG
	// �`�掞�̏������x�𑪂�
	m_drawTime = static_cast<float>(GetNowHiPerformanceCount() - start);

	/*�����o�[�̕\��*/
	// �`�揈���o�[
	float rate = (m_updateTime + m_drawTime) / 16666.6f;
	float width = Game::kScreenWidth * rate;
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kDrawBarColor, true);
	// �X�V�����o�[
	rate = m_updateTime / 16666.6f;
	width = Game::kScreenWidth * rate;
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kUpdateBarColor, true);

#endif // _DEBUG
}

void SceneManager::End()
{
	// �V�[����null�������ꍇ�͎~�܂�
	assert(m_pScene);
	// �I������
	m_pScene->End();
}
