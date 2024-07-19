#pragma once
#include "DxLib.h"
#include "../Util/CharacterData.h"

#include <array>
#include <memory>

class Model;

namespace ColInfo
{
	// 最大当たり判定ポリゴン数
	constexpr int kMaxColHitPolyNum = 2000;
	// 壁押し出し処理の最大試行回数
	constexpr int kMaxColHitTryNum = 16;
	// 壁押し出し時にスライドさせる距離
	constexpr float kColHitSlideLength = 1.0f;
}

class ObjectBase
{
public:	// 列挙体

	// 物体の分類
	enum class ColType
	{
		None,		// 無し
		Player,		// プレイヤー
		Enemy,		// エネミー
		Field,		// フィールド
		Object,		// オブジェクト
		Item,		// アイテム
	};

public:	// 関数
	ObjectBase();

	virtual ~ObjectBase();

	virtual void Init() abstract;
	virtual void Update() abstract;

	virtual void Draw() abstract;

	virtual void Draw();

	virtual void Draw2D();

	/// <summary>
	/// 存在が消えてからのカウント
	/// (存在が消えてからも倒れる演出で少しの間だけモデルを描画させるため)
	/// </summary>
	/// <returns></returns>
	bool IsExistCount();

	/// <summary>
	/// オブジェクトを消す時の処理
	/// </summary>
	void End();

	// メインポインタの設定

	// モデルハンドルの設定

};

