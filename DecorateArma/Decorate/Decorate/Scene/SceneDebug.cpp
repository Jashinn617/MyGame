#include "DxLib.h"

#include "SceneDebug.h"
#include "SceneStage.h"

#include "../Utility/Pad.h"
#include "../Utility/Game.h"

namespace
{
	constexpr float kCursorPosX = Game::kScreenWidth * 0.2f;								// �����̃J�[�\�����WX
	constexpr float kCursorPosY = Game::kScreenHeight * 0.2f;								// �����̃J�[�\�����WY
	constexpr float kSceneDescriptionPosX = Game::kScreenWidth * 0.1f;						// �V�[�������p�������WX
	constexpr float kSceneDescriptionPosY = Game::kScreenHeight * 0.05f;					// �V�[�������p�������WY

	constexpr float kCursorMove = Game::kScreenHeight * 0.03f;		// �J�[�\���̈ړ���

	constexpr unsigned int kNormalStringColor = 0xffffff;			// �ʏ�̕����F
	constexpr unsigned int kSelectStringColor = 0xff0000;			// �I�𒆂̕����F
	constexpr unsigned int kSceneDescriptionStringColor = 0x00ffff;	// �V�[�������p�����F
}

SceneDebug::SceneDebug():
	m_cursorCount(0)
{
	// �ړ��p�����̐ݒ�
	m_sceneString[static_cast<int>(SceneType::Debug)] = "Debug";		// �f�o�b�O
	m_sceneString[static_cast<int>(SceneType::Test)] = "Test";			// �e�X�g
	m_sceneString[static_cast<int>(SceneType::Title)] = "Title";		// �^�C�g��
	m_sceneString[static_cast<int>(SceneType::Select)] = "Select";		// �Z���N�g
	m_sceneString[static_cast<int>(SceneType::Stage1)] = "Stage1";		// �X�e�[�W1
	m_sceneString[static_cast<int>(SceneType::Clear)] = "Clear";		// �N���A
	m_sceneString[static_cast<int>(SceneType::GameOver)] = "GameOver";	// �Q�[���I�[�o�[
}

std::shared_ptr<SceneBase> SceneDebug::Update()
{
	// �{�^���������ꂽ�ꍇ�A�I�����ꂽ�V�[���ɑJ�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return MoveNextScene();
	}

	// �J�[�\���X�V
	UpdateCursor();

	return shared_from_this();
}

void SceneDebug::Draw()
{
	// �����`��
	for (int i = 0; i < static_cast<int>(m_sceneString.size()); i++)
	{
		if (m_cursorCount == i)	// ���̕�����I�𒆂������ꍇ
		{
			// �I�𒆂̕����F�ɂ���
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),	// ���W
				m_sceneString[i].c_str(),							// ����
				kSelectStringColor);								// �F
		}
		else	// �I�𒆂Ŗ���������
		{
			// �ʏ�̕����F�ɂ���
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),	// ���W
				m_sceneString[i].c_str(),							// ����
				kNormalStringColor);								// �F
		}
	}

	// �V�[�����`��
	DrawFormatString(static_cast<int>(kSceneDescriptionPosX), 0,
		kSceneDescriptionStringColor, "DebugScene");
	// �V�[�������`��
	DrawFormatString(static_cast<int>(kSceneDescriptionPosX),
		static_cast<int>(kSceneDescriptionPosY),
		kSceneDescriptionStringColor, "�V�[����I�����Ă�������(A�Ō���)");
}

void SceneDebug::UpdateCursor()
{
	// �J�[�\���ړ�
	if (Pad::IsTrigger(PAD_INPUT_UP))	// ��{�^���������ꂽ�ꍇ
	{
		// �J�[�\���J�E���g�����炷
		m_cursorCount--;
		// �J�E���g��0��菬�����Ȃ�����J�[�\�������[�v����悤�ɂ���
		if (m_cursorCount < 0)m_cursorCount = static_cast<int>(m_sceneString.size() - 1);
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))		// ���{�^���������ꂽ�ꍇ
	{
		// �J�[�\���J�E���g�𑝂₷
		m_cursorCount++;
		// �J�[�\����������̐����傫���Ȃ����烋�[�v����悤�ɂ���
		if (m_cursorCount > static_cast<int>(m_sceneString.size() - 1))m_cursorCount = 0;
	}
}

std::shared_ptr<SceneBase> SceneDebug::MoveNextScene()
{
	// ���̃V�[���̐ݒ�
	std::shared_ptr<SceneBase> nextScene = nullptr;

	// �I�����ꂽ�V�[���ɑJ�ڂ���
	switch (m_cursorCount)
	{
	case static_cast<int>(SceneType::Debug):	// �f�o�b�O
			nextScene = std::make_shared<SceneDebug>();
			break;
	case static_cast<int>(SceneType::Test):		// �e�X�g
		nextScene = std::make_shared<SceneStage>(Game::StageKind::StageTest);
		break;
	case static_cast<int>(SceneType::Title):	// �^�C�g��
		return shared_from_this();
		break;
	case static_cast<int>(SceneType::Select):	// �Z���N�g
		return shared_from_this();
		break;
	case static_cast<int>(SceneType::Stage1):	// �X�e�[�W1
		nextScene = std::make_shared<SceneStage>(Game::StageKind::Stage1);
		break;
	case static_cast<int>(SceneType::Clear):	// �N���A
		return shared_from_this();
		break;
	case static_cast<int>(SceneType::GameOver):	// �Q�[���I�[�o�[
		return shared_from_this();
		break;
	default:	// �����I������Ă��Ȃ������ꍇ�̓V�[���J�ڂ��s��Ȃ��悤�ɂ���
		return shared_from_this();
		break;
	}
	// �V�[����Ԃ�
	return nextScene;
}