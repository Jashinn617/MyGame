#include "Input.h"
#include "DxLib.h"

Input::Input()
{
	// 上ボタン
	commandTable["up"] = { {InputType::kwybd,KEY_INPUT_UP},
								{InputType::pad,PAD_INPUT_UP} };

	// 下ボタン
	commandTable["down"] = { {InputType::kwybd,KEY_INPUT_DOWN},
								{InputType::pad,PAD_INPUT_DOWN} };

	// Aボタン
	commandTable["A"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// Bボタン
	commandTable["B"] = { {InputType::kwybd,KEY_INPUT_X},
								{InputType::pad,PAD_INPUT_B} };

	// Yボタン
	commandTable["Y"] = { {InputType::kwybd,KEY_INPUT_C},
								{InputType::pad,PAD_INPUT_Y} };

	// Xボタン
	commandTable["X"] = { {InputType::kwybd,KEY_INPUT_V},
								{InputType::pad,PAD_INPUT_X} };
}

void Input::Update()
{
	// 直前入力をコピーしておく
	lastInputData = nowInputData;

	// ハードウェア入力チェック
	char keystate[256];	// キーボード用の配列
	GetHitKeyStateAll(keystate);	// キーボード入力の取得
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);	// パッド情報の取得

	// 登録された情報とハードの情報を照らし合わせる
	// それをもとにinputDataの内容を更新する
	for (const auto& cmd : commandTable)
	{
		// コマンドの名前から入力データを作る
		auto& input = nowInputData[cmd.first];

		for (const auto& hardIO : cmd.second)
		{
			// キーボードのチェック
			input = false;
			if (hardIO.first == InputType::kwybd)
			{
				if (keystate[hardIO.second])
				{
					input = true;
					break;	// 同時押しをできないようにここでbreakする
				}
			}
			else if (hardIO.first == InputType::pad)
			{
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
	auto it = nowInputData.find(command);
	if (it == nowInputData.end())	// 要素無し
	{
		return false;	// 反応しない
	}

	return(nowInputData.at(command) && !lastInputData.at(command));
}

bool Input::IsPressing(const char* command) const
{
	auto it = nowInputData.find(command);
	if (it == nowInputData.end())	// 要素無し
	{
		return false;	// 反応しない
	}

	return(nowInputData.at(command));
}

bool Input::IsReleased(const char* command) const
{
	auto it = nowInputData.find(command);
	if (it == nowInputData.end())	// 要素無し
	{
		return false;	// 反応しない
	}

	return(!nowInputData.at(command) && lastInputData.at(command));
}
