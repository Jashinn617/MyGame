#include "DxLib.h"

#include "Util/Game.h"
#include "Util/Input.h"
#include "Scene/SceneManager.h"

#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Data/font/GN-KillGothic-U-KanaNA.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, _T("�t�H���g�Ǎ����s"), _T(""), MB_OK);
	}

	// �Q�[���o�[�̃^�C�g��
	SetWindowText(_T("�W�����v�W�����v"));

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

	// ********** �t�H���g�̃A�����[�h **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, _T("remove failure"), _T(""), MB_OK);
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}