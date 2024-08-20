#include "MoveDirectionVec.h"
#include "../Util/Input.h"
#include "CharacterData.h"

namespace
{
	constexpr float kUp = -1.0f;	// 上移動方向ベクトル
	constexpr float kDown = 1.0f;	// 下移動方向ベクトル
	constexpr float kRight = 1.0f;	// 右移動方向ベクトル
	constexpr float kLeft = -1.0f;	// 左移動方向ベクトル
	constexpr float kZero = 0.0f;	// 移動方向ベクトルなし
}

MoveDirectionVec::MoveDirectionVec():
	m_directionVec{0,0,0}
{
}

MoveDirectionVec::~MoveDirectionVec()
{
}

void MoveDirectionVec::Update(Input& input)
{
	// 移動ベクトルの初期化
	m_directionVec = VGet(0.0f, 0.0f, 0.0f);

	// 左ボタンを押されたらプレイヤーの向きを左に
	if (input.IsPressing("left"))
	{
		m_directionVec.x = kLeft;
	}
	// 右ボタンを押されたらプレイヤーの向きを右に
	else if (input.IsPressing("right"))
	{
		m_directionVec.x = kRight;
	}
	else
	{
		m_directionVec.x = kZero;
	}

	// 上ボタンを押されたらプレイヤーの向きを上に
	if (input.IsPressing("up"))
	{
		m_directionVec.z = kUp;
	}
	// 下ボタンを押されたらプレイヤーの向きを下に
	else if (input.IsPressing("down"))
	{
		m_directionVec.z = kDown;
	}
	else
	{
		m_directionVec.z = kZero;
	}

	// 移動方向ベクトルを正規化する
	if (VSize(m_directionVec) >= 1.0f)
	{
		m_directionVec = VNorm(m_directionVec);
	}
}

void MoveDirectionVec::SetDirectionVec()
{
	// 移動方向ベクトルを初期化
	m_directionVec = VGet(0.0f, kUp, 0.0f);
}