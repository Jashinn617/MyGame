#include "Input.h"
#include "DxLib.h"

Input::Input()
{
	// ��{�^��
	m_commandTable["up"] = { {InputType::kwybd,KEY_INPUT_UP},
								{InputType::pad,PAD_INPUT_UP} };

	// ���{�^��
	m_commandTable["down"] = { {InputType::kwybd,KEY_INPUT_DOWN},
								{InputType::pad,PAD_INPUT_DOWN} };

	// �E�{�^��
	m_commandTable["right"] = { {InputType::kwybd,KEY_INPUT_RIGHT},
								{InputType::pad,PAD_INPUT_RIGHT} };

	// ���{�^��
	m_commandTable["left"] = { {InputType::kwybd,KEY_INPUT_LEFT},
								{InputType::pad,PAD_INPUT_LEFT} };

	// A�{�^��
	m_commandTable["A"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// B�{�^��
	m_commandTable["B"] = { {InputType::kwybd,KEY_INPUT_X},
								{InputType::pad,PAD_INPUT_B} };

	// Y�{�^��
	m_commandTable["Y"] = { {InputType::kwybd,KEY_INPUT_C},
								{InputType::pad,PAD_INPUT_Y} };

	// X�{�^��
	m_commandTable["X"] = { {InputType::kwybd,KEY_INPUT_V},
								{InputType::pad,PAD_INPUT_X} };
}

void Input::Update()
{
	// ���O���͂��R�s�[���Ă���
	m_lastInputData = m_nowInputData;

	// �n�[�h�E�F�A���̓`�F�b�N
	char keystate[256];	// �L�[�{�[�h�p�̔z��
	GetHitKeyStateAll(keystate);	// �L�[�{�[�h���͂̎擾
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);	// �p�b�h���̎擾

	// �o�^���ꂽ���ƃn�[�h�̏����Ƃ炵���킹��
	// ��������Ƃ�inputData�̓��e���X�V����
	for (const auto& cmd : m_commandTable)
	{
		// �R�}���h�̖��O������̓f�[�^�����
		auto& input = m_nowInputData[cmd.first];

		for (const auto& hardIO : cmd.second)
		{
			
			input = false;
			if (hardIO.first == InputType::kwybd)	// �L�[�{�[�h�̃`�F�b�N
			{
				// �L�[�{�[�h��������Ă����ꍇ
				if (keystate[hardIO.second])
				{
					input = true;
					break;	// �����������ł��Ȃ��悤�ɂ�����break����
				}
			}
			else if (hardIO.first == InputType::pad)	// �Q�[���p�b�h�̃`�F�b�N
			{
				// �Q�[���p�b�h��������Ă����ꍇ
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
	if (it == m_nowInputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(m_nowInputData.at(command) && !m_lastInputData.at(command));
}

bool Input::IsPressing(const char* command) const
{
	auto it = m_nowInputData.find(command);
	if (it == m_nowInputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(m_nowInputData.at(command));
}

bool Input::IsReleased(const char* command) const
{
	auto it = m_nowInputData.find(command);
	if (it == m_nowInputData.end())	// �v�f����
	{
		return false;	// �������Ȃ�
	}

	return(!m_nowInputData.at(command) && m_lastInputData.at(command));
}
