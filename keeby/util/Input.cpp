#include "DxLib.h"
#include "Input.h"
#include <algorithm>

const InputTable_t Input::GetCommandTable() const
{
	InputTable_t ret = commandTable;

	for (const auto ex : exclusiveKeyConfigCommands)
	{
		ret.erase(ex);
	}
	return ret;
}

Input::Input()
{
	// �����ꂽ�R�}���h�̑Ή��\

	// ��{�^��
	commandTable["up"] = { {InputType::kwybd,KEY_INPUT_UP},
								{InputType::pad,PAD_INPUT_UP} };

	// ���{�^��
	commandTable["down"] = { {InputType::kwybd,KEY_INPUT_DOWN},
								{InputType::pad,PAD_INPUT_DOWN} };

	// ���{�^��
	commandTable["left"] = { {InputType::kwybd,KEY_INPUT_LEFT},
								{InputType::pad,PAD_INPUT_LEFT} };
	// �E�{�^��
	commandTable["right"] = { {InputType::kwybd,KEY_INPUT_RIGHT},
								{InputType::pad,PAD_INPUT_RIGHT} };

	// A�{�^��
	commandTable["A"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// B�{�^��
	commandTable["B"] = { {InputType::kwybd,KEY_INPUT_X},
								{InputType::pad,PAD_INPUT_B} };

	// �X�^�[�g�{�^���EY�{�^��
	commandTable["S"] = { {InputType::kwybd,KEY_INPUT_S},
								{InputType::pad,PAD_INPUT_Y} };

	// �X�^�[�g�{�^���EX�{�^��
	commandTable["P"] = { {InputType::kwybd,KEY_INPUT_P},
								{InputType::pad,PAD_INPUT_X} };
}

void Input::Update()
{
	// ���O���͂��R�s�[���Ă���
	lastInputData = inputData;

	// �n�[�h�E�F�A���̓`�F�b�N
	char keystate[256];	// �L�[�{�[�h�p
	GetHitKeyStateAll(keystate);	// �L�[�{�[�h���͂̎擾
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);	// �p�b�h���̎擾

	// �o�^���ꂽ���ƃn�[�h�̏����Ƃ炵���킹��
	// �������Ƃ�inputData�̓��e���X�V����
	for (const auto& cmd : commandTable)
	{
		// �R�}���h�̖��O������̓f�[�^�����
		auto& input = inputData[cmd.first];

		for (const auto& hardIO : cmd.second)
		{
			// �L�[�{�[�h�̃`�F�b�N
			input = false;
			if (hardIO.first == InputType::kwybd)
			{
				if (keystate[hardIO.second])
				{
					input = true;
					break;	// �����������ł��Ȃ��悤�ɂ�����break����
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
	auto it = inputData.find(command);
	if (it == inputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(inputData.at(command) && !lastInputData.at(command));
}

bool Input::IsPressing(const char* command) const
{
	auto it = inputData.find(command);
	if (it == inputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(inputData.at(command));
}

bool Input::IsReleased(const char* command) const
{
	auto it = inputData.find(command);
	if (it == inputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(!inputData.at(command) && lastInputData.at(command));
}


