#include "SceneStage.h"
#include "StageSceneManager.h"
#include "SceneSelect.h"
#include "SceneDebug.h"
#include "SceneTitle.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Field.h"
#include "../Object/SkyDome.h"

#include "../Util/Collision.h"
#include "../Util/Pad.h"
#include "../Util/SoundManager.h"

#include <cassert>
#include <functional>

namespace
{
	// �I�v�V�����摜�t�@�C��
	const char* const kOptionImgFileName[4] =
	{
		"Data/Img/Option/OptionText1.png",
		"Data/Img/Option/OptionText2.png",
		"Data/Img/Option/OptionText3.png",
		"Data/Img/Option/OptionText4.png",
	};
	constexpr int kOptionImgPosX = Game::kScreenWidth / 2;	// �I�v�V�����摜���WX
	constexpr int kOptionImgPosY[4] = { 150,450,650,850 };	// �I�v�V�����摜���WX
	constexpr float kButtonSize = 0.8f;						// �I�v�V�����摜�T�C�Y
	constexpr float kButtonSelectSize = 1.0f;				// �I������Ă���I�v�V�����摜�T�C�Y
	constexpr int kOptionSelectNum = 3;						// �I�v�V�������̃Z���N�g�̐�
	constexpr int kOptionBackAlpha = 220;					// �I�v�V�������̔w�i�s�����x

	constexpr float kCameraNear = 5.0f;						// �J������O�N���b�v����
	constexpr float kCameraFar = 5000.0f;					// �J�������N���b�v����
}

SceneStage::SceneStage(Game::Stage stage) :
	m_cursorCount(0),
	m_isOption(false),
	m_isSceneEnd(false),
	m_nextScene(nullptr),
	m_stageKind(stage)
{
	// �X�e�[�W�}�l�[�W���[�|�C���^�̍쐬
	m_pStageSceneManager = std::make_shared<StageSceneManager>(stage);

	// �J�����̐ݒ�
	SetCameraNearFar(kCameraNear, kCameraFar);

	// �{�^���T�C�Y�̏�����
	for (int i = 0; i < m_buttonSize.size(); i++)
	{
		m_buttonSize[i] = 0;
	}

	// �摜�̃��[�h
	for (int i = 0; i < m_optionH.size(); i++)
	{
		m_optionH[i] = LoadGraph(kOptionImgFileName[i]);
		assert(m_optionH[i] != -1);
	}
}

SceneStage::~SceneStage()
{
	// �摜�̃f���[�g
	for (int i = 0; i < m_optionH.size(); i++)
	{
		DeleteGraph(m_optionH[i]);
	}
}

void SceneStage::Init()
{
	// �X�e�[�W�}�l�[�W���[�̏�����
	m_pStageSceneManager->Init();
}

std::shared_ptr<SceneBase> SceneStage::Update()
{
	// �t�F�[�h�X�V
	UpdateFade();

#ifdef _DEBUG
	// LB�������ꂽ�ꍇ
	if (Pad::isTrigger(PAD_INPUT_5))
	{
		// �f�o�b�O�ɔ��
		return std::make_shared<SceneDebug>();
	}
#endif // _DEBUG

	// Start�{�^���������ꂽ�ꍇ
	if (Pad::isTrigger(PAD_INPUT_8))
	{
		// �I�v�V�������J��
		m_isOption = true;
		// �J�[�\���̃J�E���g������������
		m_cursorCount = 0;
	}

	// ���̃V�[���ɉ�����������Ă�����
	if (m_nextScene != nullptr)
	{
		// ���̃V�[����ς�s��
		return m_nextScene;
	}

	// �I�v�V�������J����Ă����ꍇ
	if (m_isOption)
	{
		// �I�v�V�����X�V
		UpdateOption();
	}
	else
	{
		// �X�e�[�W�}�l�[�W���[�X�V
		m_pStageSceneManager->Update();

		// ���̃V�[���̐ݒ�
		switch (m_pStageSceneManager->GetNextScene())
		{
		case StageSceneManager::NextScene::GameScene:
			// �Q�[���V�[��
			return std::make_shared<SceneStage>(m_stageKind);
			break;
		case StageSceneManager::NextScene::Select:
			// �Z���N�g�V�[��
			return std::make_shared<SceneSelect>();
			break;
		case StageSceneManager::NextScene::My:
			// �����̃V�[��
			return shared_from_this();
			break;
		default:
			break;
		}
	}
	return shared_from_this();
}

void SceneStage::Draw()
{
	// �X�e�[�W�}�l�[�W���[�`��
	m_pStageSceneManager->Draw();

	// �I�v�V�������J����Ă����ꍇ
	if (m_isOption)
	{
		// �I�v�V�����`��
		DrawOption();
	}

	// �t�F�[�h�`��
	DrawFade();
}

void SceneStage::End()
{
	/*��������*/
}

void SceneStage::DrawOption()
{
	// ���w�i
	// �s�����x������������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kOptionBackAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �e�L�X�g�`��
	// �T�C�Y�͌Œ�
	DrawRotaGraph(kOptionImgPosX, kOptionImgPosY[0],
		kButtonSize, 0.0f, m_optionH[0], true);

	// �e�L�X�g�`��
	// �I������Ă��邩�ǂ����ŃT�C�Y���ς��
	DrawRotaGraph(kOptionImgPosX, kOptionImgPosY[1],
		m_buttonSize[0], 0.0f, m_optionH[1], true);
	DrawRotaGraph(kOptionImgPosX, kOptionImgPosY[2],
		m_buttonSize[1], 0.0f, m_optionH[2], true);
	DrawRotaGraph(kOptionImgPosX, kOptionImgPosY[3],
		m_buttonSize[2], 0.0f, m_optionH[3], true);
}

void SceneStage::UpdateOption()
{
	/*�J�E���g�̐؂�ւ�*/
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		SoundManager::GetInstance().Play("Select");
		m_cursorCount--;

		// �J�[�\�������[�v����悤�ɂ���
		if (m_cursorCount >= kOptionSelectNum) m_cursorCount = 0;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		SoundManager::GetInstance().Play("Select");
		m_cursorCount++;

		// �J�[�\�������[�v����悤�ɂ���
		if (m_cursorCount < 0) m_cursorCount = kOptionSelectNum - 1;
	}

	// A�{�^����B�{�^���������ꂽ�ꍇ
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
	{
		if (m_cursorCount == 0)
		{
			// SE��炷
			SoundManager::GetInstance().Play("Decide");
			// �Q�[���ɖ߂�
			m_isOption = false;
			m_nextScene = nullptr;
		}
		else if (m_cursorCount == 1)
		{
			// BGM������
			SoundManager::GetInstance().DesignationStopSound("MainScene");
			// SE��炷
			SoundManager::GetInstance().Play("SceneChange");
			// �ŏ�����
			m_nextScene = std::make_shared<SceneStage>(m_stageKind);

		}
		else if (m_cursorCount == 2)
		{
			// BGM������
			SoundManager::GetInstance().DesignationStopSound("MainScene");
			// SE��炷
			SoundManager::GetInstance().Play("SceneChange");
			// �Z���N�g�ɖ߂�
			m_nextScene = std::make_shared<SceneSelect>();
		}
	}

	// �{�^���T�C�Y�̐؂�ւ�
	for (int i = 0; i < m_buttonSize.size(); i++)
	{
		if (i == m_cursorCount)	// �I������Ă����ꍇ
		{
			m_buttonSize[i] = kButtonSelectSize;
		}
		else	// �I������Ă��Ȃ������ꍇ
		{
			m_buttonSize[i] = kButtonSize;
		}
	}
}