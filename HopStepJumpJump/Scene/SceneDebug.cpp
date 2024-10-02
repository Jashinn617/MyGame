#include "DxLib.h"

#include "SceneDebug.h"
#include "SceneStage.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneRanking.h"

#include "../Object/ObjectManager.h"

#include "../Util/Vec2.h"
#include "../Util/Pad.h"

namespace
{
	constexpr float kCursorPosX = 500.0f;		// �����J�[�\���ʒuX
	constexpr float kCursorPosY = 300.0f;		// �����J�[�\���ʒuY

	constexpr float kCursorMove = 50.0f;		// �J�[�\���̈ړ���
}

SceneDebug::SceneDebug():
	m_count(0)
{
	// �ړ��p�����̐ݒ�
	m_sceneString[static_cast<int>(SceneType::Debug)] = "Debug";
	m_sceneString[static_cast<int>(SceneType::Stage1)] = "Stage1";
	m_sceneString[static_cast<int>(SceneType::Stage2)] = "Stage2";
	m_sceneString[static_cast<int>(SceneType::Title)] = "Title";
	m_sceneString[static_cast<int>(SceneType::StageSelect)] = "StageSelect";
	m_sceneString[static_cast<int>(SceneType::Ranking)] = "Ranking";
	m_sceneString[static_cast<int>(SceneType::Test)] = "Test";
}

SceneDebug::~SceneDebug()
{
	/*��������*/
}

void SceneDebug::Init()
{
	/*��������*/
}

std::shared_ptr<SceneBase> SceneDebug::Update()
{
	// �{�^���������ꂽ��I�����ꂽ�V�[���ɑJ�ڂ���
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return UpdateNextScene();
	}

	// �J�[�\���X�V
	UpdateCursor();

	// �t�F�[�h�X�V
	UpdateFade();
	
	return shared_from_this();
}

void SceneDebug::Draw()
{
	// ������̕`��
	for (int i = 0; i < static_cast<int>(m_sceneString.size()); i++)
	{
		if (m_count == i)
		{
			// �I�΂�Ă��镶���͐Ԃ�����
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),
				m_sceneString[i].c_str(),
				0xff0000);
		}
		else
		{
			// ���̑��̕����͔�
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),
				m_sceneString[i].c_str(),
				0xffffff);
		}
	}

	DrawFormatString(0, 0, 0x00ffff, "Debug");
	DrawFormatString(60, 0, 0x00ffff, "�V�[����I�����Ă�������(A�Ō���)");

	DrawFade();
}

void SceneDebug::End()
{
	/*��������*/
}

void SceneDebug::UpdateCursor()
{
	// �J�[�\���̈ړ�
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_count--;
		// �J�[�\�������[�v����悤�ɂ���
		if (m_count < 0) m_count = static_cast<int>(m_sceneString.size() - 1);
	}
	else if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_count++;
		// �J�[�\�������[�v����悤�ɂ���
		if (m_count >= static_cast<int>(m_sceneString.size())) m_count = 0;
	}
}

std::shared_ptr<SceneBase> SceneDebug::UpdateNextScene()
{
	// ���̃V�[���̐ݒ�
	std::shared_ptr<SceneBase> nextScene = nullptr;

	// �I�����ꂽ�V�[���ɑJ�ڂ���
	switch (m_count)
	{
	case static_cast<int>(SceneType::Debug):
		nextScene = std::make_shared<SceneDebug>();
		break;
	case static_cast<int>(SceneType::Stage1):
		nextScene = std::make_shared<SceneStage>(Game::Stage::Stage1);
		break;
	case static_cast<int>(SceneType::Stage2):
		nextScene = std::make_shared<SceneStage>(Game::Stage::Stage2);
		break;
	case static_cast<int>(SceneType::Title):
		nextScene = std::make_shared<SceneTitle>();
		break;
	case static_cast<int>(SceneType::StageSelect):
		nextScene = std::make_shared<SceneSelect>();
		break;
	case static_cast<int>(SceneType::Ranking):
		nextScene = std::make_shared<SceneRanking>();
		break;
	case static_cast<int>(SceneType::Test):
		nextScene = std::make_shared<SceneStage>(Game::Stage::Test);
		break;
	default:
		// �����I������Ă��Ȃ������ꍇ�̓V�[���J�ڂ��s��Ȃ��悤�ɂ���
		return shared_from_this();
		break;
	}
	return nextScene;
}
