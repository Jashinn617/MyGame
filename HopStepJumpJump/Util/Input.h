#pragma once
#include <array>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

/// <summary>
/// ���̓f�o�C�X
/// </summary>
enum class InputType
{
	kwybd,		// �L�[�{�[�h
	pad			// �Q�[���p�b�h
};

// �R�}���h��,����<���̓f�o�C�X,����>
using InputTable_t = unordered_map<string, map<InputType, int>>;

/// <summary>
/// ���͂̊Ǘ�������N���X
/// </summary>
class Input
{
public:
	/// <summary>
	/// �����ꂽ�R�}���h�̑Ή��\
	/// </summary>
	Input();

	/// <summary>
	/// ���͏��̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �w��̃R�}���h�������ꂽ�u�ԂȂ̂���Ԃ�
	/// </summary>
	/// <param name="command">�R�}���h��</param>
	/// <returns></returns>
	bool IsTriggered(const char* command)const;

	/// <summary>
	/// �w��̃R�}���h����������Ă��邩��Ԃ�
	/// </summary>
	/// <param name="command">�R�}���h��</param>
	/// <returns></returns>
	bool IsPressing(const char* command)const;

	/// <summary>
	/// �w��̃R�}���h�������ꂽ�u�ԂȂ̂���Ԃ�
	/// </summary>
	/// <param name="command">�R�}���h��</param>
	/// <returns></returns>
	bool IsReleased(const char* command)const;


private:
	InputTable_t m_commandTable;	// �R�}���h���Ɠ��͂��y�A�ɂ����e�[�u��

	// �R�}���h�̓��͂��o���Ă���
	map<string, bool> m_nowInputData;	// ���݂̓���
	map<string, bool>m_lastInputData;	// ���O�̓���


};

