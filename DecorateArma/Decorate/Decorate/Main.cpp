#include "DxLib.h"
#include "EffekseerForDXLib.h"

#include "Utility/Game.h"

#include "Scene/SceneManager.h"

#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���o�[�̃^�C�g���ݒ�
	SetWindowText(Game::kTitleText);

	// �E�B���h�E���[�h�̐ݒ�
	ChangeWindowMode(Game::kWindowMode);

	// �X�N���[���T�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kClorDepth);

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	// Effekseer�̏�����
	Effekseer_Init(8000);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);

	// �|���S���̗�����`�悷��
	SetUseBackCulling(false);

	// �G�t�F�N�g�̃��[�h

	// �T�E���h�̃��[�h

	// ���C�g���W�̐ݒ�
	SetLightPosition(Game::kLightPos);
	// ���C�g�����̐ݒ�
	SetLightDirection(Game::kLightDirection);

	// �J�����̃A�X�y�N�g��̐ݒ�
	SetCameraDotAspect(Game::kAspect);
	// �J�����̎���p�̐ݒ�
	SetupCamera_Perspective(Game::kFov);

	// �V�[���Ǘ��|�C���^�쐬
	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();

	// �V�[��������
	pScene->Init();

	while (ProcessMessage() == 0)
	{
		// ���̃t���[���̊J�n�����̕ۑ�
		LONGLONG time = GetNowHiPerformanceCount();
		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		// �V�[���|�C���^��nullptr�������狭���I������
		if (!pScene->Update()) break;
		// �`��
		pScene->Draw();

		// �G�t�F�N�g�̍X�V

		// �G�t�F�N�g�̕`��

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) // esc�L�[�������ꂽ�ꍇ
		{
			// �V�[���I������
			pScene->End();
			// �����I��
			break;
		}

		// fps���Œ肷��
		while (GetNowHiPerformanceCount() - time < static_cast<int>(Game::kStandardTimePer1Frame)){}
	}

	// Effekseer�I������
	Effkseer_End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I�� 
	return 0;
}