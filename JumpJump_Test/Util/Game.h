#pragma once
#include "DxLib.h"

/// <summary>
/// ゲーム全体で使用する定数を定義するnamespace
/// </summary>
namespace Game
{
	constexpr int kScreenWidth = 1920;	// 画面横サイズ
	constexpr int kScreenHeight = 1080;	// 画面縦サイズ

	constexpr int kColorDepth = 32;		// カラービット数
	
	constexpr VECTOR kLightPos = { -1000.0f,2000.0f,-1000.0f };		// ライトの位置
	constexpr VECTOR kLightDir = { -1.0f, 2.0f, -1.0f };			// ライトの向き

	// ステージ名
	enum class Stage
	{
		Stage1,
		Stage2,
		Trutorial,
		StageSelect,
		StageName,
	};
}
