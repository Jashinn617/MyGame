#pragma once
#include "SceneBase.h"

#include <vector>

class Gear;

/// <summary>
/// 装備画面
/// </summary>
class SceneGear : public SceneBase
{
public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneGear();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneGear();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override final;

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
	virtual SceneKind GetSceneKind() override final { return SceneKind::Gear; }

private:	// 関数
	/// <summary>
	/// カーソル更新
	/// </summary>
	void UpdateCursor();

	/// <summary>
	/// テキスト描画
	/// </summary>
	void DrawGearText();

	/// <summary>
	/// 装備品数描画
	/// </summary>
	void DrawGearNum();

	/// <summary>
	/// 装備中装備描画
	/// </summary>
	void DrawEquippedGear();

	/// <summary>
	/// カーソル描画
	/// </summary>
	void DrawCursor();

	/// <summary>
	/// ボックス描画
	/// </summary>
	void DrawBoxes();

private:	// 変数
	int m_mulMarkH;					// ×マーク画像ハンドル
	int m_cursorH;					// カーソル画像ハンドル
	int m_gearBoxH;					// 装備品ボックス画像ハンドル
	int m_explainBoxH;				// 説明文ボックス画像ハンドル
	int m_equipTextH;				// 装備をするテキスト画像ハンドル
	int m_removeEquipTextH;			// 装備を外すテキスト画像ハンドル
	int m_costTextH;				// コストテキスト画像ハンドル
	int m_equippedBoxH;				// 装備中ボックス画像ハンドル
	int m_statusBoxH;				// ステータスボックス画像ハンドル
	std::vector<int> m_gearH;		// 装備品名画像ハンドル
	std::vector<int> m_numH;		// 数字画像ハンドル
	std::vector<int> m_explainH;	// 説明文画像ハンドル
	int m_cursorCount;				// カーソルカウント
	bool m_isCursorLeft;			// カーソルが左にあるかどうか
	std::shared_ptr<Gear> m_pGear;	// 装備品
};

