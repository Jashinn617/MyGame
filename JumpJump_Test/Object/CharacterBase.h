#pragma once
#include "ObjectBase.h"
class CharacterBase : public ObjectBase
{
public:

	// 移動情報
	struct MoveData
	{
		float walkSpeed = 0;	// 歩きスピード
		float runSpeed = 0;		// 走りスピード
		float acceleration = 0;	// 加速度
		float rotSpeed = 0;		// 回転スピード
	};

	// アニメーション情報
	struct AnimData
	{
		int8_t idle = 0;		// 待機
		int8_t walk = 0;		// 歩き
		int8_t run = 0;			// 走り
		int8_t jumpStart = 0;	// ジャンプ時
		int8_t jumpIdle = 0;	// ジャンプ中
		int8_t knockBack = 0;	// ノックバック
	};

public:


protected:	// 関数

protected:	// 変数
	MoveData m_moveData;	// 移動情報
	AnimData m_animData;	// アニメーション情報

	

};

