#include "Context.h"
#include "State.h"

Context::Context(std::function<void(void)> changeState):
	m_pNowState(nullptr),
	m_changeState(changeState)
{
	/*処理無し*/
}

Context::~Context()
{
	/*処理無し*/
}

void Context::Update()
{
	// 現在のステイトの更新
	m_pNowState->Update();
}

void Context::AddState(std::function<void(void)> listener, Context::StateData state)
{
	// ステイトを追加する
	m_pState.push_back(std::make_shared<State>(listener, state));
}

void Context::ChangeState(StateData stateData)
{
	if (m_pNowState == nullptr) // ステイトがひとつもない場合
	{
		// 先頭のステイトにして処理を終了する
		m_pNowState = m_pState.front();
		return;
	}

	// 現在の状態と変更する状態が同じ場合処理を終了する
	if (m_pNowState->GetStateData() == stateData) return;

	// ステイトの変更
	for (auto& state : m_pState)
	{
		if (state->GetStateData() == stateData) // 変更するステイトを見つけたら
		{
			// ステイトを変更する
			m_changeState();
			m_pNowState = state;
			return;
		}
	}
}

Context::StateData Context::GetState() const
{
	// 現在のステイトを返す
	return m_pNowState->GetStateData();
}