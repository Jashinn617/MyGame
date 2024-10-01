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
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
#ifdef _DEBUG
	// �ŏ��̃V�[���̃��������m�ۂ���
	m_pScene = std::make_shared<SceneDebug>();
#else
	// �ŏ��̃V�[���̃��������m�ۂ���
	m_pScene = std::make_shared<SceneTitle>();
#endif // _DEBUG

	m_pScene->Init();
}

bool SceneManager::Update()
{
	// �X�V�O�̃��[�f�B���O���Ԃ̎擾
	LONGLONG start = GetNowHiPerformanceCount();

	assert(m_pScene);

	// �p�b�h���̍X�V
	Pad::Update();

	std::shared_ptr<SceneBase> pNext = m_pScene->Update();

	if (!pNext)
	{
		m_pScene->End();
		// null�ŏI��
		return false;
	}

	if (pNext != m_pScene)
	{
		// ���ݏ������̃V�[���̏I������
		m_pScene->End();

		// Update���Ԃ����V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Init();
	}

	m_updateTime = static_cast<float>(GetNowHiPerformanceCount() - start);

	return true;
}

void SceneManager::Draw()
{
	assert(m_pScene);

	LONGLONG start = GetNowHiPerformanceCount();

	m_pScene->Draw();

#ifdef _DEBUG
	// �X�V�A�`�掞�̏������x�𑪂�
	m_drawTime = static_cast<float>(GetNowHiPerformanceCount() - start);

	// �����o�[�̕\��
	float rate = (m_updateTime + m_drawTime) / 16666.6f;
	float width = Game::kScreenWidth * rate;
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kDrawBarColor, true);

	rate = m_updateTime / 16666.6f;
	width = Game::kScreenWidth * rate;
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kUpdateBarColor, true);

#endif // _DEBUG
}

void SceneManager::End()
{
	assert(m_pScene);

	m_pScene->End();
}
