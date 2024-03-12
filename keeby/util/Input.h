#pragma once
#include<array>
#include<map>
#include<unordered_map>
#include<string>

enum class InputType
{
	kwybd,	// �L�[�{�[�h
	pad		// �p�b�h
};

using InputTable_t = std::unordered_map<std::string, std::map<InputType, int>>;

class Input
{
private:
	// �R�}���h���Ɠ��͂��y�A�ɂ����e�[�u��
	InputTable_t commandTable;
	std::vector<std::string> exclusiveKeyConfigCommands;

	// �R�}���h�̓��͂��o���Ă���
	std::map < std::string, bool> inputData;	// ���݂̓���
	std::map<std::string, bool>lastInputData;	// ���O�̓���

	const InputTable_t GetCommandTable() const;

public:

	Input();

	/// <summary>
	/// ���͏��̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �w��̃R�}���h�������ꂽ�u�ԂȂ̂��ǂ���
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	bool IsTriggered(const char* command)const;

	/// <summary>
	/// �������Ă��邩�ǂ���
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	bool IsPressing(const char* command)const;

	/// <summary>
	/// �w��̃R�}���h�������ꂽ�u�Ԃ��ǂ���
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	bool IsReleased(const char* command)const;



};

