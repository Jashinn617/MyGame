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

	// �W�����v�{�^��
	m_commandTable["jump"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// �Z���N�g�{�^��
	m_commandTable["select"] = { {InputType::kwybd,KEY_INPUT_Z},
								{InputType::pad,PAD_INPUT_A} };

	// �_�b�V���{�^��
	m_commandTable["dash"] = { {InputType::kwybd,KEY_INPUT_X},
								{InputType::pad,PAD_INPUT_B} };
	// R�{�^��
	m_commandTable["R"] = { {InputType::kwybd,KEY_INPUT_S},
								{InputType::pad,PAD_INPUT_5} };

	// L�{�^��
	m_commandTable["L"] = { {InputType::kwybd,KEY_INPUT_D},
								{InputType::pad,PAD_INPUT_6} };
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
			// �L�[�{�[�h�̃`�F�b�N
			if (hardIO.first == InputType::kwybd)
			{
				// �L�[�{�[�h��������Ă����ꍇ
				if (keystate[hardIO.second])
				{
					input = true;
					break;	// �����������ł��Ȃ��悤�ɂ�����break����
				}
			}
			// �Q�[���p�b�h�̃`�F�b�N
			else if (hardIO.first == InputType::pad)
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
	// �����œn���ꂽ�R�}���h���ƈ�v����R�}���h�������邩���ׂ�
	auto it = m_nowInputData.find(command);
	// ��v����R�}���h�����Ȃ������ꍇ��false��Ԃ�
	if (it == m_nowInputData.end())
	{
		return false;
	}

	// ���݉�����Ă���A���O�ɉ�����Ă��Ȃ������ꍇ�Atrue��Ԃ�
	return(m_nowInputData.at(command) && !m_lastInputData.at(command));
}

bool Input::IsPressing(const char* command) const
{
	// �����œn���ꂽ�R�}���h���ƈ�v����R�}���h�������邩���ׂ�
	auto it = m_nowInputData.find(command);
	// ��v����R�}���h�����Ȃ������ꍇ��false��Ԃ�
	if (it == m_nowInputData.end())
	{
		return false;
	}

	// ���݉����������true��Ԃ�
	return(m_nowInputData.at(command));
}

bool Input::IsReleased(const char* command) const
{
	// �����œn���ꂽ�R�}���h���ƈ�v����R�}���h�������邩���ׂ�
	auto it = m_nowInputData.find(command);
	// ��v����R�}���h�����Ȃ������ꍇ��false��Ԃ�
	if (it == m_nowInputData.end())
	{
		return false;
	}

	// ���݉�����ĂȂ��A���O�ɉ�����Ă�����true��Ԃ�
	return(!m_nowInputData.at(command) && m_lastInputData.at(command));
}
