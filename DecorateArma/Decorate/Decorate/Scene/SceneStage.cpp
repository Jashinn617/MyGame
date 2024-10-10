#include "SceneStage.h"
#include "StageManager.h"


#include <cassert>

namespace
{
	constexpr float kCameraNear = 5.0f;		// �J������O�N���b�v����
	constexpr float kCameraFar = 5000.0f;	// �J�������N���b�v����
}

SceneStage::SceneStage(Game::StageKind stage):
	m_stageKind(stage),
	m_pStageManager(std::make_shared<StageManager>(stage)),
	m_pNextScene(nullptr)
{
	/*��������*/
}

SceneStage::~SceneStage()
{
	/*��������*/
}

void SceneStage::Init()
{
	// �X�e�[�W�}�l�[�W���[�̏�����
	m_pStageManager->Init();
}

std::shared_ptr<SceneBase> SceneStage::Update()
{
	// �X�e�[�W�}�l�[�W���[�X�V
	m_pStageManager->Update();

	return shared_from_this();
}

void SceneStage::Draw()
{
	// �X�e�[�W�}�l�[�W���[�`��
	m_pStageManager->Draw();

#ifdef _DEBUG
	// �f�o�b�O�p�V�[�����`��
	if (static_cast<int>(m_stageKind) == 0)
	{
		DrawFormatString(0, 0, 0xffffff, "StageTest");
	}
	else
	{
		DrawFormatString(0, 0, 0xffffff, "Stage%d", static_cast<int>(m_stageKind));
	}
#endif // _DEBUG
}
