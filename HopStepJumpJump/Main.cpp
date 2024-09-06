#include "DxLib.h"
#include "EffekseerForDXLib.h"

#include "Util/Game.h"
#include "Util/Input.h"
#include "Util//Pad.h"

#include "Scene/SceneManager.h"
#include "Effect/Effekseer3DManager.h"
#include "Util/SoundManager.h"

#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(true);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[���o�[�̃^�C�g���̐ݒ�
	SetWindowText(Game::kTitleText);

	// �X�N���[���T�C�Y�̐ݒ�
	ChangeWindowMode(Game::kWindowMode);
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);	

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// Effekseer�̏�����
	Effekseer_Init(8000);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(false);
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������A2DirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);

	// �|���S���̗����͕`�悵�Ȃ�
	SetUseBackCulling(true);

	//// �G�t�F�N�g�̃��[�h
	Effekseer3DManager::GetInstance();
	//// �T�E���h�̃��[�h
	//SoundManager::GetInstance();

	// ���C�g�̐ݒ�
	SetLightPosition(Game::kLightPos);
	SetLightDirection(Game::kLightDir);

	// �A�X�y�N�g��̐ݒ�
	SetCameraDotAspect(Game::kAspect);
	// �J�����̎���p�̐ݒ�
	SetupCamera_Perspective(Game::kFov);

	// �V�[���Ǘ�
	shared_ptr<SceneManager> pScene = make_shared<SceneManager>();
	pScene->Init();

	// ����
	Input input;

	while (ProcessMessage() == 0)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// ���͂̍X�V
		input.Update();

		// �Q�[���̏���
		pScene->Update(input);
		pScene->Draw();

		// �G�t�F�N�g�̍X�V�A�`��
		Effekseer3DManager::GetInstance().Update();
		Effekseer3DManager::GetInstance().Draw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->End();

	Effkseer_End();	 // Effekseer�̏I������

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}