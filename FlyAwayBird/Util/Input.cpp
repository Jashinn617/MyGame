#include "Input.h"
#include "DxLib.h"

Input::Input()
{
	// ��{�^��
	commandTable["up"] = { {InputType::kwybd,KEY_INPUT_UP},
								{InputType::pad,PAD_INPUT_UP} };

	// ���{�^��
	commandTable["down"] = { {InputType::kwybd,KEY_INPUT_DOWN},
								{InputType::pad,PAD_INPUT_DOWN} };

	// A�{�^��
	commandTable["A"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// B�{�^��
	commandTable["B"] = { {InputType::kwybd,KEY_INPUT_X},
								{InputType::pad,PAD_INPUT_B} };

	// Y�{�^��
	commandTable["Y"] = { {InputType::kwybd,KEY_INPUT_C},
								{InputType::pad,PAD_INPUT_Y} };

	// X�{�^��
	commandTable["X"] = { {InputType::kwybd,KEY_INPUT_V},
								{InputType::pad,PAD_INPUT_X} };
}

void Input::Update()
{
	// ���O���͂��R�s�[���Ă���
	lastInputData = nowInputData;

	// �n�[�h�E�F�A���̓`�F�b�N
	char keystate[256];	// �L�[�{�[�h�p�̔z��
	GetHitKeyStateAll(keystate);	// �L�[�{�[�h���͂̎擾
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);	// �p�b�h���̎擾

	// �o�^���ꂽ���ƃn�[�h�̏����Ƃ炵���킹��
	// ��������Ƃ�inputData�̓��e���X�V����
	for (const auto& cmd : commandTable)
	{
		// �R�}���h�̖��O������̓f�[�^�����
		auto& input = nowInputData[cmd.first];

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
	auto it = nowInputData.find(command);
	if (it == nowInputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(nowInputData.at(command) && !lastInputData.at(command));
}

bool Input::IsPressing(const char* command) const
{
	auto it = nowInputData.find(command);
	if (it == nowInputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(nowInputData.at(command));
}

bool Input::IsReleased(const char* command) const
{
	auto it = nowInputData.find(command);
	if (it == nowInputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(!nowInputData.at(command) && lastInputData.at(command));
}
