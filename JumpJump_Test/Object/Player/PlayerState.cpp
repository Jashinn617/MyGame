#include "PlayerState.h"
#include "Stamina.h"
#include "../../Util/Input.h"

PlayerState::PlayerState(std::shared_ptr<Stamina> pStamina):
	m_isAction(false),
	m_pStamina(pStamina)
{
}

void PlayerState::Update(Input& input)
{
	// 状態遷移
	StateTransition(input);

	m_pNowState.stateUpdate();

	// 歩き、走り状態ではないときはサウンドを止める
}

void PlayerState::OnDamage()
{
	// 現在の状態がノックバックの時は何もせずに終了する
	if (m_pNowState.stateKind == StateKind::KnockBack) return;

	// ノックバック状態に遷移する
	for (auto& changeState : m_pState)
	{
		// 状態がノックバックの時
		if (changeState.stateKind == StateKind::KnockBack)
		{
			// 状態変更
			m_pNowState = changeState;
			// 状態の初期化
			m_pNowState.stateInit();
			m_isAction = true;
			return;
		}
	}
}

void PlayerState::StageClear()
{
	// 現在の状態がステージクリアの時は何もせずに終了する
	if (m_pNowState.stateKind == StateKind::StateClear) return;

	// ステージクリア状態に遷移する
	for (auto& changeState : m_pState)
	{
		// 状態がステージクリアの時
		if (changeState.stateKind == StateKind::StateClear)
		{
			// 状態変更
			m_pNowState = changeState;
			// 状態の初期化
			m_pNowState.stateInit();
			m_isAction = true;
			return;
		}
	}
}

void PlayerState::AddState(std::function<void(void)> stateInit, std::function<void(void)> stateUpdate, StateKind stateKind)
{
	// 状態追加用の変数の設定
	StateData state;
	state.stateInit = stateInit;
	state.stateUpdate = stateUpdate;
	state.stateKind = stateKind;

	// 状態追加
	m_pState.push_back(state);
}

void PlayerState::SetState(StateKind stateKind)
{
	for (auto& changeState : m_pState)
	{
		// 状態の種類が引数の状態の時
		if (changeState.stateKind == stateKind)
		{
			// 状態の変更
			m_pNowState = changeState;
			return;
		}
	}
}

void PlayerState::EndState()
{
	// アクションの終了
	m_isAction = false;
}

void PlayerState::StateTransitionIdle(Input& input)
{
	// アクション中の場合は何もせずに終了する
	if (m_isAction) return;

	// 移動ボタンが何も押されていなかった場合
	if (!input.IsPressing("left") && !input.IsPressing("right") &&
		!input.IsPressing("up") && !input.IsPressing("down"))
	{
		StateChange(StateKind::Idle);
	}
}

void PlayerState::StateTransitionWalk(Input& input)
{
	// アクション中の場合は何もせずに終了する
	if (m_isAction) return;

	// 移動ボタンが何かしら押されていた場合
	if (input.IsPressing("left") || input.IsPressing("right") ||
		input.IsPressing("up") || input.IsPressing("down"))
	{
		StateChange(StateKind::Walk);
	}
}

void PlayerState::StateTransitionDash(Input& input)
{
	// アクション中の場合は何もせずに終了する
	if (m_isAction) return;

	// 移動ボタンが何も押されていなかった場合は何もせずに終了する
	if (!input.IsPressing("left") && !input.IsPressing("right") &&
		!input.IsPressing("up") && !input.IsPressing("down")) return;

	// スタミナが残っていてダッシュボタンが押されているとき
	if (input.IsPressing("dash") && !m_pStamina->GetStaminaUseUp())
	{
		StateChange(StateKind::Dash);
	}
}

void PlayerState::StateTransitionJump(Input& input)
{
	// アクション中の場合は何もせずに終了する
	if (m_isAction) return;

	// スタミナが残っていてジャンプボタンが押されたとき
	if (input.IsTriggered("jump") && !m_pStamina->GetStaminaUseUp())
	{
		m_isAction = true;
		StateChange(StateKind::Jump);
	}

}

void PlayerState::StateTransition(Input& input)
{
	// 状態遷移
	StateTransitionIdle(input);
	StateTransitionWalk(input);
	StateTransitionDash(input);
	StateTransitionJump(input);
}

void PlayerState::StateChange(StateKind stateKind)
{
	for (auto& changeState : m_pState)
	{
		// 状態の種類が引数の状態の時
		if (changeState.stateKind == stateKind)
		{
			// 状態変更
			m_pNowState = changeState;
			// 状態の初期化処理
			m_pNowState.stateInit();
			return;
		}
	}
}
