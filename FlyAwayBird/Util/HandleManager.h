#pragma once
#include <unordered_map>
#include <string>

using namespace std;

// <�n���h����,�n���h��>
using HandleTable_t = unordered_map<string, int>;

/// <summary>
/// �e�n���h���̊Ǘ�������N���X
/// </summary>
class HandleManager
{
public:
	HandleManager();
	~HandleManager();

	int GetModel(const char* command)const;
	int GetImg(const char* command)const;
	int GetSound(const char* command)const;
	int GetFont(const char* command)const;

private:	// �֐�
	void LoadModel();
	void LoadImg();
	void LoadSound();
	void LoadFont();

	void DeleteModel();
	void DeleteImg();
	void DeleteSound();
	void DeleteFont();

private:// �ϐ�
	/*�n���h�����ƃn���h�����y�A�ɂ����e�[�u��*/
	HandleTable_t m_modelHandleTable;	// 3D���f���̃n���h��
	HandleTable_t m_imgHandleTable;		// �摜�̃n���h��
	HandleTable_t m_soundHandleTable;	// �T�E���h�̃n���h��

};

