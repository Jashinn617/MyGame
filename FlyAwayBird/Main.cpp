#include "DxLib.h"
#include "Util/Game.h"
#include "Util/Input.h"
#include "Util/HandleManager.h"
#include "Scene/SceneManager.h"

#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	// ��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 3D�`��̉��s�����g�p����
	SetUseZBuffer3D(true);

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Data/font/GN-KillGothic-U-KanaNA.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, _T("�t�H���g�Ǎ����s"), _T(""), MB_OK);
	}


	// �Q�[���o�[�̃^�C�g��
	SetWindowText(_T("�Ƃ�Ƃ�Ƃ肭��I�I"));

	// �n���h���Ǘ�
	HandleManager handle;

	// �V�[���Ǘ�
	shared_ptr<SceneManager> pScene = make_shared<SceneManager>();
	pScene->Init(handle);

	// ����
	Input input;

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// ���͂̍X�V
		input.Update();

		// �Q�[���̏���
		pScene->Update(input,handle);
		pScene->Draw(handle);

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	pScene->End();

	// ********** �t�H���g�̃A�����[�h **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, _T("remove failure"), _T(""), MB_OK);
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

