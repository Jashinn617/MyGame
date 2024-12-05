#pragma once
#include "SceneBase.h"

#include <vector>

/// <summary>
/// セレクト画面
/// </summary>
class SceneSelect : public SceneBase
{
public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneSelect();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init()override final;

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>次のシーン</returns>
	virtual std::shared_ptr<SceneBase> Update() override final;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() override final;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() override final;

	/// <summary>
	/// シーン種類の取得
	/// </summary>
	/// <returns>シーンの種類</returns>
	virtual SceneKind GetSceneKind() override final { return SceneKind::Select; }

private:	// 関数
	/// <summary>
	/// カーソル更新
	/// </summary>
	void UpdateCursor();

	/// <summary>
	/// 背景描画
	/// </summary>
	void DrawBack();

	/// <summary>
	/// ボックス描画
	/// </summary>
	void DrawBox();

private:	// 変数
	std::vector<int> m_backH;		// 背景画像ハンドル
	int m_stageSelectBoxH;			// ステージ選択ボックスハンドル
	int m_gearBoxH;					// 装備ボックスハンドル
	int m_optionBoxH;				// オプションボックスハンドル
	int m_gameEndBoxH;				// ゲーム終了ボックスハンドル
	int m_descriptionBoxH;			// 説明文ボックスハンドル
	int m_selectButtonH;			// セレクトボタンハンドル
	int m_decisionButtonH;			// 決定ボタンハンドル

	int m_backWidth;		// 背景画像横幅
	int m_backHeight;		// 背景画像縦幅

	int m_scrollXBack;		// 奥スクロール値
	int m_scrollXMiddle;	// 中スクロール値
	int m_scrollXFront;		// 手前スクロール値

	bool m_isCursorUp;			// カーソルが上にいるか
	bool m_isCursorLeft;		// カーソルが左にいるか
	bool m_isCursorGameEnd;		// カーソルがゲーム終了にいるか
};