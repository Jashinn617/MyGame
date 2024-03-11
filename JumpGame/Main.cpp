#include "DxLib.h"
#include "Handle/ModelManager.h"
#include "Scene/SceneManager.h"
#include <memory>

using namespace std;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(3.0f, 3000.0f);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 450, -1000), VGet(0.0f, 0.0f, 0.0f));

	// ハンドルの取得
	shared_ptr<ModelManager> pModel = make_shared<ModelManager>();
	
	// シーン管理
	shared_ptr<SceneManager> pScene = make_shared<SceneManager>();
	pScene->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();		

		// ゲームの処理
		pScene->Update();
		pScene->Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	pScene->End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}