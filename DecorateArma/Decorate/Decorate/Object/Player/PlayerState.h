#pragma once
#include "DxLib.h"

#include <memory>

class Player;

/// <summary>
/// プレイヤーのステイトを管理するクラス
/// </summary>
class PlayerState
{
public:	// 列挙型

	/// <summary>
	/// ステイトの種類
	/// </summary>
	enum class StateKind
	{
		Idle,		// 待機
		Walk,		// 歩き
		Dash,		// ダッシュ
		Jump,		// ジャンプ
		Damage,		// ダメージ
		StateNum,	// ステイト数
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pPlayer">プレイヤーポインタ</param>
	PlayerState(Player* pPlayer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerState();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ダメージ処理
	/// </summary>
	void OnDamage();

	/// <summary>
	/// ステイトの設定
	/// </summary>
	/// <param name="stateKind"></param>
	void SetState(StateKind stateKind);

	/// <summary>
	/// ステイトの終了処理
	/// </summary>
	void EndState();

	StateKind GetState()const { return m_nowState; }

private:	// 関数
	/// <summary>
	/// 待機状態への変更
	/// </summary>
	void StateTransitionIdle();

	/// <summary>
	/// 歩き状態への変更
	/// </summary>
	void StateTransitionWalk();

	/// <summary>
	/// ダッシュ状態への変更
	/// </summary>
	void StateTransitionDash();

	/// <summary>
	/// ジャンプ状態への変更
	/// </summary>
	void StateTransitionJump();

	/// <summary>
	/// 各ステイトの遷移
	/// </summary>
	void StateTransition();

	/// <summary>
	/// ステイト変更
	/// </summary>
	/// <param name="state">ステイト</param>
	void ChangeState(StateKind stateKind);

private:	// 変数
	bool m_isAction;		// アクション行動中か
	StateKind m_nowState;	// 現在のステイト
	Player* m_pPlayer;		// プレイヤーポインタ
};