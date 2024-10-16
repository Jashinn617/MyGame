#pragma once
#include "DxLib.h"

#include <vector>
#include <memory>
#include <functional>

class Time;

class PlayerState
{
public:
	/// <summary>
	/// ステイトの種類
	/// </summary>
	enum class StateKind
	{
		Idle,		// 待機
		Walk,		// 歩き
		Dash,		// 走り
		Jump,		// ジャンプ
		KnockBack,	// ノックバック
		StateClear,	// ステージクリア
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerState();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerState();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ダメージを受けた
	/// </summary>
	void OnDamage();

	/// <summary>
	/// ステージクリア
	/// </summary>
	void StageClear();

	/// <summary>
	/// ステイト情報の追加
	/// </summary>
	/// <param name="stateInit">初期化</param>
	/// <param name="stateUpdate">更新</param>
	/// <param name="stateKind">ステイトの種類</param>
	void AddState(std::function<void(void)> stateInit, 
		std::function<void(void)> stateUpdate, 
		StateKind stateKind);

	/// <summary>
	/// ステイトの設定
	/// </summary>
	/// <param name="state">ステイト</param>
	void SetState(StateKind stateKind);

	/// <summary>
	/// ステイトの終了処理
	/// </summary>
	void EndState();

	/// <summary>
	/// 現在のステイトの取得
	/// </summary>
	/// <returns></returns>
	StateKind GetState() const { return m_pNowState.stateKind; }

private:	// 構造体
	/// <summary>
	/// ステイト情報
	/// </summary>
	struct StateData
	{
		std::function<void(void)> stateInit{};		// 状態初期化処理
		std::function<void(void)> stateUpdate{};	// 状態更新処理
		StateKind stateKind{};						// 状態の種類
	};

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
	void StateChange(StateKind stateKind);

private:	// 変数
	bool m_isAction;						// アクション行動中か
	std::vector<StateData> m_pState;		// 状態の格納
	StateData m_pNowState;					// 現在の状態
};