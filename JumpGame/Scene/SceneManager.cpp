#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "../Input.h"

SceneManager::SceneManager():
	m_pScene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// �ŏ��̃V�[���̃��������m�ۂ���
	m_pScene = make_shared<SceneTitle>();
	m_pScene->Init();
}

void SceneManager::Update(Input& input)
{
	shared_ptr<SceneBase> pNext = m_pScene->Update(input);
	if (pNext != m_pScene)
	{
		// ���ݏ������̃V�[���̏I������
		m_pScene->End();

		// Update���Ԃ����V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Init();
	}
}

void SceneManager::Draw()
{
	m_pScene->Draw();
}

void SceneManager::End()
{
	m_pScene->End();
}
