#pragma once

#include <vector>
#include <memory>
#include <functional>

class Stamina;
class Time;

class PlayerState
{
public:
	// 状態
	enum class State
	{
		Idle,		// 待機
		Walk,		// 歩き
		Run,		// 走り
		Jump,		// ジャンプ
		KnockBack,	// ノックバック
	};

private:	// 構造体

	// 状態情報
	struct StateData
	{

	};
};

