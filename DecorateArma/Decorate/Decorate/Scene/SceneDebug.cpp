#include "DxLib.h"

#include "SceneDebug.h"
#include "SceneStage.h"

#include "../Utility/Pad.h"
#include "../Utility/Game.h"

namespace
{
	constexpr float kCursorPosX = Game::kScreenWidth * 0.2f;								// 初期のカーソル座標X
	constexpr float kCursorPosY = Game::kScreenHeight * 0.2f;								// 初期のカーソル座標Y
	constexpr float kSceneDescriptionPosX = Game::kScreenWidth * 0.1f;						// シーン説明用文字座標X
	constexpr float kSceneDescriptionPosY = Game::kScreenHeight * 0.05f;					// シーン説明用文字座標Y

	constexpr float kCursorMove = Game::kScreenHeight * 0.03f;		// カーソルの移動量

	constexpr unsigned int kNormalStringColor = 0xffffff;			// 通常の文字色
	constexpr unsigned int kSelectStringColor = 0xff0000;			// 選択中の文字色
	constexpr unsigned int kSceneDescriptionStringColor = 0x00ffff;	// シーン説明用文字色
}

SceneDebug::SceneDebug():
	m_cursorCount(0)
{
	// 移動用文字の設定
	m_sceneString[static_cast<int>(SceneType::Debug)] = "Debug";		// デバッグ
	m_sceneString[static_cast<int>(SceneType::Test)] = "Test";			// テスト
	m_sceneString[static_cast<int>(SceneType::Title)] = "Title";		// タイトル
	m_sceneString[static_cast<int>(SceneType::Select)] = "Select";		// セレクト
	m_sceneString[static_cast<int>(SceneType::Stage1)] = "Stage1";		// ステージ1
	m_sceneString[static_cast<int>(SceneType::Clear)] = "Clear";		// クリア
	m_sceneString[static_cast<int>(SceneType::GameOver)] = "GameOver";	// ゲームオーバー
}

std::shared_ptr<SceneBase> SceneDebug::Update()
{
	// ボタンが押された場合、選択されたシーンに遷移する
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return MoveNextScene();
	}

	// カーソル更新
	UpdateCursor();

	return shared_from_this();
}

void SceneDebug::Draw()
{
	// 文字描画
	for (int i = 0; i < static_cast<int>(m_sceneString.size()); i++)
	{
		if (m_cursorCount == i)	// その文字を選択中だった場合
		{
			// 選択中の文字色にする
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),	// 座標
				m_sceneString[i].c_str(),							// 文字
				kSelectStringColor);								// 色
		}
		else	// 選択中で無かった時
		{
			// 通常の文字色にする
			DrawString(static_cast<int>(kCursorPosX),
				static_cast<int>(kCursorPosY + (i * kCursorMove)),	// 座標
				m_sceneString[i].c_str(),							// 文字
				kNormalStringColor);								// 色
		}
	}

	// シーン名描画
	DrawFormatString(static_cast<int>(kSceneDescriptionPosX), 0,
		kSceneDescriptionStringColor, "DebugScene");
	// シーン説明描画
	DrawFormatString(static_cast<int>(kSceneDescriptionPosX),
		static_cast<int>(kSceneDescriptionPosY),
		kSceneDescriptionStringColor, "シーンを選択してください(Aで決定)");
}

void SceneDebug::UpdateCursor()
{
	// カーソル移動
	if (Pad::IsTrigger(PAD_INPUT_UP))	// 上ボタンが押された場合
	{
		// カーソルカウントを減らす
		m_cursorCount--;
		// カウントが0より小さくなったらカーソルがループするようにする
		if (m_cursorCount < 0)m_cursorCount = static_cast<int>(m_sceneString.size() - 1);
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))		// 下ボタンが押された場合
	{
		// カーソルカウントを増やす
		m_cursorCount++;
		// カーソルが文字列の数より大きくなったらループするようにする
		if (m_cursorCount > static_cast<int>(m_sceneString.size() - 1))m_cursorCount = 0;
	}
}

std::shared_ptr<SceneBase> SceneDebug::MoveNextScene()
{
	// 次のシーンの設定
	std::shared_ptr<SceneBase> nextScene = nullptr;

	// 選択されたシーンに遷移する
	switch (m_cursorCount)
	{
	case static_cast<int>(SceneType::Debug):	// デバッグ
			nextScene = std::make_shared<SceneDebug>();
			break;
	case static_cast<int>(SceneType::Test):		// テスト
		nextScene = std::make_shared<SceneStage>(Game::StageKind::StageTest);
		break;
	case static_cast<int>(SceneType::Title):	// タイトル
		return shared_from_this();
		break;
	case static_cast<int>(SceneType::Select):	// セレクト
		return shared_from_this();
		break;
	case static_cast<int>(SceneType::Stage1):	// ステージ1
		nextScene = std::make_shared<SceneStage>(Game::StageKind::Stage1);
		break;
	case static_cast<int>(SceneType::Clear):	// クリア
		return shared_from_this();
		break;
	case static_cast<int>(SceneType::GameOver):	// ゲームオーバー
		return shared_from_this();
		break;
	default:	// 何も選択されていなかった場合はシーン遷移を行わないようにする
		return shared_from_this();
		break;
	}
	// シーンを返す
	return nextScene;
}