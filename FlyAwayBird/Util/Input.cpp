#include "Input.h"
#include "DxLib.h"

Input::Input()
{
	// 上ボタン
	m_commandTable["up"] = { {InputType::kwybd,KEY_INPUT_UP},
								{InputType::pad,PAD_INPUT_UP} };

	// 下ボタン
	m_commandTable["down"] = { {InputType::kwybd,KEY_INPUT_DOWN},
								{InputType::pad,PAD_INPUT_DOWN} };

	// 右ボタン
	m_commandTable["right"] = { {InputType::kwybd,KEY_INPUT_RIGHT},
								{InputType::pad,PAD_INPUT_RIGHT} };

	// 左ボタン
	m_commandTable["left"] = { {InputType::kwybd,KEY_INPUT_LEFT},
								{InputType::pad,PAD_INPUT_LEFT} };

	// Aボタン
	m_commandTable["A"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// Bボタン
	m_commandTable["B"] = { {InputType::kwybd,KEY_INPUT_X},
								{InputType::pad,PAD_INPUT_B} };

	// Yボタン
	m_commandTable["Y"] = { {InputType::kwybd,KEY_INPUT_C},
								{InputType::pad,PAD_INPUT_Y} };

	// Xボタン
	m_commandTable["X"] = { {InputType::kwybd,KEY_INPUT_V},
								{InputType::pad,PAD_INPUT_X} };
}

void Input::Update()
{
	// 直前入力をコピーしておく
	m_lastInputData = m_nowInputData;

	// ハードウェア入力チェック
	char keystate[256];	// キーボード用の配列
	GetHitKeyStateAll(keystate);	// キーボード入力の取得
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);	// パッド情報の取得

	// 登録された情報とハードの情報を照らし合わせる
	// それをもとにinputDataの内容を更新する
	for (const auto& cmd : m_commandTable)
	{
		// コマンドの名前から入力データを作る
		auto& input = m_nowInputData[cmd.first];

		for (const auto& hardIO : cmd.second)
		{
			
			input = false;
			if (hardIO.first == InputType::kwybd)	// キーボードのチェック
			{
				// キーボードが押されていた場合
				if (keystate[hardIO.second])
				{
					input = true;
					break;	// 同時押しをできないようにここでbreakする
				}
			}
			else if (hardIO.first == InputType::pad)	// ゲームパッドのチェック
			{
				// ゲームパッドが押されていた場合
				if (padstate & hardIO.second)
				{
					input = true;
					break;
				}
			}
		}
	}
}

bool Input::IsTriggered(const char* command) const
{
	auto it = m_nowInputData.find(command);
	if (it == m_nowInputData.end())	// 要素無し
	{
		return false;	// 反応しない
	}

	return(m_nowInputData.at(command) && !m_lastInputData.at(command));
}

bool Input::IsPressing(const char* command) const
{
	auto it = m_nowInputData.find(command);
	if (it == m_nowInputData.end())	// 要素無し
	{
		return false;	// 反応しない
	}

	return(m_nowInputData.at(command));
}

bool Input::IsReleased(const char* command) const
{
	auto it = m_nowInputData.find(command);
	if (it == m_nowInputData.end())	// 要素無し
	{
		return false;	// 反応しない
	}

	return(!m_nowInputData.at(command) && m_lastInputData.at(command));
}
