#pragma once
#include "SceneBase.h"

#include <array>

class SceneSelect : public SceneBase
{
public:
	enum class NextScene
	{
		My,
		Stage1,
		Stage2,
		Ranking,
		End
	};

public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();

	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

	virtual SceneKind GetSceneKind() { return SceneKind::StageSelect; }

private:	// 関数
	/// <summary>
	/// セレクトの更新
	/// </summary>
	void  SelectUpdate();

	/// <summary>
	/// 背景の描画
	/// </summary>
	void BackDraw();

	/// <summary>
	/// セレクトボックスの描画
	/// </summary>
	void SelectBoxDraw();

private:	// 変数
	int m_backgroundH;					// 背景画像のハンドル
	std::array<int, 4> m_SelectBoxH{};	// セレクトボックスのハンドル
	int m_scrollX;						// 背景のスクロール値
	int m_backWidth;					// 画像の横幅
	int m_backHeight;					// 画像の縦幅
	bool m_isUp;						// 上が選択されているかどうか
	bool m_isLeft;						// 左が選択されているかどうか

	NextScene m_next;					// 次のシーン
};

