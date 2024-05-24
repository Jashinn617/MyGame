#include "DxLib.h"

#include "Util/Game.h"
#include "Util/Input.h"
#include "Scene/SceneManager.h"

#include <memory>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// ********** フォントのロード **********
	LPCSTR font_path = "Data/font/GN-KillGothic-U-KanaNA.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, _T("フォント読込失敗"), _T(""), MB_OK);
	}

	// ゲームバーのタイトル
	SetWindowText(_T("ジャンプジャンプ"));

	// シーン管理
	shared_ptr<SceneManager> pScene = make_shared<SceneManager>();
	pScene->Init();

	// 入力
	Input input;

	while (ProcessMessage() == 0)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// 入力の更新
		input.Update();

		// ゲームの処理
		pScene->Update(input);
		pScene->Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->End();

	// ********** フォントのアンロード **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, _T("remove failure"), _T(""), MB_OK);
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}